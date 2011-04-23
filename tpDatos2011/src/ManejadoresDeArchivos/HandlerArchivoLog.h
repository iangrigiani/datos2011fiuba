/*
 * HandlerArchivoLog.h
 *
 *  Created on: 22/04/2011
 *      Author: andrea
 */

#ifndef HANDLERARCHIVOLOG_H_
#define HANDLERARCHIVOLOG_H_

#include <sstream>
#include <fstream>
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../EstructurasEnComun/Constantes.h"

using namespace std;

class HandlerArchivoLog {
public:
	HandlerArchivoLog();
	virtual ~HandlerArchivoLog();
	void insertarRegistro(int IDArchivo);
	int  buscarRegistro(int IDArchivo);
	void setearIndexado(int IDArchivo, int parametro);


private:
	string crearStringAInsertar(int numero, int ind1, int ind2, int ind3, int ind4);

};

#endif /* HANDLERARCHIVOLOG_H_ */
