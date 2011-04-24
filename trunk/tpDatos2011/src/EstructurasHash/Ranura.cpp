/*
 * Ranura.cpp
 *
 *  Created on: 21/04/2011
 *      Author: angeles
 */

#include "Ranura.h"

Ranura::Ranura(int tam_disp) : Bloque(tam_disp), estado(VACIA) {}

void Ranura::modificar_estado() {
	if (estado == VACIA)
		estado = OCUPADA;
	else estado = VACIA;
}

bool Ranura::esta_ocupada() {
	if (estado == OCUPADA)
		return true;
	return false;
}

void Ranura::agregar_nuevo_reg(const RegTitulo& reg) {
	this->reg = reg;
	this->modificar_estado();
}

bool Ranura::eliminar_reg(int clave) {
	if (clave == this->reg.get_clave()) {
		this->modificar_estado();
		return true;
	}
	return false;
}

bool Ranura::actualizar_reg(int num_bloque, HandlerTabla& handler, RegTitulo& reg) {
	int pos_tabla;

	if (num_bloque != handler.get_num_bloque(this->reg.get_clave(), pos_tabla)) {
		reg = this->reg;
		this->eliminar_reg(this->reg.get_clave());
		return true;
	}

	return false;
}

void Ranura::serializar(char* buffer, unsigned int& offset) {
	Persistencia::PonerEnteroEnChar(buffer, offset, this->estado);
	Persistencia::PonerEnteroEnChar(buffer, offset, this->get_tam_disp());
	reg.serializar(buffer, offset);
}

void Ranura::hidratar(char* buffer, unsigned int& offset) {
	this->estado = Persistencia::getEnteroDesdeBuffer(buffer, offset);
	this->set_tam_disp(Persistencia::getEnteroDesdeBuffer(buffer, offset));
	RegTitulo reg;
	reg.hidratar(buffer, offset);
	this->reg = reg;
}

void Ranura::toString() {
	cout << " Ranura --> " << endl;
	cout << " Estado:   " << this->estado << endl;
	cout << " Tamaño de dispersión:   " << this->get_tam_disp() << endl;
	if (this->estado == OCUPADA)
		this->reg.toString();
}
