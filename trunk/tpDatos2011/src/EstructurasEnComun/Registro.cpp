#include "Registro.h"


Registro::Registro() {
	this->clave = new Clave("0");
}

Registro::Registro(string titulo,string autor,string editorial,list<string> palabras, string uiKey){
	this->titulo = titulo;
	this->autor = autor;
	this->editorial = editorial;
	this->palabras = palabras;
	this->clave = new Clave(uiKey);
}

Registro::Registro(Clave * uiKey){
	this->clave = uiKey;
}

Registro::Registro(const Registro &a){
	this->titulo = a.titulo;
	this->autor = a.autor;
	this->editorial = a.editorial;
	this->palabras = a.palabras;
	this->clave = new Clave(*(a.clave));
}

void Registro::serializar(char * buffer, unsigned int &offset){
	Persistencia::PonerStringEnChar(buffer, offset, (char*)this->titulo.c_str());
	Persistencia::PonerStringEnChar(buffer, offset, (char*)this->autor.c_str());
	Persistencia::PonerStringEnChar(buffer, offset, (char*)this->editorial.c_str());
	Persistencia::PonerEnteroEnChar(buffer, offset, this->palabras.size());
	list<string>::iterator it = this->palabras.begin();
	while( it != this->palabras.end()){
		Persistencia::PonerStringEnChar(buffer, offset, (char*)(*it).c_str());
		++it;
	}
	this->clave->serializar(buffer, offset);
}

void Registro::hidratar(char * buffer, unsigned int &offset){
	this->titulo = Persistencia::getStringDesdeBuffer(buffer, offset);
	this->autor = Persistencia::getStringDesdeBuffer(buffer, offset);
	this->editorial = Persistencia::getStringDesdeBuffer(buffer, offset);
	int palabras = Persistencia::getEnteroDesdeBuffer(buffer, offset);
	int cont = 0;
	while(cont < palabras){
		this->palabras.push_back(Persistencia::getStringDesdeBuffer(buffer,offset));
		++cont;
	}
	this->clave->hidratar(buffer, offset);
}

void Registro::toString(){
	std::cout << "Registro de Libro--> " << std::endl;
	std::cout << "		 	 Título   : " << this->titulo << std::endl;
	std::cout << "		 	 Autor 	  : " << this->autor << std::endl;
	std::cout << "		 	 Editorial: " << this->editorial << std::endl;
	std::cout << "Cantidad de Palabras: " << this->palabras.size() << std::endl;
	this->clave->toString();
}
Registro::~Registro() {
	delete this->clave;
}
