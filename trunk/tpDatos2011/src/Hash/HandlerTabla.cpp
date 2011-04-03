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
	getline(arch, s, '|');
	arch.close();

	ss << s;
	ss >> hex >> this->tam_tabla;
}

void HandlerTabla::set_tam_tabla(int tam_tabla) {
	this->tam_tabla = tam_tabla;
}

void HandlerTabla::duplicar_tabla() {
	fstream arch;
	string s;
	long pos;
	int contador = 0;

	arch.open (NOM_ARCH_TABLA, fstream::in | fstream::out);

	getline(arch, s, '|');

	while (contador != this->tam_tabla) {
		arch >> s;
		pos = arch.tellp();
		arch.seekg(0, fstream::end);
		arch << ' ' << s;
		++ contador;
		arch.seekp(pos);
	}

	this->tam_tabla *= 2;

	arch.seekg(0, fstream::beg);
	arch.width(8);
	arch << hex << this->tam_tabla;

	arch.close();
}

void HandlerTabla::truncar_tabla() {
	ifstream arch;
	ofstream arch_aux;
	string s;
	int contador = 0;

	arch.open(NOM_ARCH_TABLA);
	arch_aux.open(NOM_ARCH_TEMP);

	this->tam_tabla /= 2;
	arch_aux.width(8);
	arch_aux << hex << this->tam_tabla << '|';

	getline(arch, s, '|');

	while (contador != this->tam_tabla) {
		arch >> s;
		arch_aux << ' ' << s;
		++ contador;
	}

	arch.close();
	arch_aux.close();

	remove(NOM_ARCH_TABLA);
	rename(NOM_ARCH_TEMP, NOM_ARCH_TABLA);
}

bool HandlerTabla::mitades_iguales() const {
	fstream arch;
	string s, s_aux;
	long pos_1, pos_2;
	int contador = 0;
	bool igual = true;

	arch.open(NOM_ARCH_TABLA, fstream::in | fstream::out);

	getline(arch, s, '|');
	pos_1 = arch.tellp();

	while (contador != this->tam_tabla / 2) {
		arch >> s;
		++ contador;
	}
	pos_2 = arch.tellp();

	contador = 0;
	arch.seekp(pos_1);
	while (contador != this->tam_tabla / 2 && igual == true) {
		arch >> s;
		pos_1 = arch.tellp();

		arch.seekp(pos_2);
		arch >> s_aux;
		pos_2 = arch.tellp();

		if (s.compare(s_aux) != 0)
			igual = false;

		++ contador;
		arch.seekp(pos_1);
	}

	arch.close();

	return igual;
}

int HandlerTabla::get_num_bloque(int clave) const {
	fstream arch;
	string s;
	int num_bloque;
	int contador = 0;

	arch.open(NOM_ARCH_TABLA, fstream::in | fstream::out);

	getline(arch, s, '|');

	while (contador != clave % this->tam_tabla + 1) {
		arch >> s;
		++ contador;
	}

	stringstream ss;
	ss << s;
	ss >> num_bloque;

	return num_bloque;
}

void HandlerTabla::reemplazar_referencia(const Bloque_Hash& bloque_a_reemplazar, const Bloque_Hash& nuevo_bloque) {
	ifstream arch;
	ofstream arch_aux;
	string s;
	int num_bloque;
	bool encontrado = false;
	int contador = 0;

	arch.open(NOM_ARCH_TABLA);
	arch_aux.open(NOM_ARCH_TEMP);

	arch_aux.width(8);
	arch_aux << hex << this->tam_tabla << '|';

	getline(arch, s, '|');

	while (contador != this->tam_tabla && encontrado == false) {
		arch >> s;

		stringstream ss;
		ss << s;
		ss >> num_bloque;

		if (num_bloque == bloque_a_reemplazar.get_pos_arch()) {
			encontrado = true;
			arch_aux << ' ' << dec << nuevo_bloque.get_pos_arch();
		}
		else arch_aux << ' ' << dec << num_bloque;

		++ contador;
	}

	while (contador != this->tam_tabla) {
		arch >> s;
		arch_aux << ' ' << s;
		++ contador;
	}

	arch.close();
	arch_aux.close();

	remove(NOM_ARCH_TABLA);
	rename(NOM_ARCH_TEMP, NOM_ARCH_TABLA);
}

void HandlerTabla::reemplazar_referencias(int pos_inicial, const Bloque_Hash& nuevo_bloque) {
	ifstream arch;
	ofstream arch_aux;
	string s;
	int contador = this->tam_tabla - pos_inicial;
	int dist_salto = contador;

	arch.open(NOM_ARCH_TABLA);
	arch_aux.open(NOM_ARCH_TEMP);

	arch_aux.width(8);
	arch_aux << hex << this->tam_tabla << '|';

	getline(arch, s, '|');

	while (contador - this->tam_tabla + pos_inicial != this->tam_tabla) {
		arch >> s;

		if (dist_salto == nuevo_bloque.get_tam_dispersion()) {
			arch_aux << ' ' << dec << nuevo_bloque.get_pos_arch();
			dist_salto = 0;
		}
		else arch_aux << ' ' << s;

		++ contador;
		++ dist_salto;
	}

	arch.close();
	arch_aux.close();

	remove(NOM_ARCH_TABLA);
	rename(NOM_ARCH_TEMP, NOM_ARCH_TABLA);
}

bool HandlerTabla::puedo_liberar_bloque(const Bloque_Hash& bloque_a_liberar, int pos_actual, int* bloque_a_reemplazar) const {
	fstream arch;
	string s;
	stringstream ss_1, ss_2;
	int bloque_anterior, bloque_siguiente, pos_anterior, pos_siguiente;
	int contador = 0;

	arch.open(NOM_ARCH_TABLA, fstream::in | fstream::out);

	getline(arch, s, '|');

	pos_anterior = pos_actual - bloque_a_liberar.get_tam_dispersion() / 2 + 1;
	if (pos_anterior <= 0)
		pos_anterior += this->tam_tabla;

	pos_siguiente = pos_actual + bloque_a_liberar.get_tam_dispersion() / 2 + 1;
	if (pos_siguiente > this->tam_tabla)
		pos_siguiente -= this->tam_tabla;

	if (pos_anterior < pos_siguiente) {
		while (contador != pos_anterior) {
			arch >> s;
			++ contador;
		}
		ss_1 << s;
		ss_1 >> bloque_anterior;

		while (contador != pos_siguiente) {
			arch >> s;
			++ contador;
		}
		ss_2 << s;
		ss_2 >> bloque_siguiente;
	}
	else {
		while (contador != pos_siguiente) {
			arch >> s;
			++ contador;
		}
		ss_1 << s;
		ss_1 >> bloque_siguiente;

		while (contador != pos_anterior) {
			arch >> s;
			++ contador;
		}
		ss_2 << s;
		ss_2 >> bloque_anterior;
	}

	if (bloque_anterior == bloque_siguiente) {
		*bloque_a_reemplazar = bloque_anterior;
		return true;
	}
	bloque_a_reemplazar = NULL;
	return false;
}

void HandlerTabla::liberar_referencias(int pos_inicial, const Bloque_Hash& bloque_por_reemplazar) {
	this->reemplazar_referencias(pos_inicial, bloque_por_reemplazar);
}
