/*
 * Bloque_Hash.cpp
 *
 *  Created on: 31/03/2011
 *      Author: angeles
 */

#include "Bloq.h"

Bloq::Bloq() : pos_bloque_aux(-1), espacio_libre(TAM_BLOQUE) {}

void Bloq::set_pos_bloque_aux(int pos_bloque_aux) {
	this->pos_bloque_aux = pos_bloque_aux;
}

bool Bloq::esta_vacio() const {
	if (this->espacio_libre == TAM_BLOQUE)
		return true;
	return false;
}

bool Bloq::entra_en_bloque(const Reg& reg) const {
	if (this->espacio_libre > reg.get_tam())
		return true;
	return false;
}

void Bloq::agregar_nuevo_reg(const Reg& reg) {
	this->regs.push_back(reg);
	this->espacio_libre -= reg.get_tam();
}

bool Bloq::eliminar_reg(int clave) {
	list < Reg > ::iterator it;

	it = this->regs.begin();
	while (it != this->regs.end() && (*it).get_clave() != clave)
		++ it;

	if ((*it).get_clave() == clave) {
		this->regs.erase(it);
		this->espacio_libre += (*it).get_tam();
		return true;
	}
	return false;
}

bool Bloq::agregar_nuevo_offset_a_reg(int clave, int offset) {
	list < Reg > ::iterator it;

	it = this->regs.begin();
	while (it != this->regs.end() && (*it).get_clave() != clave)
		++ it;

	if ((*it).get_clave() == clave) {
		(*it).agregar_nuevo_offset(offset);
		this->espacio_libre -= (*it).get_tam();
		return true;
	}
	return false;
}

int Bloq::eliminar_offset_de_reg(int clave, int offset) {
	list < Reg > ::iterator it;

	it = this->regs.begin();
	while (it != this->regs.end() && (*it).get_clave() != clave)
		++ it;

	if ((*it).get_clave() == clave) {
		if ((*it).eliminar_offset(offset) == true) {
			this->espacio_libre += (*it).get_tam();
			return 0;
		}
		return 1;
	}
	return 2;
}

void Bloq::vaciar() {
	this->pos_bloque_aux = -1;
	this->espacio_libre = TAM_BLOQUE;
	this->regs.clear();
}

void Bloq::serializar(char* buffer, unsigned int& offset) {
	Persistencia::PonerEnteroEnChar(buffer, offset, this->pos_bloque_aux);

	Persistencia::PonerEnteroEnChar(buffer, offset, this->regs.size());
	list < Reg > ::iterator it;
	for (it = this->regs.begin(); it != this->regs.end(); ++ it)
		(*it).serializar(buffer, offset);
}

void Bloq::hidratar(char* buffer, unsigned int& offset) {
	this->pos_bloque_aux = Persistencia::getEnteroDesdeBuffer(buffer, offset);

	int tam_regs = Persistencia::getEnteroDesdeBuffer(buffer, offset);
	for (int i = 0; i < tam_regs; ++ i) {
		Reg reg;
		reg.hidratar(buffer, offset);
		this->regs.push_back(reg);
		this->espacio_libre -= this->regs.back().get_tam();
	}
}

void Bloq::toString() {
	cout << " Bloque --> " << endl;
	cout << " Apunta al bloque N°:   " << this->pos_bloque_aux << endl;
	cout << " Cantidad de espacio libre:   " << this->espacio_libre << endl;

	list < Reg > ::iterator it;
	for (it = this->regs.begin(); it != this->regs.end(); ++ it)
		(*it).toString();
}
