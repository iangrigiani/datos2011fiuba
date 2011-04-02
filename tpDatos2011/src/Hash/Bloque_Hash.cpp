/*
 * Bloque_Hash.cpp
 *
 *  Created on: 31/03/2011
 *      Author: angeles
 */

#include "Bloque_Hash.h"

Bloque_Hash::Bloque_Hash(int pos_arch, int tam_dispersion) :
	pos_arch(pos_arch), tam_dispersion(tam_dispersion), espacio_libre(TAM_BLOQUE) {}

bool Bloque_Hash::esta_vacio() const {
	if (this->espacio_libre == TAM_BLOQUE)
		return true;
	return false;
}

bool Bloque_Hash::entra_en_bloque(const Registro_Hash& reg) const {
	if (this->espacio_libre > reg.obtener_tam())
		return true;
	return false;
}

void Bloque_Hash::agregar_nueva_pos(int pos) {
	this->pos_tabla.push_back(pos);
}

bool Bloque_Hash::eliminar_pos(int pos) {
	list < int > ::iterator it;

	it = this->pos_tabla.begin();
	while (it != this->pos_tabla.end() && *it != pos)
		++ it;

	if (*it == pos) {
		this->pos_tabla.erase(it);
		return true;
	}
	return false;
}

void Bloque_Hash::agregar_nuevo_reg(const Registro_Hash& reg) {
	this->regs.push_back(reg);
}

bool Bloque_Hash::eliminar_reg(int clave) {
	list < Registro_Hash > ::iterator it;

	it = this->regs.begin();
	while (it != this->regs.end() && (*it).get_clave() != clave)
		++ it;

	if ((*it).get_clave() == clave) {
		this->regs.erase(it);
		return true;
	}
	return false;
}

bool Bloque_Hash::agregar_nuevo_offset_a_reg(int clave, int offset) {
	list < Registro_Hash > ::iterator it;

	it = this->regs.begin();
	while (it != this->regs.end() && (*it).get_clave() != clave)
		++ it;

	if ((*it).get_clave() == clave) {
		(*it).agregar_nuevo_offset(offset);
		return true;
	}
	return false;
}

int Bloque_Hash::eliminar_offset_de_reg(int clave, int offset) {
	list < Registro_Hash > ::iterator it;

	it = this->regs.begin();
	while (it != this->regs.end() && (*it).get_clave() != clave)
		++ it;

	if ((*it).get_clave() == clave) {
		if ((*it).eliminar_offset(offset) == true)
			return 0;
		return 1;
	}
	return 2;
}

list < Registro_Hash > Bloque_Hash::actualizar_regs(int tam_tabla) {
	list < Registro_Hash > ::iterator it_1;
	list < int > ::iterator it_2;
	list < Registro_Hash > list_aux;
	Registro_Hash reg_aux(0);
	int resto;

	for (it_1 = this->regs.begin(); it_1 != this->regs.end(); ++ it_1) {
		resto = (*it_1).get_clave() % tam_tabla;

		it_2 = this->pos_tabla.begin();
		while (it_2 != this->pos_tabla.end() && *it_2 != resto)
			++ it_2;

		if (*it_2 != resto && it_2 == this->pos_tabla.end()) {
			reg_aux = *it_1;
			this->regs.erase(it_1);
			list_aux.push_back(reg_aux);
		}
	}
	return list_aux;
}

void Bloque_Hash::incorporar_regs(list < Registro_Hash > regs) {
	this->regs = regs;
}
