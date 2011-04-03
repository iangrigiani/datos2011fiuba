#ifndef HandlerArchivoRLV_H_
#define HandlerArchivoRLV_H_

#include <sstream>
#include <fstream>
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "Constantes.h"

using namespace std;

class HandlerArchivoRLV{

private:
		int ultimoID;
		long int size;
		int obtenerTamanioLibro(char * cadenaDeDatos);
		void recuperarUltimoID();
		int obtenerUltimoIDPersistido(char * cadenaDeDatos);

public:
		HandlerArchivoRLV();
		virtual ~HandlerArchivoRLV() {};
		int insertarLibro(const string& path_nuevo_libro);
		char* buscarLibro(int offset);
		void quitarLibro(int offset);
		int obtenerUltimoID(); //TODO Borrar luego de pruebas
};

#endif /* HANDLERARCHIVORLV_H_ */
