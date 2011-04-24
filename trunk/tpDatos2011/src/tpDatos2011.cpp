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


void llenarArbol(ArbolBMas* a){
		int i = 0;
		while (i < 50){
			stringstream ss;
			ss << "casa" << i;
			string s = ss.str();
			a->insertar(new Elementos(new Clave(s), 0));
			cout << "Inserte Elemento: " << i << endl;
			++i;
		}

		a->MostrarArbol();
}
void limpiarArchivos(){
	fstream ff ;
	ff.open(PATH_CONFIGURACION_AUTORES, ios_base::out);
	ff.close();

	ff.open(PATH_CONFIGURACION_EDITORIAL, ios_base::out);
	ff.close();

	ff.open(PATH_NODOS, ios_base::out);
	ff.close();

	ff.open(PATH_FRONT_CODING, ios_base::out);
	ff.close();

	ff.open(PATH_ARBOL, ios_base::out);
	ff.close();
}

void borrarNodos(ArbolBMas *a){

	a->MostrarArbol();
	Clave * clave;
	clave = new Clave("26");
	a->borrar(*clave);
	delete clave;
	cout << "Borro la clave 26" << endl;
	a->MostrarArbol();

	clave = new Clave("27");
	a->borrar(*clave);
	delete clave;
	cout << "Borro la clave 27" << endl;

	a->MostrarArbol();


//	clave = new Clave("45");
//	a->borrar(*clave);
//	delete clave;
//	cout << "Borro la clave 45" << endl;
//	a->MostrarArbol();
//
//
//	clave = new Clave("52");
//	a->borrar(*clave);
//	delete clave;
//	cout << "Borro la clave 52" << endl;
//	a->MostrarArbol();
//
//
//	clave = new Clave("0");
//	a->borrar(*clave);
//	delete clave;
//	cout << "Borro la clave 0" << endl;
//	a->MostrarArbol();


}

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
	limpiarArchivos();
	ArbolBMas* a = new ArbolBMas(1, PATH_ARBOL, 20);

	llenarArbol(a);
	//borrarNodos(a);


	delete a;
}
