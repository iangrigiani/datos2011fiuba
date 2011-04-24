/*
 * Reg.cpp
 *
 *  Created on: 23/04/2011
 *      Author: catu
 */

#include "Reg.h"


Reg::Reg() : clave(-1) {}

Reg::Reg(int clave): clave(clave){}


void Reg::set_clave(int clave) {
	this->clave = clave;
}

