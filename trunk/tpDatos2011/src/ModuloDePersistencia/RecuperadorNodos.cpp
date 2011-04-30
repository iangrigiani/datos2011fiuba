#include "RecuperadorNodos.h"


RecuperadorNodos::RecuperadorNodos() {
}

RecuperadorNodos::RecuperadorNodos (std::string path){
	this->path = path;
	this->handler = new HandlerBloques(TAMANIO_BUFFER, this->path);
}

Nodo * RecuperadorNodos::obtenerNodo(int nroNodo){
	this->buffer = (char*)calloc(TAMANIO_BUFFER, sizeof(char));
	char* buffer_aux = (char*)calloc(TAMANIO_BUFFER, sizeof(char));
	unsigned int offset = 0;
	this->buffer = this->handler->recuperar_bloque_arbol(nroNodo);
	std::stringstream ss;
	ss << this->buffer;
	string cadena = ss.str();
	if (cadena.length() > 0){
		buffer_aux = this->handler->recuperar_bloque_arbol(nroNodo);
		NodoInterior* aux = new NodoInterior();
		int nivel = aux->obtenerNivel(buffer_aux);
		free(buffer_aux);
		delete aux;
		if (nivel == 0){
			NodoHoja* hoja = new NodoHoja();
			hoja->hidratar(this->buffer, offset);
			return hoja;
		}else{
			NodoInterior* interior = new NodoInterior();
			interior->hidratar(this->buffer, offset);
			return interior;

		}
	}
	return NULL;
}

RecuperadorNodos::~RecuperadorNodos(){
	free(this->buffer);
	delete this->handler;
}
