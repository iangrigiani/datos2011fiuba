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
#include "ModuloDePersistencia/EscritorBloques.h"
#include "ModuloDePersistencia/RecuperadorBloques.h"
#include "ArbolB+/ArbolBMas.h"

int main() {
	ClaveNumerica* clave1 = new ClaveNumerica(12);
//	ClaveNumerica* clave2 = new ClaveNumerica(1234);
//	ClaveNumerica* clave3 = new ClaveNumerica(2354);
	ArbolBMas* arbol = new ArbolBMas("Arbol.txt", 10);
	Registro* reg1 = new Registro("uccello", clave1->getValorClave());
//	Registro* reg2 = new Registro("Sorian", clave2->getValorClave());
//	Registro* reg3 = new Registro("Pretorian", clave3->getValorClave());


	EscritorBloques* w = new EscritorBloques("salidaBloqques.txt");
	int offset = w->getOffset();
	arbol->insertar(reg1, offset);
	w->GrabarRegistro(reg1);
	arbol->MostrarArbol();
//
//	offset = w->getOffset();
//	arbol->insertar(reg2, offset);
//	w->GrabarRegistro(reg2);
//
//
//	offset = w->getOffset();
//	arbol->insertar(reg3, offset);
//	w->GrabarRegistro(reg3);

	w->GrabarBloqueEnArchivo();
	delete w;

	arbol->MostrarArbol();
//	RecuperadorBloques* r = new RecuperadorBloques("salidaBloqques.txt");
//	Registro* registro = r->getRegistro(new ClaveNumerica(1234567), 0);
//	registro->toString();

}
