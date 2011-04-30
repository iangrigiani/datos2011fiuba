#include "EscritorNodosLibres.h"
#include <stdlib.h>

EscritorNodosLibres::EscritorNodosLibres() {
}

EscritorNodosLibres::EscritorNodosLibres(std::string path) {
	this->path  = path;
	this->handler = new HandlerBloques(TAMANIO_BUFFER, this->path);
}

void EscritorNodosLibres::GrabarDatosConfig(int primeraHoja , vector<int> nodosLibres){
	this->buffer = (char*)calloc (TAMANIO_BUFFER, sizeof(int));
	unsigned int offset = 0;
	serializarPrimeraHoja(primeraHoja, this->buffer, offset);
	serializarNodosLibres(nodosLibres, this->buffer, offset);
	this->handler->guardar_bloque_arbol(this->buffer, 0);
}

void EscritorNodosLibres::serializarPrimeraHoja(int primeraHoja, char * buffer, unsigned int &offset){
	Persistencia::PonerEnteroEnChar(buffer, offset, primeraHoja);
}
void EscritorNodosLibres::serializarNodosLibres(vector<int> nodosLibres, char * buffer, unsigned int &offset){
	Persistencia::PonerEnteroEnChar(buffer, offset, nodosLibres.size());
	for (int i = 0;(unsigned int)i < nodosLibres.size(); i++){
		Persistencia::PonerEnteroEnChar(buffer,offset,nodosLibres[i]);
	}
}
EscritorNodosLibres::~EscritorNodosLibres() {
	free(this->buffer);
	delete this->handler;
}
