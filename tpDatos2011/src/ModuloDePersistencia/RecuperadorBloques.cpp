#include "RecuperadorBloques.h"

RecuperadorBloques::RecuperadorBloques() {

}

RecuperadorBloques::RecuperadorBloques (std::string path){
	this->path = path;
	offset = 0;
}

Registro * RecuperadorBloques::getRegistro(ClaveNumerica * key, int offset){
	std::ifstream archivoEntrada;
	archivoEntrada.open(this->path.c_str());
	archivoEntrada.seekg(offset);
	char bloqueLeido[TAMANIO_BUFFER];
	archivoEntrada.read(bloqueLeido, TAMANIO_BUFFER);
	Bloque * bloque = new Bloque();
	unsigned int offsetChar = 0;
	bloque->hidratar(bloqueLeido, offsetChar);
	Registro * temporal = bloque->getRegistro(key);
	if (temporal==NULL){
		offset += TAMANIO_BUFFER;
		return getRegistro(key, offset);
	}
	Registro * reg = new Registro(*temporal);
	delete bloque;
	return reg;
}


Registro * RecuperadorBloques::getSiguienteRegistro(ClaveNumerica * key,ClaveNumerica * prevKey, int offset){
	std::ifstream archivoEntrada;
	archivoEntrada.open(this->path.c_str());
	archivoEntrada.seekg(offset);
	char bloqueLeido[TAMANIO_BUFFER];
	archivoEntrada.read(bloqueLeido, TAMANIO_BUFFER);
	Bloque * bloque = new Bloque();
	unsigned int offsetChar = 0;
	bloque->hidratar(bloqueLeido, offsetChar);
	Registro * temporal = bloque->getSiguienteRegistro(key, prevKey);
	if (temporal==NULL){
		offset += TAMANIO_BUFFER;
		return getSiguienteRegistro(key, prevKey, offset);
	}
	Registro * reg = new Registro(*temporal);
	delete bloque;
	return reg;
}


Bloque * RecuperadorBloques::getSiguienteBloque(){
	std::ifstream archivoEntrada;
	archivoEntrada.open(this->path.c_str(), std::ios_base::in);
	int inicio = archivoEntrada.tellg();
	archivoEntrada.seekg (0, std::ios_base::end);
	int fin = archivoEntrada.tellg();
	int tamanio = (fin-inicio);
	if (offset < (unsigned int)tamanio){
		archivoEntrada.seekg(offset);
		char bloqueLeido[TAMANIO_BUFFER];
		archivoEntrada.read(bloqueLeido, TAMANIO_BUFFER);
		Bloque * bloqueObtenido = new Bloque();
		unsigned int offsetChar = 0;
		bloqueObtenido->hidratar(bloqueLeido, offsetChar);
		offset += TAMANIO_BUFFER;
		return bloqueObtenido;
	}
	return NULL;
}


RecuperadorBloques::~RecuperadorBloques() {

}
