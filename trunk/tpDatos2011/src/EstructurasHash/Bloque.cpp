/*
 * Bloque.cpp
 *
 *  Created on: 22/04/2011
 *      Author: angeles
 */

#include "Bloque.h"

Bloque::Bloque(int tam_disp) : tam_disp(tam_disp) {}

void Bloque::set_tam_disp(int tam_disp) {
	this->tam_disp = tam_disp;
}

void Bloque::duplicar_tam_disp() {
	this->tam_disp *= 2;
}

void Bloque::truncar_tam_disp() {
	this->tam_disp /= 2;
}

