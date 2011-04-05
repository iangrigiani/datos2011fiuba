//============================================================================
// Name        : tpDatos2011.cpp
// Author      : lucas
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
using namespace std;
#include "ManejadorArchivoRLV/HandlerArchivoRLV.h"
#include "EstructurasEnComun/Registro.h"
#include "ParserLibros/ParserDeLibros.h"
#include "ArbolB+/ArbolBMas.h"

int main() {
	ParserDeLibros* p = new ParserDeLibros();
	ifstream fd;
	fd.open("Test1.txt", ios_base::in);
	fd.seekg(0, ios_base::end);
	int tamanio = fd.tellg();
	fd.seekg(0, ios_base::beg);
	char* libro = (char*)calloc(tamanio, sizeof(char));
	fd.read(libro, tamanio);
	fd.close();
	cout << "El libro es: " << endl;
	cout << libro << endl;
	Registro* reg = p->obtenerRegistroDeLibro(libro);
	reg->toString();
	p->mostrarLista();
//	int offset = handler->insertarRegistro("Test1.txt");
//	cout << "Grabe libro en offset: " << offset <<  endl;
	delete p;
//	HandlerArchivoRLV* handler2 = new HandlerArchivoRLV();
//	handler2->insertarLibro("Libro.txt");
//	cout << "Grabe libro" << endl;
//	delete handler2;
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
