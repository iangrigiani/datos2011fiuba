#ifndef HANDLERARCHIVORLV_H_
#define HANDLERARCHIVORLV_H_

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
		int ultimo_ID;
		long int size;
		int obtenerTamanioLibro(char * cadenaDeDatos);
		void obtenerDatosDeEntrada();

public:
		HandlerArchivoRLV();
		virtual ~HandlerArchivoRLV() {};
		int insertarLibro(const string& path_nuevo_libro);
		char* buscarLibro(int offset);
		void quitarLibro(int offset);

};

#endif /* HANDLERARCHIVORLV_H_ */
