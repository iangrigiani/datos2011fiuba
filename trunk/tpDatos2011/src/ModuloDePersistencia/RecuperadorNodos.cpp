#include "RecuperadorNodos.h"


RecuperadorNodos::RecuperadorNodos() {

}

RecuperadorNodos::RecuperadorNodos (std::string path){
	this->path = path;
	this->handler = new HandlerDeBloques(this->path);
}

Nodo * RecuperadorNodos::obtenerNodo(int nroNodo, int tipoNodo){
	this->buffer = (char*)calloc(TAMANIO_BUFFER, sizeof(char));
	unsigned int offset = 0;
	this->buffer = this->handler->recuperar_bloque(nroNodo);
	std::stringstream ss;
	ss << this->buffer;
	string cadena = ss.str();
	if (cadena.length() > 0){
		if (tipoNodo == 1){
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
