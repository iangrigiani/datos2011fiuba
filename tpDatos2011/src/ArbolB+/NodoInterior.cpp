
#include "NodoInterior.h"


NodoInterior::NodoInterior(int nivel) : Nodo(nivel) {
	this->hijos = new int[TAM_EFECTIVO_NODO + 2];
	this->espacioOcupado = TAM_CONTROL_NODO;
}

NodoInterior::NodoInterior() : Nodo(0){
	this->hijos = new int[TAM_EFECTIVO_NODO + 2];
	this->espacioOcupado = TAM_CONTROL_NODO;
}

NodoInterior::~NodoInterior() {
	delete[] hijos;
}

void NodoInterior::serializar(char * buffer, unsigned int &offset){
	Persistencia::PonerEnteroEnChar(buffer, offset, this->nivel);
	Persistencia::PonerEnteroEnChar(buffer, offset, this->numero);
	Persistencia::PonerEnteroEnChar(buffer, offset, this->espacioOcupado);
	Persistencia::PonerEnteroEnChar(buffer, offset, this->cantidadClaves);
	for (int i = 0; i < cantidadClaves; i++){
		claves[i].serializar(buffer,offset);
	}
	for (int i = 0; i <= cantidadClaves; i++){
		Persistencia::PonerEnteroEnChar(buffer,offset,hijos[i]);
	}
}
void NodoInterior::hidratar(char * buffer, unsigned int &offset){
	this->nivel = Persistencia::getEnteroDesdeBuffer(buffer,offset);
	this->numero = Persistencia::getEnteroDesdeBuffer(buffer,offset);
	this->espacioOcupado = Persistencia::getEnteroDesdeBuffer(buffer,offset);
	this->cantidadClaves = Persistencia::getEnteroDesdeBuffer(buffer,offset);
	for (int i = 0; i < cantidadClaves ; i++){
		Clave clave;
		clave.hidratar(buffer,offset);
		this->claves[i] = clave;
	}

	for (int i = 0; i <= cantidadClaves ; i++){
		this->hijos[i] = Persistencia::getEnteroDesdeBuffer(buffer,offset);
	}
}

int NodoInterior::obtenerNivel (char* buffer){
	unsigned int offset = 0;
	return (Persistencia::getEnteroDesdeBuffer(buffer,offset));
}
