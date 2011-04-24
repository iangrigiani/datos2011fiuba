/*
 * RegTitulo.cpp
 *
 *  Created on: 21/04/2011
 *      Author: angeles
 */

#include "RegTitulo.h"


int RegTitulo::get_tam() const {
	return (sizeof(clave) + sizeof(offset));
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
