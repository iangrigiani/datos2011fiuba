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

int main() {
//	ClaveNumerica* clave1 = new ClaveNumerica(1234567);
//	ClaveNumerica* clave2 = new ClaveNumerica(1234567);
//	Registro* reg1 = new Registro("uccello", clave1->getValorClave());
//	Registro* reg2 = new Registro("Sorian", clave2->getValorClave());
//
//	cout << "Los registros agregados son: " << endl;
//	reg1->toString();
//	reg2->toString();
//
//	EscritorBloques* w = new EscritorBloques("salidaBloqques.txt");
//	w->GrabarRegistro(reg1);
//	w->GrabarRegistro(reg2);
//	w->GrabarBloqueEnArchivo();
//	delete w;

	RecuperadorBloques* r = new RecuperadorBloques("salidaBloqques.txt");
	Registro* registro = r->getRegistro(new ClaveNumerica(1234567), 0);
	registro->toString();

}
