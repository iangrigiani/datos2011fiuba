#include "Elementos.h"

Elementos::Elementos() {
	this->clave = new Clave("0");
	this->claveEnFC = new Clave("0");
	this->transformada = 0;
}

Elementos::Elementos(Clave* clave, unsigned int offset){
	this->clave = clave;
	this->offset = offset;
	this->claveEnFC = new Clave("0");
	this->transformada = 0;
}

void Elementos::transformarAFrontCoding(string primera){
	if (transformada == 0){
		FrontCoding* fc = new FrontCoding();
		string modificada = fc->pasarAFrontCoding(primera, this->clave->getClave());
		this->claveEnFC->setValorClave(modificada);
		this->transformada = 1;
		delete fc;
	}
}

void Elementos::sacarElFrontCoding(string palabra){
	if (transformada == 1){
		FrontCoding* fc = new FrontCoding();
		string modificada = fc->interpretarFrontCoding(palabra);
		this->claveEnFC->setValorClave(modificada);
		this->transformada = 0;
		delete fc;
	}
}
Elementos::~Elementos() {
//	delete this->clave;
}
void Elementos::serializar(char * buffer, unsigned int &offset){
	this->clave->serializar(buffer, offset);
	this->claveEnFC->serializar(buffer, offset);
	Persistencia::PonerEnteroEnChar(buffer, offset, this->offset);
	Persistencia::PonerEnteroEnChar(buffer, offset, this->transformada);
}
void Elementos::hidratar(char * buffer, unsigned int &offset){
	this->clave->hidratar(buffer,offset);
	this->claveEnFC->hidratar(buffer,offset);
	this->offset = Persistencia::getEnteroDesdeBuffer(buffer,offset);
	this->transformada = Persistencia::getEnteroDesdeBuffer(buffer,offset);
}

void Elementos::toString(){
	cout << "Elemento de Nodo --->" << endl;
	cout<< "	Dato del elemento: " << this->clave->getClave() << endl;
	cout<< "	offset : " << this->offset << endl;
}
