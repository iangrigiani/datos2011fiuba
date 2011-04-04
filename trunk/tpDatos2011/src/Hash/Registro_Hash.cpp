/*
 * Registro_Hash.cpp
 *
 *  Created on: 31/03/2011
 *      Author: angeles
 */

#include "Registro_Hash.h"

Registro_Hash::Registro_Hash(int clave) : clave(clave) {}

void Registro_Hash::agregar_nuevo_offset(int offset) {
	this->offsets.push_back(offset);
}

bool Registro_Hash::eliminar_offset(int offset) {
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

int Registro_Hash::obtener_tam() const {
	return (sizeof(int) + this->offsets.size() * sizeof(int));
}

void Registro_Hash::serializar(char* buffer, unsigned int& offset) {
	Persistencia::PonerEnteroEnChar(buffer, offset, this->clave);

	Persistencia::PonerEnteroEnChar(buffer, offset, this->offsets.size());
	list < int > ::iterator it;
	for (it = this->offsets.begin(); it != this->offsets.end(); ++ it)
		Persistencia::PonerEnteroEnChar(buffer, offset, (*it));
}

void Registro_Hash::hidratar(char* buffer, unsigned int& offset) {
	this->clave = Persistencia::getEnteroDesdeBuffer(buffer, offset);

	int tam_offsets = Persistencia::getEnteroDesdeBuffer(buffer, offset);
	for (int i = 0; i < tam_offsets; ++ i)
		this->offsets.push_back(Persistencia::getEnteroDesdeBuffer(buffer,offset));
}

void Registro_Hash::toString() {
	cout << " Registro de Hash --> " << endl;
	cout << " Clave:   " << this->clave << endl;
	cout << " Tamaño ocupado:   " << this->obtener_tam() << endl;

	list < int > ::iterator it;
	int i = 0;
	for (it = this->offsets.begin(); it != this->offsets.end(); ++ it) {
		cout << " Offset #" << i << ":   " << *it << endl;
		++ i;
	}
}
