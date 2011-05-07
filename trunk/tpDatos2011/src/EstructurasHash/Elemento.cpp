/*
 * Elemento.cpp
 *
 *  Created on: 03/05/2011
 *      Author: angeles
 */

#include "Elemento.h"

Elemento::Elemento(const string& cadena, const list < int > & offsets) : cadena(cadena), offsets(offsets) {}

void Elemento::set_cadena(const string& cadena) {
	this->cadena = cadena;
}

void Elemento::set_offsets(const list < int > & offsets) {
	this->offsets = offsets;
}

int Elemento::get_tam() {
//	int tam = this->cadena.size() + sizeof(' ');
	int tam = strlen(this->cadena.c_str());
//	stringstream ss;
//	ss << this->offsets.size() << ' ';
//	string s(ss.str());
//	tam += s.size();
//	s.clear();

//	list < int > ::iterator it;
//	for (it = this->offsets.begin(); it != this->offsets.end(); ++ it) {
//		stringstream ss;
//		ss << *it << ' ';
//		s = ss.str();
//		tam += s.size();
//		s.clear();
//		tam += sizeof(int);
//	}
	tam += (this->offsets.size()*sizeof(int) + this->offsets.size()*sizeof(char));
	return tam;
}

void Elemento::agregar_nuevos_offsets(list < int > & offsets) {
	list < int > ::iterator it;
	for (it = offsets.begin(); it != offsets.end(); ++ it)
		this->offsets.push_back(*it);
}

bool Elemento::eliminar_offset(int offset) {
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

void Elemento::serializar(char* buffer, unsigned int& offset) {
//	int size = this->cadena.size();
//	char* aux = (char*) malloc (sizeof(char) * (size + 1));
//	this->cadena.copy(aux, size);
//	aux[size] = '\0';
	Persistencia::PonerStringEnChar(buffer, offset,(char*)this->cadena.c_str());
//	free(aux);

	Persistencia::PonerEnteroEnChar(buffer, offset, this->offsets.size());
	list < int > ::iterator it;
	for (it = this->offsets.begin(); it != this->offsets.end(); ++ it)
		Persistencia::PonerEnteroEnChar(buffer, offset, (*it));
}

void Elemento::hidratar(char* buffer, unsigned int& offset) {
	this->cadena = Persistencia::getStringDesdeBuffer(buffer, offset);

	int tam_offsets = Persistencia::getEnteroDesdeBuffer(buffer, offset);
	for (int i = 0; i < tam_offsets; ++ i)
		this->offsets.push_back(Persistencia::getEnteroDesdeBuffer(buffer,offset));
}

void Elemento::toString() {
	cout << " Elemento --> " << endl;
	cout << " Cadena:   " << this->cadena << endl;
	cout << " Tamaño ocupado:   " << this->get_tam() << " Bytes" << endl;
/*
	list < int > ::iterator it;
	int i = 0;
	for (it = this->offsets.begin(); it != this->offsets.end(); ++ it) {
		cout << " Offset #" << i << ":   " << *it << endl;
		++ i;
	}
*/
}
