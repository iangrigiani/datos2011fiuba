#include "EscritorNodosLibres.h"
#include <stdlib.h>

EscritorNodosLibres::EscritorNodosLibres() {
}

EscritorNodosLibres::EscritorNodosLibres(std::string path) {
	this->path  = path;
	this->handler = new HandlerBloques(TAMANIO_BUFFER, this->path);
}

void EscritorNodosLibres::GrabarDatosConfig(int primeraHoja , vector<int> nodosLibres){
//	this->buffer = (char*)calloc (TAMANIO_BUFFER, sizeof(int));
	char buffer[TAMANIO_BUFFER];
	for (int i = 0 ; i < TAMANIO_BUFFER ; ++i){
		buffer[i] = NULL;
	}
	unsigned int offset = 0;
	serializarPrimeraHoja(primeraHoja, buffer, offset);
	serializarNodosLibres(nodosLibres, buffer, offset);
	this->handler->guardar_bloque_arbol(buffer, 0);
//	free(this->buffer);
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
//	free(this->buffer);
	delete this->handler;
}
