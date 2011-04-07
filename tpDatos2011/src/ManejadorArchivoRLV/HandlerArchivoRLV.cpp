#include "HandlerArchivoRLV.h"


int HandlerArchivoRLV::obtenerTamanioLibro(char * cadenaDeDatos)
{
	char * caracterProcesado;
	int tamanioLibro;
	strtok(cadenaDeDatos,"|");

	//Busco donde se que se encuentra el campo asociado al tamanio del libro
	caracterProcesado = strtok(NULL,"|");
	tamanioLibro = atoi(caracterProcesado);
	return tamanioLibro;
}

HandlerArchivoRLV::HandlerArchivoRLV() {
}

int HandlerArchivoRLV::insertarRegistro(const string& path_nuevo_libro)
{
// Manejo sobre el archivo del libro a ingresar
	std::ifstream f_ent;
	f_ent.open(path_nuevo_libro.c_str(), std::ios_base::in);
	f_ent.seekg(0,std::ios_base::end);

	// Obtengo tamanio de libro
	int tamanioRegistro = f_ent.tellg();
	f_ent.seekg(0);
	char* buffer = (char*) calloc (tamanioRegistro-1 , sizeof(char));
    f_ent.read(buffer, tamanioRegistro);

    f_ent.close();


// Obtengo ID del ultimo libro ingresado y seteo todos sus datos
	int id_Archivo = buscarOffsetArchivoEspaciosLibres(tamanioRegistro);
	if (id_Archivo == ERROR){
		id_Archivo = this->obtenerTamanioMaestro();
	}else{
/*
 *  Si lo voy a insertar en un espacio libre debo borrar ese dato
 *  del archivo de espacios libres
 */
		borrarOffsetArchivoDeEspaciosLibres(id_Archivo);
	}
    int indexado = 0;
	int procesado = 1;

// Manejo sobre el archivo de RLV
	std::ofstream f_dst;
	f_dst.open(PATH_REG_LONG_VARIABLE, std::ios_base::app);
	stringstream ss;

// Armo las cabecera para el libro
	ss << id_Archivo << "|" << tamanioRegistro << "|" << procesado << "|" << indexado << "|" << "\n" << buffer << "\n" ;
	string str = ss.str();
	// Escribo libro en el archivo de RLV
	f_dst.write(str.c_str(), str.length());

	f_dst.close();

	free(buffer);

// Retorno el offset que se guardara en el arbol.
	return id_Archivo;
}

char* HandlerArchivoRLV::buscarRegistro(int offset)
{
	std::ifstream archivoMaestro;
	char  cadenaDeDatos[100];
	archivoMaestro.open(PATH_REG_LONG_VARIABLE, std::ios_base::in);
	// Me posiciono en el archivo de RLV
	archivoMaestro.seekg(offset);

	archivoMaestro.get(cadenaDeDatos,100);
	string cad = cadenaDeDatos;
	int longitudCadena = cad.length();
	longitudCadena += offset;
	//Obtengo el tamanio del libro a leer
	int espacioOcupado = obtenerTamanioLibro(cadenaDeDatos);

	/*Le sumo a la longitud de la cadena de datos el offset para posicionarme nuevamente
	 en el archivo*/
	archivoMaestro.seekg(longitudCadena);
	// obtengo el libro
	char * libroLeido = (char*)calloc (espacioOcupado, sizeof(char));
	archivoMaestro.read(libroLeido, espacioOcupado);
	archivoMaestro.close();

	return libroLeido;
}

int HandlerArchivoRLV::obtenerTamanioMaestro(){
	FILE* fin;
	if ((fin = fopen(PATH_REG_LONG_VARIABLE, "r")) == NULL){
		cout << "Error al abrir el archivo de registro de longitud variable" << endl;
		return -1;
	}
	fseek(fin, 0 , SEEK_END);
	int retorno = ftell(fin);
	rewind(fin);
	fclose(fin);
	return retorno;
}

void HandlerArchivoRLV::quitarRegistro(int offset){
// Abro el archivo y me posiciono para obtener los datos
	std::fstream fh;
	char  cadenaDeDatos[100];
	fh.open(PATH_REG_LONG_VARIABLE, std::ios_base::in | std::ios_base::out);
	fh.seekg(offset);
	fh.get(cadenaDeDatos,100);
	string cad = cadenaDeDatos;
	int longitudCadena = cad.length();
	int espacioOcupado = obtenerTamanioLibro(cadenaDeDatos);
	espacioOcupado += longitudCadena;
	fh.seekg(offset);
	char * libroLeido = (char*)calloc (espacioOcupado, sizeof(char));
	free(libroLeido);
	fh.write(libroLeido, espacioOcupado);
	fh.flush();

	fh.close();

// Agrego los datos en el archivo de espacios libres.
	actualizarEspaciosLibres(offset,espacioOcupado);
}

/*
 * Busca un offset en el archivo de espacios libres de acuerdo al tamaño de registro
 * que recibe por parámetro. Si lo encuentra devuelve ese offset asociado al tamanio
 * de registro.
 * Si no existe ninguno devuelve ERROR.
 */
int HandlerArchivoRLV::buscarOffsetArchivoEspaciosLibres(int tamanioRegistro){

	std::fstream archEspaciosLibres;
	char  cadenaDeDatos[100];
	bool encontrado = false;
	int offsetProcesado = 0;
	int tamanioProcesado = 0;
	int longCadenaDeDatos = 0;
	string cadena;
	char * caracterProcesado;

	archEspaciosLibres.open(PATH_ESPACIO_LIBRE_RLV, std::ios_base::in | std::ios_base::out);

	while (!encontrado and !archEspaciosLibres.eof())
	{
		archEspaciosLibres.get(cadenaDeDatos,100);
		cadena = cadenaDeDatos;

		strtok(cadenaDeDatos,"|");
		caracterProcesado = strtok(NULL,"|");
		tamanioProcesado = atoi(caracterProcesado);

		//Si el tamanio del registro es el que se proceso
		//entonces se borra el offset del archivo de espacios libres.
		if(tamanioRegistro == tamanioProcesado) //TODO No debería ser mayor o igual?
		{
			encontrado = true;
			offsetProcesado = atoi(cadenaDeDatos);
			this->borrarOffsetArchivoDeEspaciosLibres(offsetProcesado);
		}

		longCadenaDeDatos+= cadena.length();
		longCadenaDeDatos++;

		archEspaciosLibres.seekg(longCadenaDeDatos);
	}

	if(encontrado)
		return offsetProcesado;
	else
		return ERROR;
}

void HandlerArchivoRLV::actualizarEspaciosLibres(int offset,int espacioLibre){
	std::fstream fh;
	fh.open(PATH_REG_LONG_VARIABLE, std::ios_base::app);
	stringstream ss;
	ss << offset << "|" << espacioLibre << "\n" ;
	string str = ss.str();
	fh.write(str.c_str(), str.length());
	fh.flush();
	fh.close();
}

/* Borra del Archivo de Espacios Libres la linea del offset que se va ocupar
 * Recibe el offset dentro del archivo de Espacios Libre
 */
void HandlerArchivoRLV::borrarOffsetArchivoDeEspaciosLibres(int offsetLineaABorrar){

	char  cadenaDeDatos[100];
	string cadena;
    int longCadena = 0;

	std::fstream el;
	el.open(PATH_ESPACIO_LIBRE_RLV, std::ios_base::in | std::ios_base::out);
	el.seekg(offsetLineaABorrar);

	archEspaciosLibres.get(cadenaDeDatos,100);
    strtok(cadenaDeDatos,"/n");
	cadena = cadenaDeDatos;

    longCadena = cadena.length();
    while (longCadena){
        el.put(offsetLineaABorrar, "0");
        offsetLineaABorrar++;
        longCadena--;
    }
}
