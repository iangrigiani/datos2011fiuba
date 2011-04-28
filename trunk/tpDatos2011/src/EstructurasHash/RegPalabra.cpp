/*
 * Registro_Hash.cpp
 *
 *  Created on: 31/03/2011
 *      Author: angeles
 */

#include "RegPalabra.h"

int RegPalabra::get_tam() const {
	return (sizeof(int) + sizeof(int) + this->offsets.size() * sizeof(int));
}

void RegPalabra::set_bloque_sig(int bloque_sig) {
	this->bloque_sig = bloque_sig;
}

void RegPalabra::set_offsets(list < int > & offsets) {
	this->offsets = offsets;
}

void RegPalabra::agregar_nuevos_offsets(list < int > & offsets) {
	list < int > ::iterator it;
	for (it = offsets.begin(); it != offsets.end(); ++ it)
		this->offsets.push_back(*it);
}

bool RegPalabra::eliminar_offset(int offset) {
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

void RegPalabra::serializar(char* buffer, unsigned int& offset) {
	Persistencia::PonerEnteroEnChar(buffer, offset, this->clave);
	Persistencia::PonerEnteroEnChar(buffer, offset, this->bloque_sig);

	Persistencia::PonerEnteroEnChar(buffer, offset, this->offsets.size());
	list < int > ::iterator it;
	for (it = this->offsets.begin(); it != this->offsets.end(); ++ it)
		Persistencia::PonerEnteroEnChar(buffer, offset, (*it));
}

void RegPalabra::hidratar(char* buffer, unsigned int& offset) {
	this->clave = Persistencia::getEnteroDesdeBuffer(buffer, offset);
	this->bloque_sig = Persistencia::getEnteroDesdeBuffer(buffer, offset);

	int tam_offsets = Persistencia::getEnteroDesdeBuffer(buffer, offset);
	for (int i = 0; i < tam_offsets; ++ i)
		this->offsets.push_back(Persistencia::getEnteroDesdeBuffer(buffer,offset));
}

void RegPalabra::toString() {
	cout << " Registro --> " << endl;
	cout << " Clave:   " << this->clave << endl;
	cout << " Bloque siguiente:   " << this->bloque_sig << endl;
	cout << " Tamaño ocupado:   " << this->get_tam() << " Bytes" << endl;

/*	list < int > ::iterator it;
	int i = 0;
	for (it = this->offsets.begin(); it != this->offsets.end(); ++ it) {
		cout << " Offset #" << i << ":   " << *it << endl;
		++ i;
	}
*/
}

void RegPalabra::agregar_nuevo_offset(int offset) {
	this->offsets.push_back(offset);
}
