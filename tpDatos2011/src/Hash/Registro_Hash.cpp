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
