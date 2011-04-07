/*
 * Registro_Hash.cpp
 *
 *  Created on: 31/03/2011
 *      Author: angeles
 */

#include "Reg.h"

Reg::Reg() : clave(0) {}

Reg::Reg(int clave) : clave(clave) {}

void Reg::agregar_nuevo_offset(int offset) {
	this->offsets.push_back(offset);
}

bool Reg::eliminar_offset(int offset) {
	list < int > ::iterator it;

	it = this->offsets.begin();
	while (it != this->offsets.end() && *it != offset)
		++ it;

	if (*it == offset) {
		this->offsets.erase(it);
		return true;
	}
	return false;
}

int Reg::get_tam() const {
	return (sizeof(int) + this->offsets.size() * sizeof(int));
}

void Reg::serializar(char* buffer, unsigned int& offset) {
	Persistencia::PonerEnteroEnChar(buffer, offset, this->clave);

	Persistencia::PonerEnteroEnChar(buffer, offset, this->offsets.size());
	list < int > ::iterator it;
	for (it = this->offsets.begin(); it != this->offsets.end(); ++ it)
		Persistencia::PonerEnteroEnChar(buffer, offset, (*it));
}

void Reg::hidratar(char* buffer, unsigned int& offset) {
	this->clave = Persistencia::getEnteroDesdeBuffer(buffer, offset);

	int tam_offsets = Persistencia::getEnteroDesdeBuffer(buffer, offset);
	for (int i = 0; i < tam_offsets; ++ i)
		this->offsets.push_back(Persistencia::getEnteroDesdeBuffer(buffer,offset));
}

void Reg::toString() {
	cout << " Registro --> " << endl;
	cout << " Clave:   " << this->clave << endl;
	cout << " Tamaño ocupado:   " << this->get_tam() << " Bytes" << endl;

	list < int > ::iterator it;
	int i = 0;
	for (it = this->offsets.begin(); it != this->offsets.end(); ++ it) {
		cout << " Offset #" << i << ":   " << *it << endl;
		++ i;
	}
}
