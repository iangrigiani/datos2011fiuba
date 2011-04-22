/*
 * HandlerArchivoLog.cpp
 *
 *  Created on: 22/04/2011
 *      Author: andrea
 */


#include "HandlerArchivoLog.h"
#include <sstream>
#include <fstream>
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../EstructurasEnComun/Constantes.h"

HandlerArchivoLog::HandlerArchivoLog() {
	// TODO Auto-generated constructor stub
}

HandlerArchivoLog::~HandlerArchivoLog() {
	// TODO Auto-generated destructor stub
}

void HandlerArchivoLog::insertarRegistro(int IDArchivo){
	string linea = crearStringAInsertar(IDArchivo);
	ofstream archivoLog;
	archivoLog.open(PATH_ARCHIVO_LOG,std::ios_base::app);
	archivoLog.write(linea.c_str(), linea.length());
	archivoLog.close();
}

void HandlerArchivoLog::buscarRegistro(int IDArchivo){}
void HandlerArchivoLog::setearIndexadoPorAutor(int IDArchivo){}
void HandlerArchivoLog::setearIndexadoPorEditorial(int IDArchivo){}
void HandlerArchivoLog::setearIndexadoPorTitulo(int IDArchivo){}
void HandlerArchivoLog::setearIndexadoPorPalabras(int IDArchivo){}


string HandlerArchivoLog::crearStringAInsertar(int numero){
   stringstream ss;
   ss << numero  << "|" << "0" << "|" << "0" << "|" << "0"<< "|" << "0" << "\n" ;
   return ss.str();
}



