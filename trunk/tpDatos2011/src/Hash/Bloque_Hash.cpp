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

void Bloque_Hash::incorporar_regs(list < Reg > regs) {
	list < Reg > ::iterator it;
	for (it = regs.begin(); it != regs.end(); ++ it)
		this->agregar_nuevo_reg(*it);
}

void Bloque_Hash::serializar(char* buffer, unsigned int& offset) {
	Persistencia::PonerEnteroEnChar(buffer, offset, this->tam_dispersion);
	Persistencia::PonerEnteroEnChar(buffer, offset, this->get_pos_bloque_aux());

	Persistencia::PonerEnteroEnChar(buffer, offset, this->get_regs().size());
	list < Reg > ::iterator it;
	for (it = this->get_regs().begin(); it != this->get_regs().end(); ++ it)
		(*it).serializar(buffer, offset);
}

void Bloque_Hash::hidratar(char* buffer, unsigned int& offset) {
	this->vaciar();
	this->tam_dispersion = Persistencia::getEnteroDesdeBuffer(buffer, offset);
	this->set_pos_bloque_aux(Persistencia::getEnteroDesdeBuffer(buffer, offset));

	int tam_regs = Persistencia::getEnteroDesdeBuffer(buffer, offset);
	for (int i = 0; i < tam_regs; ++ i) {
		Reg reg;
		reg.hidratar(buffer, offset);
		this->agregar_nuevo_reg(reg);
	}
}

void Bloque_Hash::toString() {
	cout << " Bloque --> " << endl;
	cout << " Tamaño de dispersión:   " << this->tam_dispersion << endl;
	cout << " Cantidad de espacio libre:   " << this->get_esp_libre() << endl;
	cout << " Apunta al bloque N°:   " << this->get_pos_bloque_aux() << endl;
	cout << " Cantidad de registros:   " << this->get_regs().size() << endl;

/*
	list < Reg > ::iterator it;
	for (it = this->get_regs().begin(); it != this->get_regs().end(); ++ it)
		(*it).toString();
		*/
}
