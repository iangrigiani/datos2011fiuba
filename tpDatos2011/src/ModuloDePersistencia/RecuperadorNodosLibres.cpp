#include "RecuperadorNodosLibres.h"


RecuperadorNodosLibres::RecuperadorNodosLibres() {
}

RecuperadorNodosLibres::RecuperadorNodosLibres (std::string path){
	this->path = path;
	this->handler = new HandlerBloques(TAMANIO_BUFFER, this->path);
}

void RecuperadorNodosLibres::obtenerDatos(int &primeraHoja, vector<int>& nodosLibres){
	this->buffer = (char*)calloc(TAMANIO_BUFFER, sizeof(char));
	this->buffer = this->handler->recuperar_bloque_arbol(0);
	unsigned int offset = 0;
	hidratarPrimeraHoja(this->buffer,offset,primeraHoja);
	hidratarNodosLibres(this->buffer,offset,nodosLibres);
}

void RecuperadorNodosLibres::hidratarPrimeraHoja(char* readData, unsigned int &offset, int& primeraHoja){
	primeraHoja = Persistencia::getEnteroDesdeBuffer(readData,offset);
}
void RecuperadorNodosLibres::hidratarNodosLibres(char* readData, unsigned int &offset, vector<int>& nodosLibres){
   int cantidad = Persistencia::getEnteroDesdeBuffer(readData,offset);
   for (int i = 0; i < cantidad; i++){
	   nodosLibres.push_back(Persistencia::getEnteroDesdeBuffer(readData,offset));
   }
}
RecuperadorNodosLibres::~RecuperadorNodosLibres(){
	free(this->buffer);
	delete this->handler;

}
