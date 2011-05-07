/*
 * RegTitulo.cpp
 *
 *  Created on: 21/04/2011
 *      Author: angeles
 */

#include "RegTitulo.h"

int RegTitulo::get_tam() const {

	int tam = 0;

	stringstream ss1;
	ss1 << this->clave << ' ';
	string s(ss1.str());
	tam += s.size();
	s.clear();

	stringstream ss2;
	ss2 << this->offset << ' ';
	s = ss2.str();
	tam += s.size();
	s.clear();

	return tam;
}

void RegTitulo::serializar(char* buffer, unsigned int& offset) {
	Persistencia::PonerEnteroEnChar(buffer, offset, this->clave);
	Persistencia::PonerEnteroEnChar(buffer, offset, this->offset);
}

void RegTitulo::hidratar(char* buffer, unsigned int& offset) {
	this->clave = Persistencia::getEnteroDesdeBuffer(buffer, offset);
	this->offset = Persistencia::getEnteroDesdeBuffer(buffer, offset);
}

void RegTitulo::toString() {
	cout << " Registro de titulo --> " << endl;
	cout << " Clave:   " << this->clave << endl;
	cout << " Offset:   " << this->offset << endl;
}
