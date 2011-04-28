#include "Nodo.h"

Nodo::Nodo(int nivel) {
	this->nivel = nivel;
	this->espacioOcupado = 0;
	this->cantidadClaves = 0;
	this->offset = 0;
//	this->claves = new Clave[(TAM_EFECTIVO_NODO/(TAM_CONTROL_REGISTRO)) + 2];
	this->claves = new Clave[TAM_EFECTIVO_NODO + 2];
}

Nodo::~Nodo() {
 delete[] this->claves;
}

bool Nodo::isNodoHoja() {
	return (nivel == 0);
}

bool Nodo::isOverflow(int tamanioRegistro) {
	return (espacioOcupado + tamanioRegistro > TAM_EFECTIVO_NODO);
}

bool Nodo::isUnderflow() {
	return (espacioOcupado < TAM_EFECTIVO_NODO / 2);
}

bool Nodo::puedeCederElementos() {
	return (espacioOcupado > TAM_EFECTIVO_NODO / 2);
}
