/*
 * HandlerArchivoRLV.cpp
 *
 *  Created on: 30/03/2011
 *      Author: angeles
 */

#include "HandlerArchivoRLV.h"

HandlerArchivoRLV::HandlerArchivoRLV() {
	string path(PATH_REG_LONG_VARIABLE);
	this->path = path;

	FILE* arch;
	if ((arch = fopen(this->path.c_str(), "r")) == NULL) {
		cout << "Error al intentar abrir el archivo: " << this->path << endl;
		return;
	}

	char buffer[sizeof(int)];
	fread(buffer, 1, sizeof(int), arch);
	this->ultimo_ID = atoi(buffer);

	fseek(arch, 0, SEEK_END);
	this->size = ftell(arch);

	fclose(arch);
}

void HandlerArchivoRLV::insertarNuevoLibro(const string& path_nuevo_libro)
{
	FILE* f_src;
	FILE* f_dst;

	if ((f_src = fopen(path_nuevo_libro.c_str(), "r")) == NULL) {
		cout << "Error al intentar abrir el archivo: " << path_nuevo_libro << endl;
		return;
	}

	fseek(f_src, 0, SEEK_END);
	long int size = ftell(f_src);
	rewind(f_src);

	char* buffer = (char*) malloc (sizeof(char) * size);
	fread(buffer, 1, size, f_src);
	fclose(f_src);

	cout << buffer << endl;

	int indexado = 0;
	int procesado = 1;
	int id_Archivo = this->ultimo_ID + 1;

	if ((f_dst = fopen(this->path.c_str(), "a+")) == NULL) {
		cout << "Error al intentar abrir el archivo: " << this->path << endl;
		return;
	}

	stringstream ss;
	ss << id_Archivo << "|" << size << "|" << procesado << "|" << indexado << "|" << "\n";
	string str = ss.str();
	//char* buffer_aux = str.c_str();
	//fwrite(buffer_aux, 1, str.length(), f_dst);
	fwrite(buffer, 1, size, f_dst);

	fclose(f_dst);

	free(buffer);
}

char* HandlerArchivoRLV::obtenerLibro(int offset)
{
	std::ifstream archivoRegistros;
	char * cadenaDeDatos;
	int espacioOcupado;

	archivoRegistros.open(this->path.c_str());
	archivoRegistros.seekg(offset);

	//Obtengo la linea correspondiente al libro en la que se tiene la información de tamanio
	archivoRegistros.get(cadenaDeDatos,100);


	int longitudCadena = strlen(cadenaDeDatos);

	//Obtengo el tamanio del libro a leer
	espacioOcupado = obtenerTamanioLibro(cadenaDeDatos);


	/*Le sumo a la longitud de la cadena de datos el offset para posicionarme nuevamente
	 en el archivo*/
	longitudCadena += offset;

	archivoRegistros.seekg(longitudCadena);

	char * libroLeido = (char*)calloc (espacioOcupado, sizeof(char));

	archivoRegistros.read(libroLeido, espacioOcupado);

	//Prueba para ver si leyo bien después BORRAR!!!!
	cout.write(libroLeido,espacioOcupado);

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

