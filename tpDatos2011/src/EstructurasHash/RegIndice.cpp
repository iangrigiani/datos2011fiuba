/*
 * Registro_Hash.cpp
 *
 *  Created on: 31/03/2011
 *      Author: angeles
 */

#include "RegIndice.h"

RegIndice::RegIndice() : clave(-1), bloque_sig(-1) {}

RegIndice::RegIndice(int clave) : clave(clave), bloque_sig(-1) {}

void RegIndice::set_clave(int clave) {
	this->clave = clave;
}

void RegIndice::set_bloque_sig(int bloque_sig) {
	this->bloque_sig = bloque_sig;
}

void RegIndice::set_elementos(const list < Elemento > & elementos) {
	this->elementos = elementos;
}

bool RegIndice::esta_vacio() {
	list < Elemento > ::iterator it;

	for (it = this->elementos.begin(); it != this->elementos.end(); ++ it) {
		if ((*it).get_offsets().empty() != true)
			return false;
	}
	return true;
}

int RegIndice::get_tam() {
	int acum = sizeof(this->clave) + sizeof(this->bloque_sig);
	list < Elemento > ::iterator it;
	for (it = this->elementos.begin(); it != this->elementos.end(); ++ it)
		acum += (*it).get_tam();
	return acum;
}

void RegIndice::agregar_nuevo_elemento(const Elemento& elemento) {
	this->elementos.push_back(elemento);
}

int RegIndice::eliminar_elemento(const string& cadena) {
	list < Elemento > ::iterator it;

	it = this->elementos.begin();
	while (it != this->elementos.end() && cadena.compare((*it).get_cadena()) != 0)
		++ it;

	if (cadena.compare((*it).get_cadena()) == 0) {
		this->elementos.erase(it);
		return true;
	}
	return false;
}

bool RegIndice::existe_elemento(const string& cadena) {
	list < Elemento > ::iterator it;

	it = this->elementos.begin();
	while (it != this->elementos.end() && cadena.compare((*it).get_cadena()) != 0)
		++ it;

	if (cadena.compare((*it).get_cadena()) == 0)
		return true;
	return false;
}

Elemento& RegIndice::buscar_elemento(const string& cadena) {
	list < Elemento > ::iterator it;

	it = this->elementos.begin();
	while (cadena.compare((*it).get_cadena()) != 0)
		++ it;

	return *it;
}

void RegIndice::serializar(char* buffer, unsigned int& offset) {
	Persistencia::PonerEnteroEnChar(buffer, offset, this->clave);
	Persistencia::PonerEnteroEnChar(buffer, offset, this->bloque_sig);

	Persistencia::PonerEnteroEnChar(buffer, offset, this->elementos.size());
	list < Elemento > ::iterator it;
	for (it = this->elementos.begin(); it != this->elementos.end(); ++ it)
		(*it).serializar(buffer, offset);
}

void RegIndice::hidratar(char* buffer, unsigned int& offset) {
	this->clave = Persistencia::getEnteroDesdeBuffer(buffer, offset);
	this->bloque_sig = Persistencia::getEnteroDesdeBuffer(buffer, offset);

	int tam_offsets = Persistencia::getEnteroDesdeBuffer(buffer, offset);
	for (int i = 0; i < tam_offsets; ++ i) {
		Elemento elemento;
		elemento.hidratar(buffer, offset);
		this->elementos.push_back(elemento);
	}
}

void RegIndice::toString() {
	cout << " Registro --> " << endl;
	cout << " Clave:   " << this->clave << endl;
	cout << " Bloque siguiente:   " << this->bloque_sig << endl;

	list < Elemento > ::iterator it;
	for (it = this->elementos.begin(); it != this->elementos.end(); ++ it)
		(*it).toString();

	cout << " Tamaño ocupado:   " << this->get_tam() << " Bytes" << endl;
}
