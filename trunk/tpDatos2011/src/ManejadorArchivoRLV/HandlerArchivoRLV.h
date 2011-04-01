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
		int insertarNuevoLibro(const string& path_nuevo_libro);
		char* obtenerLibro(int offset);

};

#endif /* HANDLERARCHIVORLV_H_ */
