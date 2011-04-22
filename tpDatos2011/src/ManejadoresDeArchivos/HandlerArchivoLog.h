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
	void buscarRegistro(int IDArchivo);
	void setearIndexadoPorAutor(int IDArchivo);
	void setearIndexadoPorEditorial(int IDArchivo);
	void setearIndexadoPorTitulo(int IDArchivo);
	void setearIndexadoPorPalabras(int IDArchivo);

private:
	string crearStringAInsertar(int numero);
};

#endif /* HANDLERARCHIVOLOG_H_ */
