#include "Elementos.h"

Elementos::Elementos() {

}

Elementos::Elementos(Clave* clave, unsigned int offset){
	this->clave = clave;
	this->offset = offset;
}
Elementos::~Elementos() {
	delete this->clave;
}
void Elementos::serializar(char * buffer, unsigned int &offset){
	this->clave->serializar(buffer, offset);
	Persistencia::PonerEnteroEnChar(buffer, offset, this->offset);
}
void Elementos::hidratar(char * buffer, unsigned int &offset){
	this->clave->hidratar(buffer,offset);
	this->offset = Persistencia::getEnteroDesdeBuffer(buffer,offset);
}

void Elementos::toString(){
	cout << "Elemento de Nodo --->" << endl;
	cout<< "	Dato del elemento: " << this->clave->getClave() << endl;
	cout<< "	offset : " << this->offset << endl;
}
