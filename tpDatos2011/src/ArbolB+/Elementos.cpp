#include "Elementos.h"

Elementos::Elementos() {
	// TODO Auto-generated constructor stub

}

Elementos::Elementos(ClaveNumerica* clave, string dato, unsigned int offset){
	this->clave = clave;
	this->offset = offset;
}
Elementos::~Elementos() {
	delete this->clave;
}
void Elementos::serializar(char * buffer, unsigned int &offset){
	this->clave->serializar(buffer, offset);
	Persistencia::PonerStringEnChar(buffer,offset, (char*)this->dato.c_str());
	Persistencia::PonerEnteroEnChar(buffer, offset, this->offset);
}
void Elementos::hidratar(char * buffer, unsigned int &offset){
	this->clave->hidratar(buffer,offset);
	this->dato = Persistencia::getStringDesdeBuffer(buffer,offset);
	this->offset = Persistencia::getEnteroDesdeBuffer(buffer,offset);
}

void Elementos::toString(){
	cout << "Elemento de Nodo --->" << endl;
	this->clave->toString();
	cout<< "	Dato del elemento: " << this->dato << endl;
	cout<< "	offset : " << this->offset << endl;
}
