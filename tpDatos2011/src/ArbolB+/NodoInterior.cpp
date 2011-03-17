
#include "NodoInterior.h"


NodoInterior::NodoInterior(int nivel) : Nodo(nivel) {

}

NodoInterior::~NodoInterior() {
	list<int*>::iterator it = this->hijos.begin();
	while (it != this->hijos.end()){
		delete (*it);
		it++;
	}
}

void NodoInterior::serializar(char * buffer, unsigned int &offset){
	Persistencia::PonerEnteroEnChar(buffer, offset, this->numero);
	Persistencia::PonerEnteroEnChar(buffer, offset, this->nivel);
	Persistencia::PonerEnteroEnChar(buffer, offset, this->espacioOcupado);
	Persistencia::PonerEnteroEnChar(buffer, offset, this->cantidadClaves);
	Persistencia::PonerEnteroEnChar(buffer, offset, this->claves.size());
	list<ClaveNumerica*>::iterator itClaves = this->claves.begin();
	while ( itClaves != claves.end()){
		(*itClaves)->serialzar(buffer,offset);
	}
	Persistencia::PonerEnteroEnChar(buffer, offset, this->hijos.size());
	list<int*>::iterator itHijos = this->hijos.begin();
	while ( itHijos != hijos.end()){
		Persistencia::PonerEnteroEnChar(buffer, offset, (*(*itHijos)));
	}
}
void NodoInterior::hidratar(char * buffer, unsigned int &offset){
	this->numero = Persistencia::getEnteroDesdeBuffer(buffer,offset);
	this->nivel = Persistencia::getEnteroDesdeBuffer(buffer,offset);
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
	int hijos = Persistencia::getEnteroDesdeBuffer(buffer,offset);
	while (cont < hijos){
		int hijo = Persistencia::getEnteroDesdeBuffer(buffer,offset);
		this->hijos.push_back(&hijo);
		cont++;
	}
}
