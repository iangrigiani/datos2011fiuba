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
#include "ManejadoresDeArchivos/HandlerDeBloques.h"
#include "ManejadoresDeArchivos/HandlerBloques.h"
#include "ParserLibros/ParserDeLibros.h"
#include "ArbolB+/ArbolBMas.h"

int main() {
//
//	HandlerDeBloques* h = new HandlerDeBloques("Archivo_Nodos.txt");
//
//	Elementos* e = new Elementos(new Clave("holaaa"), 20);
//	unsigned int offsetElemento = 0;
//	char* bufferElemento = (char*)calloc(TAMANIO_BUFFER, sizeof(char));
//	e->serializar(bufferElemento, offsetElemento);
//	h->guardar_bloque(bufferElemento,0);
//
//	Elementos* e2 = new Elementos(new Clave("holaaa2"), 202);
//	unsigned int offsetElemento2 = 0;
//	char* bufferElemento2 = (char*)calloc(TAMANIO_BUFFER, sizeof(char));
//	e2->serializar(bufferElemento2, offsetElemento2);
//	h->guardar_bloque(bufferElemento2,1);
//
//	Elementos* e3 = new Elementos(new Clave("holaaa3"), 203);
//	unsigned int offsetElemento3 = 0;
//	char* bufferElemento3 = (char*)calloc(TAMANIO_BUFFER, sizeof(char));
//	e3->serializar(bufferElemento3, offsetElemento3);
//	h->guardar_bloque(bufferElemento3,2);
//
//	cout << "Grabe todos los bloques" << endl;
//	free(bufferElemento);
//	free(bufferElemento2);
//	free(bufferElemento3);
//	delete(h);
//	delete(e);
//	delete(e2);
//	delete(e3);



////-----------------------------------------------------------------------------
//	HandlerDeBloques* h = new HandlerDeBloques("Archivo_Nodos.txt");
//
//	Elementos* e = new Elementos();
//	unsigned int offsetElemento = 0;
//	char* bufferElemento = (char*)calloc(TAMANIO_BUFFER, sizeof(char));
//	bufferElemento = h->recuperar_bloque(0);
//	e->hidratar(bufferElemento, offsetElemento);
//	e->toString();
//
//	Elementos* e2 = new Elementos();
//	unsigned int offsetElemento2 = 0;
//	char* bufferElemento2 = (char*)calloc(TAMANIO_BUFFER, sizeof(char));
//	bufferElemento2 = h->recuperar_bloque(1);
//	e->hidratar(bufferElemento2, offsetElemento2);
//	e->toString();
//
//	Elementos* e3 = new Elementos();
//	unsigned int offsetElemento3 = 0;
//	char* bufferElemento3 = (char*)calloc(TAMANIO_BUFFER, sizeof(char));
//	bufferElemento3 = h->recuperar_bloque(2);
//	e->hidratar(bufferElemento3, offsetElemento3);
//	e->toString();
//
//	cout << "Recupere todos los bloques" << endl;
//	free(bufferElemento);
//	free(bufferElemento2);
//	free(bufferElemento3);
//	delete(h);
//	delete(e);
//	delete(e2);
//	delete(e3);
//
	ArbolBMas* a = new ArbolBMas(PATH_NODOS, 20);
	int i = 0;
	while (i < 60){
		stringstream ss;
		ss << i;
		string s = ss.str();
		a->insertar(new Elementos(new Clave(s), i+2));
		cout << "Inserte Elemento: " << i << endl;
		++i;
	}


//	a->MostrarArbol();
	delete a;
}
