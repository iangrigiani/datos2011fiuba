/*
 * HandlerArchivoRLV.h
 *
 *  Created on: 30/03/2011
 *      Author: angeles
 */

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

class HandlerArchivoRLV {

private:
		string path;
		int ultimo_ID;
		long int size;

		int obtenerTamanioLibro(char * cadenaDeDatos);

public:
		HandlerArchivoRLV();
		virtual ~HandlerArchivoRLV() {};

		void insertarNuevoLibro(const string& path_nuevo_libro);
		char* obtenerLibro(int offset);

};

#endif /* HANDLERARCHIVORLV_H_ */
