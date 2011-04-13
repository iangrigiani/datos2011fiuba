#include "Clave.h"


Clave::Clave() {

}

Clave::Clave(std::string clave){
	setValorClave(clave);
}

std::string Clave::getClave(){
	return (this->clave);
}

void Clave::serializar(char * buffer,unsigned int &offset){
	Persistencia::PonerStringEnChar(buffer, offset, (char*)this->clave.c_str());
}

void Clave::hidratar(char * buffer,unsigned int &offset){
	this->clave = Persistencia::getStringDesdeBuffer(buffer, offset);
}

bool Clave::igual (Clave *a){
	Clave key = (*a);
	return this->clave == key.clave;
}

bool Clave::esMenor(Clave *a){
	Clave key = (*a);
	return this->clave < key.clave;
}

bool Clave::esMenorIgual(Clave *a){
	Clave key = (*a);
	std::cout << clave << " " << key.getClave() << std::endl;
	return this->clave <= key.clave;
}
void Clave::toString(){
	std::cout << "	Clave de Registro: " << this->clave << std::endl;
}
Clave::~Clave() {

}
