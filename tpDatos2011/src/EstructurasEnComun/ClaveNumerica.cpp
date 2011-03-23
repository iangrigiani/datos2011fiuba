#include "ClaveNumerica.h"


ClaveNumerica::ClaveNumerica() {

}

ClaveNumerica::ClaveNumerica(int clave){
	this->clave = 0;
	setValorClave(clave);
}

int ClaveNumerica::getValorClave(){
	return (this->clave);
}

int ClaveNumerica::getTipo(){
	return TIPO_CLAVE_NUMERICA;
}

void ClaveNumerica::serializar(char * buffer,unsigned int &offset){
	Persistencia::PonerEnteroEnChar(buffer, offset, this->clave);
}

void ClaveNumerica::hidratar(char * buffer,unsigned int &offset){
	this->clave = Persistencia::getEnteroDesdeBuffer(buffer, offset);
}

bool ClaveNumerica::igual (ClaveNumerica *a){
	ClaveNumerica key = (*a);
	return this->clave == key.clave;
}

bool ClaveNumerica::esMenor(ClaveNumerica *a){
	ClaveNumerica key = (*a);
	return this->clave < key.clave;
}

bool ClaveNumerica::esMenorIgual(ClaveNumerica *a){
	ClaveNumerica key = (*a);
	std::cout << clave << " " << key.getValorClave() << std::endl;
	return this->clave <= key.clave;
}
void ClaveNumerica::toString(){
	std::cout << "	Clave de Registro: " << this->clave << std::endl;
}
ClaveNumerica::~ClaveNumerica() {

}
