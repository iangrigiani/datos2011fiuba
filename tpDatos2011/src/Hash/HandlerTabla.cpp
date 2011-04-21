/*
 * HandlerTabla.cpp
 *
 *  Created on: 31/03/2011
 *      Author: angeles
 */

#include "HandlerTabla.h"

HandlerTabla::HandlerTabla() {
	ifstream arch;
	string s;
	stringstream ss;

	arch.open(NOM_ARCH_TABLA);
	getline(arch, s, '|');
	arch.close();

	ss << s;
	ss >> hex >> this->tam_tabla;
}

bool HandlerTabla::tabla_vacia() {
	ifstream arch;
	string s;
	stringstream ss;

	arch.open(NOM_ARCH_TABLA);
	getline(arch, s, '|');
	arch.close();

	ss << s;
	ss >> hex >> this->tam_tabla;
	if (this->tam_tabla == 0)
		return true;

	return false;
}

void HandlerTabla::crear_tabla_inicial(int num_bloque) {
	fstream arch;
	string s;
	stringstream ss;

	this->tam_tabla = 1;

	arch.open(NOM_ARCH_TABLA, fstream::in | fstream::out);

	arch.width(8);
	arch << hex << this->tam_tabla << '|';
	arch << ' ' << dec << num_bloque;

	arch.close();
}

void HandlerTabla::duplicar_tabla() {
	fstream arch;
	string s;
	long pos;
	int contador = 0;

	arch.open(NOM_ARCH_TABLA, fstream::in | fstream::out);

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
	if (this->tam_tabla < 0)
		this->tam_tabla = 0;
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

	arch.open(NOM_ARCH_TABLA, fstream::in);

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

int HandlerTabla::get_num_bloque(int clave, int& pos_tabla) const {
	ifstream arch;
	string s;
	int num_bloque;
	int contador = 0;

	arch.open(NOM_ARCH_TABLA);

	getline(arch, s, '|');

	while (contador != clave % this->tam_tabla) {
		arch >> num_bloque;
		++ contador;
	}

	arch >> num_bloque;
	pos_tabla = contador;

	return num_bloque;
}

list < Reg > HandlerTabla::actualizar_regs(int num_bloque, Cubo& bloque) {
	list < Reg > ::iterator it;
	list < Reg > list_aux;
	Reg reg_desact;
	int pos_tabla;
	unsigned int tam_regs;
	unsigned int contador = 0;

	tam_regs = bloque.get_regs().size();
	it = bloque.get_regs().begin();

	while (contador != tam_regs) {
		if (num_bloque != this->get_num_bloque((*it).get_clave(), pos_tabla)) {
			reg_desact = *it;
			it = bloque.get_regs().erase(it);
			bloque.aumentar_esp_libre(reg_desact.get_tam());
			list_aux.push_back(reg_desact);
		}
		else ++ it;
		++ contador;
	}

	return list_aux;
}

void HandlerTabla::reemplazar_referencia(int num_bloque_a_reemplazar, int num_nuevo_bloque) {
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
		arch >> num_bloque;

		if (num_bloque == num_bloque_a_reemplazar) {
			encontrado = true;
			arch_aux << ' ' << dec << num_nuevo_bloque;
		}
		else arch_aux << ' ' << dec << num_bloque;

		++ contador;
	}

	while (contador != this->tam_tabla) {
		arch >> num_bloque;
		arch_aux << ' ' << dec << num_bloque;
		++ contador;
	}

	arch.close();
	arch_aux.close();

	remove(NOM_ARCH_TABLA);
	rename(NOM_ARCH_TEMP, NOM_ARCH_TABLA);
}

void HandlerTabla::reemplazar_referencias(int pos_inicial, int num_nuevo_bloque, const Cubo& nuevo_bloque) {
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

		if (dist_salto == nuevo_bloque.get_tam_disp()) {
			arch_aux << ' ' << dec << num_nuevo_bloque;
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

int HandlerTabla::puedo_liberar_bloque(const Cubo& bloque_a_liberar, int pos_actual) const {
	ifstream arch;
	string s;
	int bloque_anterior, bloque_siguiente, pos_anterior, pos_siguiente;
	int contador = 0;

	arch.open(NOM_ARCH_TABLA);

	getline(arch, s, '|');

	pos_anterior = pos_actual - bloque_a_liberar.get_tam_disp() / 2 + 1;
	if (pos_anterior <= 0)
		pos_anterior += this->tam_tabla;

	pos_siguiente = pos_actual + bloque_a_liberar.get_tam_disp() / 2 + 1;
	if (pos_siguiente > this->tam_tabla)
		pos_siguiente -= this->tam_tabla;

	if (pos_anterior < pos_siguiente) {
		while (contador != pos_anterior) {
			arch >> bloque_anterior;
			++ contador;
		}
		while (contador != pos_siguiente) {
			arch >> bloque_siguiente;
			++ contador;
		}
	}
	else {
		if (pos_anterior < pos_siguiente) {
			while (contador != pos_siguiente) {
				arch >> bloque_siguiente;
				++ contador;
			}
			while (contador != pos_anterior) {
				arch >> bloque_anterior;
				++ contador;
			}
		}
		else {
			while (contador != pos_anterior) {
				arch >> bloque_anterior;
				++ contador;
			}
		}
	}

	if (bloque_anterior == bloque_siguiente || pos_anterior == pos_siguiente)
		return bloque_anterior;
	return -1;
}

void HandlerTabla::liberar_referencias(int pos_inicial, int num_bloque_por_reemplazar,
		const Cubo& bloque_por_reemplazar) {
	this->reemplazar_referencias(pos_inicial, num_bloque_por_reemplazar, bloque_por_reemplazar);
}
