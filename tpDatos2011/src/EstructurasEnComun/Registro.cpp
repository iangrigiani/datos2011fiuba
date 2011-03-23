#include "Registro.h"


Registro::Registro() {
	this->Clave = new ClaveNumerica();
}

Registro::Registro(std::string apellido, int uiKey){
	this->apellido = apellido;
	this->Clave = new ClaveNumerica(uiKey);
}

Registro::Registro(ClaveNumerica * uiKey){
	this->Clave = uiKey;
}

Registro::Registro(const Registro &a){
	this->apellido = a.apellido;
	this->Clave = new ClaveNumerica(*(a.Clave));
}

std::string Registro::getApellido(){
	return this->apellido;
}

void Registro::serializar(char * buffer, unsigned int &offset){
	Persistencia::PonerStringEnChar(buffer, offset, (char*)this->apellido.c_str());
	this->Clave->serializar(buffer, offset);
}

void Registro::hidratar(char * buffer, unsigned int &offset){
	this->apellido = Persistencia::getStringDesdeBuffer(buffer, offset);
	this->Clave->hidratar(buffer, offset);
}

void Registro::toString(){
	std::cout << "Registro --> " << std::endl;
	std::cout << "		 Apellido: " << this->apellido << std::endl;
	this->Clave->toString();
}
Registro::~Registro() {
	delete this->Clave;
}
