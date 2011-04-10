/*
 * Bloque_Hash.cpp
 *
 *  Created on: 31/03/2011
 *      Author: angeles
 */

#include "Bloq.h"

Bloq::Bloq() : pos_bloque_aux(-1), esp_libre(TAM_BLOQUE) {}

void Bloq::set_pos_bloque_aux(int pos_bloque_aux) {
	this->pos_bloque_aux = pos_bloque_aux;
}

bool Bloq::esta_vacio() const {
	if (this->esp_libre == TAM_BLOQUE)
		return true;
	return false;
}

bool Bloq::entra_en_bloque(const Reg& reg) const {
	if (this->esp_libre > reg.get_tam())
		return true;
	return false;
}

void Bloq::agregar_nuevo_reg(const Reg& reg) {
	this->regs.push_back(reg);
	this->esp_libre -= reg.get_tam();
}

bool Bloq::eliminar_reg(int clave) {
	list < Reg > ::iterator it;

	it = this->regs.begin();
	while (it != this->regs.end() && (*it).get_clave() != clave)
		++ it;

	if ((*it).get_clave() == clave) {
		this->regs.erase(it);
		this->esp_libre += (*it).get_tam();
		return true;
	}
	return false;
}

void Bloq::vaciar() {
	this->pos_bloque_aux = -1;
	this->esp_libre = TAM_BLOQUE;
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
	this->vaciar();
	this->pos_bloque_aux = Persistencia::getEnteroDesdeBuffer(buffer, offset);

	int tam_regs = Persistencia::getEnteroDesdeBuffer(buffer, offset);
	for (int i = 0; i < tam_regs; ++ i) {
		Reg reg;
		reg.hidratar(buffer, offset);
		this->agregar_nuevo_reg(reg);
	}
}

void Bloq::toString() {
	cout << " Bloque --> " << endl;
	cout << " Apunta al bloque N°:   " << this->pos_bloque_aux << endl;
	cout << " Cantidad de espacio libre:   " << this->esp_libre << endl;

	list < Reg > ::iterator it;
	for (it = this->regs.begin(); it != this->regs.end(); ++ it)
		(*it).toString();
}
