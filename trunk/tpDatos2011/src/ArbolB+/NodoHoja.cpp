
#include "NodoHoja.h"


NodoHoja::NodoHoja() : Nodo(0) {
	hojaSiguiente = 0;
}

NodoHoja::~NodoHoja() {
	delete[] this->datos;
}

void NodoHoja::serializar(char * buffer, unsigned int &offset) {
	Persistencia::PonerEnteroEnChar(buffer, offset, this->numero);
	Persistencia::PonerEnteroEnChar(buffer, offset, this->nivel);
	Persistencia::PonerEnteroEnChar(buffer, offset, this->offset);
	Persistencia::PonerEnteroEnChar(buffer, offset, this->espacioOcupado);
	Persistencia::PonerEnteroEnChar(buffer, offset, this->cantidadClaves);
	for (int i = 0; i < cantidadClaves; i++){
		claves[i].serializar(buffer,offset);
	}
	Persistencia::PonerEnteroEnChar(buffer, offset, this->hojaSiguiente);
	for (int i = 0; i < cantidadClaves; i++){
		datos[i].serializar(buffer,offset);
	}
}

void NodoHoja::hidratar(char * buffer, unsigned int &offset) {
	this->numero = Persistencia::getEnteroDesdeBuffer(buffer,offset);
	this->nivel = Persistencia::getEnteroDesdeBuffer(buffer,offset);
	this->offset = Persistencia::getEnteroDesdeBuffer(buffer,offset);
	this->espacioOcupado = Persistencia::getEnteroDesdeBuffer(buffer,offset);
	this->cantidadClaves = Persistencia::getEnteroDesdeBuffer(buffer,offset);
	for (int i = 0; i < cantidadClaves ; i++){
		ClaveNumerica clave;
		clave.hidratar(buffer,offset);
		this->claves[i] = clave;
	}
	this->hojaSiguiente = Persistencia::getEnteroDesdeBuffer(buffer,offset);
	for (int i = 0; i < cantidadClaves ; i++){
		Elementos elem;
		elem.hidratar(buffer,offset);
		this->datos[i] = elem;
	}
}

//void NodoHoja::modificarDatos(int posicion, Elementos* dato){
//	bool encontrado = false;
//	int cont = 0;
//	list<Elementos*>::iterator itDatos = this->datos.begin();
//	while ( itDatos != datos.end() && !encontrado){
//		if (cont == posicion){
//			encontrado = true;
//			(*(*itDatos)) = (*dato);
//		}
//		++cont;
//		++itDatos;
//	}
//}
//
//Elementos* NodoHoja::obtenerDato(int posicion){
//	int cont = 0;
//	list<Elementos*>::iterator itDatos = this->datos.begin();
//	while ( itDatos != datos.end()){
//		if (cont == posicion){
//			return (*itDatos);
//		}
//		++cont;
//		++itDatos;
//	}
//	return NULL;
//}
