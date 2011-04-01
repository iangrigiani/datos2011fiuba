//============================================================================
// Name        : tpDatos2011.cpp
// Author      : lucas
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
using namespace std;
#include "EstructurasEnComun/Registro.h"
#include "ManejadorArchivoRLV/HandlerArchivoRLV.h"
#include "ArbolB+/ArbolBMas.h"

int main() {
	HandlerArchivoRLV* handler = new HandlerArchivoRLV();
	handler->insertarLibro("Libro.txt");
	cout << "Grabe libro" << endl;
//		handler->insertarLibro("Libro.txt");
//		handler->insertarLibro("Libro.txt");
//		handler->insertarLibro("Libro.txt");
//	delete handler;

//	if (handler->insertarLibro("Libro.txt") == OK){
//			cout << "Grabe Libro" << endl;
//	}
//	delete handler;
//	HandlerArchivoRLV* handler2 = new HandlerArchivoRLV();
//	char * Libro = handler2->buscarLibro(0);
//	cout << Libro;
//	delete handler2;
}
