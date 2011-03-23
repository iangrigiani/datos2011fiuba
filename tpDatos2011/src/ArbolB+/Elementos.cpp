#include "Elementos.h"

Elementos::Elementos() {
	// TODO Auto-generated constructor stub

}

Elementos::Elementos(ClaveNumerica* clave, unsigned int offset){
	this->clave = clave;
	this->offset = offset;
}
Elementos::~Elementos() {
	delete this->clave;
}
void Elementos::serializar(char * buffer, unsigned int &offset){
	Persistencia::PonerEnteroEnChar(buffer,offset,offset);
	this->clave->serializar(buffer, offset);
}
void Elementos::hidratar(char * buffer, unsigned int &offset){
	this->offset = Persistencia::getEnteroDesdeBuffer(buffer,offset);
	this->clave->hidratar(buffer,offset);
}

void Elementos::toString(){
	this->clave->toString();
	cout<< "offset : " << this->offset << endl;
}
