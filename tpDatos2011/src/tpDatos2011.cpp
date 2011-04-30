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
#include "ManejadoresDeArchivos/HandlerBloques.h"
#include "ManejadoresDeArchivos/HandlerBloques.h"
#include "ParserLibros/ParserDeLibros.h"
#include "ArbolB+/ArbolBMas.h"
int main(int argc, char **argv) {
	ArbolBMas* a = new ArbolBMas(1, PATH_ARBOL);
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
	delete a;
}
