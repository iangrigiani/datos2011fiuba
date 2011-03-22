
#include "NodoHoja.h"


NodoHoja::NodoHoja() : Nodo(0) {
	hojaSiguiente = 0;
}

NodoHoja::~NodoHoja() {
	list<Elementos*>::iterator it = this->datos.begin();
	while (it != this->datos.end()){
		delete (*it);
		it++;
	}
}

void NodoHoja::Serializar(char * buffer, unsigned int &offset) {
	Persistencia::PonerEnteroEnChar(buffer, offset, this->numero);
	Persistencia::PonerEnteroEnChar(buffer, offset, this->nivel);
	Persistencia::PonerEnteroEnChar(buffer, offset, this->offset);
	Persistencia::PonerEnteroEnChar(buffer, offset, this->espacioOcupado);
	Persistencia::PonerEnteroEnChar(buffer, offset, this->cantidadClaves);
	Persistencia::PonerEnteroEnChar(buffer, offset, this->claves.size());
	list<ClaveNumerica*>::iterator itClaves = this->claves.begin();
	while ( itClaves != claves.end()){
		(*itClaves)->serialzar(buffer,offset);
	}
	Persistencia::PonerEnteroEnChar(buffer, offset, this->hojaSiguiente);
	Persistencia::PonerEnteroEnChar(buffer, offset, this->datos.size());
	list<Elementos*>::iterator itDatos = this->datos.begin();
	while ( itDatos != datos.end()){
		(*itDatos)->serializar(buffer,offset);
	}
}

void NodoHoja::Hidratar(char * buffer, unsigned int &offset) {
	this->numero = Persistencia::getEnteroDesdeBuffer(buffer,offset);
	this->nivel = Persistencia::getEnteroDesdeBuffer(buffer,offset);
	this->offset = Persistencia::getEnteroDesdeBuffer(buffer,offset);
	this->espacioOcupado = Persistencia::getEnteroDesdeBuffer(buffer,offset);
	this->cantidadClaves = Persistencia::getEnteroDesdeBuffer(buffer,offset);
	int claves = Persistencia::getEnteroDesdeBuffer(buffer,offset);
	int cont = 0;
	while (cont < claves){
		ClaveNumerica * clave = new ClaveNumerica();
		clave->hidratar(buffer,offset);
		this->claves.push_back(clave);
		cont++;
	}
	cont = 0;
	this->hojaSiguiente = Persistencia::getEnteroDesdeBuffer(buffer,offset);
	int datos = Persistencia::getEnteroDesdeBuffer(buffer,offset);
	while (cont < datos){
		Elementos * elem = new Elementos();
		elem->hidratar(buffer,offset);
		this->datos.push_back(elem);
		cont++;
	}
}

void NodoHoja::modificarDatos(int posicion, Elementos* dato){
	bool encontrado = false;
	int cont = 0;
	list<Elementos*>::iterator itDatos = this->datos.begin();
	while ( itDatos != datos.end() && !encontrado){
		if (cont == posicion){
			encontrado = true;
			(*(*itDatos)) = (*dato);
		}
		++cont;
		++itDatos;
	}
}

Elementos* NodoHoja::obtenerDato(int posicion){
	bool encontrado = false;
	int cont = 0;
	list<Elementos*>::iterator itDatos = this->datos.begin();
	while ( itDatos != datos.end()){
		if (cont == posicion){
			return (*itDatos);
		}
		++cont;
		++itDatos;
	}
	return NULL;
}
