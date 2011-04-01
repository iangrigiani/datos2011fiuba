#include "HandlerArchivoRLV.h"

HandlerArchivoRLV::HandlerArchivoRLV() {
	obtenerDatosDeEntrada();
}

int HandlerArchivoRLV::insertarNuevoLibro(const string& path_nuevo_libro)
{
	FILE* f_src;
	FILE* f_dst;
	obtenerDatosDeEntrada();
	if ((f_src = fopen(path_nuevo_libro.c_str(), "r")) == NULL) {
		cout << "Error al intentar abrir el archivo : " << path_nuevo_libro << endl;
		return ERROR;
	}

	fseek(f_src, 0, SEEK_END);
	long int size = ftell(f_src);
	rewind(f_src);

	char* buffer = (char*) malloc (sizeof(char) * size);
	fread(buffer, 1, size, f_src);
	fclose(f_src);

	int indexado = 0;
	int procesado = 1;
	int id_Archivo = this->ultimo_ID + 1;
	if ((f_dst = fopen(PATH_REG_LONG_VARIABLE, "a+")) == NULL) {
		cout << "El archivo de Registros variables no está creado"<< endl;
		return ERROR;
	}

	stringstream ss;
	ss << id_Archivo << "|" << size << "|" << procesado << "|" << indexado << "|" << "\n" << buffer;
	string str = ss.str();
	fwrite(str.c_str(), 1,((3* sizeof(int))+size) ,f_dst);
	fclose(f_dst);
	free(buffer);
	return OK;
}

char* HandlerArchivoRLV::obtenerLibro(int offset)
{
	std::ifstream archivoRegistros;
	char * cadenaDeDatos;
	archivoRegistros.open(PATH_REG_LONG_VARIABLE);
	archivoRegistros.seekg(offset);
	//Obtengo la linea correspondiente al libro en la que se tiene la información de tamanio
	archivoRegistros.get(cadenaDeDatos,100);
	string cad = cadenaDeDatos;
	int longitudCadena = cad.length();

	//Obtengo el tamanio del libro a leer
	int espacioOcupado = obtenerTamanioLibro(cadenaDeDatos);
	/*Le sumo a la longitud de la cadena de datos el offset para posicionarme nuevamente
	 en el archivo*/
	longitudCadena += offset;

	archivoRegistros.seekg(longitudCadena);
	char * libroLeido = (char*)calloc (espacioOcupado, sizeof(char));

	archivoRegistros.read(libroLeido, espacioOcupado);
	archivoRegistros.close();
	//No olvidar de liberar la memoria!!!!
	return libroLeido;
}

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

void HandlerArchivoRLV::obtenerDatosDeEntrada(){
	FILE* arch;
	if ((arch = fopen(PATH_REG_LONG_VARIABLE, "r")) == NULL) {
		cout << "Error al intentar abrir el archivo : " << PATH_REG_LONG_VARIABLE << endl;
		return;
	}else{
		char buffer[sizeof(int)];
		fread(buffer, 1, sizeof(int), arch);
		this->ultimo_ID = atoi(buffer);
		fseek(arch, 0, SEEK_END);
		this->size = ftell(arch);

		fclose(arch);
	}
}
