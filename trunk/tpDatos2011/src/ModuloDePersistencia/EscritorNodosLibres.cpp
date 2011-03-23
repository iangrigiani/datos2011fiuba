#include "EscritorNodosLibres.h"
#include <stdlib.h>

EscritorNodosLibres::EscritorNodosLibres() {
}

EscritorNodosLibres::EscritorNodosLibres(std::string path) {
	this->path  = path;
	this->bufferOffset = 0;
	this->fileOffset = 0;
}

void EscritorNodosLibres::GrabarDatosConfig(int primeraHoja , vector<int> nodosLibres){
	this->buffer = (char*)calloc (BUFFER_NODOS_LIBRES, sizeof(int));
	serializarPrimeraHoja(primeraHoja, this->buffer, this->bufferOffset);
	serializarNodosLibres(nodosLibres, this->buffer, this->bufferOffset);
	std::ofstream archivoSalida;
	archivoSalida.open(this->path.c_str());
	archivoSalida.write(this->buffer, BUFFER_NODOS_LIBRES);
	archivoSalida.close();
	free (this->buffer);
	this->bufferOffset = 0;
	this->fileOffset += BUFFER_NODOS_LIBRES;
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

}
