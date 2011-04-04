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


void HandlerArchivoRLV::recuperarUltimoID(){
	FILE* arch;
	if ((arch = fopen(PATH_CONFIG_RLV, "r")) == NULL) {
		cout << "Error al intentar abrir el archivo: " << PATH_CONFIG_RLV << endl;
		return;
	}

	char buffer[sizeof(int)];
	fread(buffer, 1, sizeof(int), arch);
	string cad = buffer;
	if (cad.length() > 0){
		this->ultimoID = atoi(buffer);
	}else{
		this->ultimoID = 0;
	}
	fclose(arch);

	std::ifstream archivoMaestro;
	char  cadena[100];
	archivoMaestro.open(PATH_CONFIG_RLV, std::ios_base::in);
	archivoMaestro.seekg(0);
	archivoMaestro.get(cadena,100);
	string cad2 = cadena;
	int longitudCadena = cad2.length();
	if (longitudCadena > 0){
		this->ultimoOffset = obtenerTamanioLibro(cadena);
	}else{
		this->ultimoOffset = 0;
	}
}

HandlerArchivoRLV::HandlerArchivoRLV() {
    recuperarUltimoID();

}

int HandlerArchivoRLV::insertarRegistro(const string& path_nuevo_libro)
{
// Manejo sobre el archivo del libro a ingresar
	std::ifstream f_ent;
	f_ent.open(path_nuevo_libro.c_str(), std::ios_base::in);
	f_ent.seekg(0,std::ios_base::end);
	// Obtengo tamanio de libro
	int size = f_ent.tellg();
	f_ent.seekg(0);
	char* buffer = (char*) calloc (size-1 , sizeof(char));
    f_ent.read(buffer, size);
	f_ent.close();


// Obtengo ID del ultimo libro ingresado
	int id_Archivo = this->ultimoID + 1;
    this->ultimoID = id_Archivo;
// Manejo sobre el archivo de RLV
    this->ultimoOffset = obtenerTamanioMaestro();
    grabarUltimoID();

    int indexado = 0;
	int procesado = 1;

	std::ofstream f_dst;
	f_dst.open(PATH_REG_LONG_VARIABLE, std::ios_base::app);
	stringstream ss;
	// Armo los datos de entrada para ese libro
	ss << id_Archivo << "|" << size << "|" << procesado << "|" << indexado << "|" << "\n" << buffer;
	string str = ss.str();
	// Escribo libro en el archivo de RLV
	f_dst.write(str.c_str(), str.length());
	f_dst.close();
	free(buffer);
// Retorno el offset que se guardara en el arbol.
	return this->ultimoOffset;
}

void HandlerArchivoRLV::grabarUltimoID(){
	std::ofstream f_dst;
	f_dst.open(PATH_CONFIG_RLV, std::ios_base::out);
	stringstream ss;
	// Armo los datos de entrada para ese libro
	ss << this->ultimoID << "|" << this->ultimoOffset;
	string str = ss.str();
	// Escribo libro en el archivo de RLV
	f_dst.write(str.c_str(), str.length());
	f_dst.flush();
	f_dst.close();
}

/*
 * Devuelve un puntero a una cadena de char que contiene todo el libro
 */
char* HandlerArchivoRLV::buscarRegistro(int offset)
{
	std::ifstream archivoMaestro;
	char  cadenaDeDatos[100];
	archivoMaestro.open(PATH_REG_LONG_VARIABLE, std::ios_base::in);
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
