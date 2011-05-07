#include "HandlerArchivoRLV.h"


int HandlerArchivoRLV::obtenerTamanioLibro(char * cadenaDeDatos)
{
	char * caracterProcesado;
	int tamanioLibro;
	strtok(cadenaDeDatos,"|");

	//Busco donde se que se encuentra el campo asociado al tamanio del libro
	caracterProcesado = strtok(NULL,"|");
	if (caracterProcesado){
		tamanioLibro = atoi(caracterProcesado);
		return tamanioLibro;
	}else{
		return 0;
	}
}

HandlerArchivoRLV::HandlerArchivoRLV() {
	this->offsetAAEL = 0;
}

int HandlerArchivoRLV::insertarRegistro(const string& path_nuevo_libro)
{
	// Manejo sobre el archivo del libro a ingresar
	std::ifstream f_ent;
	f_ent.open(path_nuevo_libro.c_str(), std::ios_base::in);
	if (f_ent.is_open()){

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
			borrarOffsetArchivoDeEspaciosLibres();
		}
		int indexado = 0;
		int procesado = 1;

		// Manejo sobre el archivo de RLV
		std::fstream f_dst;
		f_dst.open(PATH_REG_LONG_VARIABLE, std::ios_base::in | std::ios_base::out);
		stringstream ss;

		// Armo las cabecera para el libro
		ss << id_Archivo << "|" << tamanioRegistro << "|" << procesado << "|" << indexado << "|" << "\n" << buffer << "\n" ;
		string str = ss.str();
		// Escribo libro en el archivo de RLV
		f_dst.seekg(id_Archivo);
		f_dst.write(str.c_str(), str.length());

		f_dst.close();

		free(buffer);

		// Retorno el offset que se guardara en el arbol.
		return id_Archivo;
	}else{
		cout << "Path de libro incorrecto" << endl;
		return ERROR;
	}
}

char* HandlerArchivoRLV::buscarRegistro(int offset)
{
	std::ifstream archivoMaestro;
	char  cadenaDeDatos[100];
	archivoMaestro.open(PATH_REG_LONG_VARIABLE, std::ios_base::in);
	if (archivoMaestro.is_open()){
		// Me posiciono en el archivo de RLV
		archivoMaestro.seekg(offset);

		archivoMaestro.get(cadenaDeDatos,100);
		string cad = cadenaDeDatos;
		int longitudCadena = cad.length();
		longitudCadena += offset;
		int tamanioArchivo = obtenerTamanioMaestro();
		if (tamanioArchivo > BASURA_RLV){
			//Obtengo el tamanio del libro a leer
			int espacioOcupado = obtenerTamanioLibro(cadenaDeDatos);
			if (espacioOcupado > 0){
				/*Le sumo a la longitud de la cadena de datos el offset para posicionarme nuevamente
				 en el archivo*/
				archivoMaestro.seekg(longitudCadena);
				// obtengo el libro
				char * libroLeido = (char*)calloc (espacioOcupado, sizeof(char));
				archivoMaestro.read(libroLeido, espacioOcupado);
				archivoMaestro.close();
				return libroLeido;
			}
		}else{
			return NULL;
		}
	}else{
		archivoMaestro.open(PATH_REG_LONG_VARIABLE, std::ios_base::out);
		archivoMaestro.close();
		return NULL;
	}
	return NULL;
}

int HandlerArchivoRLV::obtenerTamanioMaestro(){
	FILE* fin;
	if ((fin = fopen(PATH_REG_LONG_VARIABLE, "r")) == NULL){
		fin = fopen(PATH_REG_LONG_VARIABLE, "w");
		fclose(fin);
		fin = fopen(PATH_REG_LONG_VARIABLE, "r");
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
	int tamanioArchivo = obtenerTamanioMaestro();
	if (tamanioArchivo > BASURA_RLV){
		int espacioOcupado = obtenerTamanioLibro(cadenaDeDatos);
		if (espacioOcupado > 0){
			espacioOcupado += longitudCadena;
			fh.seekg(offset); //No tendría que ser un seekp?

			char * libroLeido = (char*)calloc (espacioOcupado, sizeof(char));
			free(libroLeido);
			fh.write(libroLeido, espacioOcupado);
			fh.flush();
			fh.close();

			// Agrego los datos en el archivo de espacios libres.
			actualizarEspaciosLibres(offset,espacioOcupado);
		}
	}
}


/* PRE: Recibe tamanioRegistro que indica la cant. de espacio que hay que buscar
 * Busca un offset en el archivo de espacios libres de acuerdo al tamaño de registro
 * que recibe por parámetro. Si lo encuentra devuelve ese offset asociado al tamanio
 * de registro.
 * Si no existe ninguno devuelve ERROR.
 */
int HandlerArchivoRLV::buscarOffsetArchivoEspaciosLibres(int tamanioRegistro){

	std:: fstream ifs;
	ifs.open(PATH_ESPACIO_LIBRE_RLV, std::ios_base::in | std::ios_base::out);
	if (!ifs.is_open()){
		ifs.open(PATH_ESPACIO_LIBRE_RLV, std::ios_base::out);
		ifs.close();
		ifs.open(PATH_ESPACIO_LIBRE_RLV, std::ios_base::in | std::ios_base::out);
	}
	char* cadena = (char*)calloc(100, sizeof(char));
	bool encontrado  = false;
	int tamanioLibro = 0;
	char * caracterProcesado;
	int retorno = ERROR;
	string cad;
	while (!encontrado && !ifs.eof()){
		this->offsetAAEL = ifs.tellg();
		ifs.getline(cadena, 100);
		cad = cadena;
		if (cad.length() > 0){
			retorno = atoi(strtok(cadena,"|"));
			//Busco donde se que se encuentra el campo asociado al tamanio del libro
			caracterProcesado = strtok(NULL,"\n");
			tamanioLibro = atoi(caracterProcesado);
			if (tamanioLibro >= tamanioRegistro){
				encontrado = true;
			}else{
				retorno = ERROR;
				tamanioLibro = 0;
			}
		}else{
			retorno = ERROR;
		}
	}
ifs.close();
return retorno;
}

void HandlerArchivoRLV::actualizarEspaciosLibres(int offset,int espacioLibre){
	std::ofstream fh;
	fh.open(PATH_ESPACIO_LIBRE_RLV, std::ios_base::app);
	stringstream ss;
	ss << offset << "|" << espacioLibre << "\n" ;
	string str = ss.str();
	fh.write(str.c_str(), str.length());
	fh.flush();
	fh.close();
}


void HandlerArchivoRLV::borrarOffsetArchivoDeEspaciosLibres(){
	std::fstream fh;
	char  cadenaDeDatos[100];
	fh.open(PATH_ESPACIO_LIBRE_RLV, std::ios_base::in | std::ios_base::out);
	fh.seekg(this->offsetAAEL);
	fh.get(cadenaDeDatos,100);
	string cad = cadenaDeDatos;
	cad = cadenaDeDatos;
	int longitudCadena = cad.length();
	fh.seekg(this->offsetAAEL); //No tendría que ser un seekp?
	char * libroLeido = (char*)calloc (longitudCadena, sizeof(char));
	free(libroLeido);
	fh.write(libroLeido, longitudCadena);
	fh.flush();
	fh.close();
}
