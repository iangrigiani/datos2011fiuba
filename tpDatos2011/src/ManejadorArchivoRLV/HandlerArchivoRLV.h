#ifndef HandlerArchivoRLV_H_
#define HandlerArchivoRLV_H_

#include <sstream>
#include <fstream>
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../EstructurasEnComun/Constantes.h"

using namespace std;

class HandlerArchivoRLV{

private:
		int ultimoID;
		int ultimoOffset;
		int obtenerTamanioLibro(char * cadenaDeDatos);
		void recuperarUltimoID();
		void grabarUltimoID();
		int obtenerTamanioMaestro();
public:
		HandlerArchivoRLV();
		virtual ~HandlerArchivoRLV() {};
		int insertarRegistro(const string& path_nuevo_libro);
		char* buscarRegistro(int offset);
		void quitarRegistro(int offset);
};

#endif /* HANDLERARCHIVORLV_H_ */
