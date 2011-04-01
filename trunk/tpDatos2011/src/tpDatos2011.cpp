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
//	if (handler->insertarNuevoLibro("Libro.txt") == OK){
//			cout << "Grabe Libro" << endl;
//	}

	char * Libro = handler->obtenerLibro(0);
	cout << Libro << endl;
}
