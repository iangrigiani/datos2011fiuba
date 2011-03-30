/*
 * RecuperadorRegistro.cpp
 *
 *  Created on: 30/03/2011
 *      Author: catu
 */

#include "RecuperadorRegistro.h"


RecuperadorRegistro::RecuperadorRegistro() {

}

RecuperadorRegistro::RecuperadorRegistro(std::string path) {

	this->path = path;
	this->offset = 0;
}


RecuperadorRegistro::~RecuperadorRegistro() {

}

char * RecuperadorRegistro::obtenerLibro(int offset)
{
	std::ifstream archivoRegistros;
	archivoRegistros.open(this->path.c_str());
	archivoRegistros.seekg(offset);
	//TODO definir el tamanio del libro a leer! Hablar con Angie!
	char  libroLeido [100];
	archivoRegistros.read(libroLeido, 100);
	return libroLeido;
}

unsigned int RecuperadorRegistro::getOffset()
{
	return this->offset;
}

void RecuperadorRegistro::setOffset(unsigned int offset)
{
	this->offset = offset;
}

