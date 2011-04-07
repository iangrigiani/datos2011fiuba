/*
 * Bloque_Hash.cpp
 *
 *  Created on: 31/03/2011
 *      Author: angeles
 */

#include "Bloque_Hash.h"

Bloque_Hash::Bloque_Hash(int tam_dispersion) : Bloq(), tam_dispersion(tam_dispersion) {}

void Bloque_Hash::duplicar_tam_dispersion() {
	this->tam_dispersion *= 2;
}

void Bloque_Hash::truncar_tam_dispersion() {
	this->tam_dispersion /= 2;
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

bool Bloque_Hash::agregar_nuevo_offset_a_reg(int clave, int offset) {
	int esp_libre;
	list < Reg > ::iterator it;

	it = this->get_regs().begin();
	while (it != this->get_regs().end() && (*it).get_clave() != clave)
		++ it;

	if ((*it).get_clave() == clave) {
		(*it).agregar_nuevo_offset(offset);
		esp_libre = this->get_esp_libre();
		esp_libre -= (*it).get_tam();
		return true;
	}
	return false;
}

int Bloque_Hash::eliminar_offset_de_reg(int clave, int offset) {
	int esp_libre;
	list < Reg > ::iterator it;

	it = this->get_regs().begin();
	while (it != this->get_regs().end() && (*it).get_clave() != clave)
		++ it;

	if ((*it).get_clave() == clave) {
		if ((*it).eliminar_offset(offset) == true) {
			esp_libre = this->get_esp_libre();
			esp_libre += (*it).get_tam();
			return 0;
		}
		return 1;
	}
	return 2;
}

list < Reg > Bloque_Hash::actualizar_regs(int tam_tabla) {
	list < Reg > ::iterator it_1;
	list < int > ::iterator it_2;
	list < Reg > list_aux;
	Reg reg_aux(0);
	int resto;

	for (it_1 = this->get_regs().begin(); it_1 != this->get_regs().end(); ++ it_1) {
		resto = (*it_1).get_clave() % tam_tabla;

		it_2 = this->pos_tabla.begin();
		while (it_2 != this->pos_tabla.end() && *it_2 != resto)
			++ it_2;

		if (*it_2 != resto && it_2 == this->pos_tabla.end()) {
			reg_aux = *it_1;
			this->get_regs().erase(it_1);
			list_aux.push_back(reg_aux);
		}
	}
	return list_aux;
}

void Bloque_Hash::incorporar_regs(list < Reg > regs) {
	this->get_regs() = regs;
}

void Bloque_Hash::serializar(char* buffer, unsigned int& offset) {
	this->serializar(buffer, offset);
	Persistencia::PonerEnteroEnChar(buffer, offset, this->pos_arch);
	Persistencia::PonerEnteroEnChar(buffer, offset, this->tam_dispersion);

	Persistencia::PonerEnteroEnChar(buffer, offset, this->pos_tabla.size());
	list < int > ::iterator it;
	for (it = this->pos_tabla.begin(); it != this->pos_tabla.end(); ++ it)
		Persistencia::PonerEnteroEnChar(buffer, offset, (*it));
}

void Bloque_Hash::hidratar(char* buffer, unsigned int& offset) {
	this->hidratar(buffer, offset);
	this->pos_arch = Persistencia::getEnteroDesdeBuffer(buffer, offset);
	this->tam_dispersion = Persistencia::getEnteroDesdeBuffer(buffer, offset);

	int tam_pos_tabla = Persistencia::getEnteroDesdeBuffer(buffer, offset);
	for (int i = 0; i < tam_pos_tabla; ++ i)
		this->pos_tabla.push_back(Persistencia::getEnteroDesdeBuffer(buffer,offset));
}

void Bloque_Hash::toString() {
	this->toString();
	cout << " ID (posición relativa en el archivo):   " << this->pos_arch << endl;
	cout << " Tamaño de dispersión:   " << this->tam_dispersion << endl;

	int i = 0;
	list < int > ::iterator it;
	for (it = this->pos_tabla.begin(); it != this->pos_tabla.end(); ++ it) {
		cout << " Posición en la tabla #" << i << ":   " << *it << endl;
		++ i;
	}
}
