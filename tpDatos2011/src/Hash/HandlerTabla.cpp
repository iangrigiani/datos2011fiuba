/*
 * HandlerTabla.cpp
 *
 *  Created on: 31/03/2011
 *      Author: angeles
 */

#include "HandlerTabla.h"

HandlerTabla::HandlerTabla() {
	fstream arch;
	string s;
	stringstream ss;

	arch.open (NOM_ARCH_TABLA, fstream::in | fstream::out);
	if (!arch.is_open()) {
	    cout << "Error abriendo el archivo: " << NOM_ARCH_TABLA << endl;
	    return;
	}

	getline(arch, s, '|');
	arch.close();

	ss << s;
	ss >> this->tam_tabla;
}

void HandlerTabla::set_tam_tabla(int tam_tabla) {
	this->tam_tabla = tam_tabla;
}

void HandlerTabla::duplicar_tabla() {
	fstream arch;

	arch.open (NOM_ARCH_TABLA, fstream::in | fstream::out);
	if (!arch.is_open()) {
	    cout << "Error abriendo el archivo: " << NOM_ARCH_TABLA << endl;
	    return;
	}

	string s;
	getline(arch, s, '|');
	s.clear();

	long pos;
	int contador = 0;
	while (contador != this->tam_tabla) {
		arch >> s;
		pos = arch.tellp();
		arch.seekg(0, fstream::end);
		arch << ' ' << s;
		++ contador;
		arch.seekp(pos);
		s.clear();
	}

	this->tam_tabla *= 2;

	stringstream ss;
	ss << this->tam_tabla;
	ss >> s;

	arch.seekg(0, fstream::beg);
	arch.width(4);
	arch << s;

	arch.close();
}

void HandlerTabla::truncar_tabla() {
	ifstream arch;
	ofstream arch_aux;

	arch.open(NOM_ARCH_TABLA);
	if (!arch.is_open()) {
	    cout << "Error abriendo el archivo: " << NOM_ARCH_TABLA << endl;
	    return;
	}

	arch_aux.open(NOM_ARCH_TEMP);
	if (!arch_aux.is_open()) {
	    cout << "Error abriendo el archivo: " << NOM_ARCH_TEMP << endl;
	    return;
	}

	string s;
	getline(arch, s, '|');

	this->tam_tabla /= 2;
	arch_aux.width(4);
	arch_aux << this->tam_tabla << '|';
	s.clear();

	int contador = 0;
	while (contador != this->tam_tabla) {
		arch >> s;
		arch_aux << ' ' << s;
		++ contador;
		s.clear();
	}

	arch.close();
	arch_aux.close();

	remove(NOM_ARCH_TABLA);
	rename(NOM_ARCH_TEMP, NOM_ARCH_TABLA);
}
