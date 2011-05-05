#include "RecuperadorNodos.h"


RecuperadorNodos::RecuperadorNodos() {
}

RecuperadorNodos::RecuperadorNodos (std::string path){
	this->path = path;
	this->handler = new HandlerBloques(TAMANIO_BUFFER, this->path);
}

Nodo * RecuperadorNodos::obtenerNodo(int nroNodo){
	char buffer[TAMANIO_BUFFER];
	char buffer_aux[TAMANIO_BUFFER];
	for (int i = 0 ; i < TAMANIO_BUFFER ; ++i){
		buffer[i] = NULL;
	}
	for (int i = 0 ; i < TAMANIO_BUFFER ; ++i){
		buffer_aux[i] = NULL;
	}
//	buffer = "";
//	buffer_aux = "";
//	this->buffer = (char*)calloc(TAMANIO_BUFFER, sizeof(char));
//	char* buffer_aux = (char*)calloc(TAMANIO_BUFFER, sizeof(char));
	unsigned int offset = 0;
	this->handler->recuperar_bloque_arbol(nroNodo, buffer);
	std::stringstream ss;
	ss << buffer;
	string cadena = ss.str();
	if (cadena.length() > 0){
		this->handler->recuperar_bloque_arbol(nroNodo, buffer_aux);
		NodoInterior* aux = new NodoInterior();
		int nivel = aux->obtenerNivel(buffer_aux);
//		free(buffer_aux);
		delete aux;
		if (nivel == 0){
			NodoHoja* hoja = new NodoHoja();
			hoja->hidratar(buffer, offset);
//			free(this->buffer);
			return hoja;
		}else{
			NodoInterior* interior = new NodoInterior();
			interior->hidratar(buffer, offset);
//			free(this->buffer);
			return interior;

		}
	}
//	}else{
//		free(buffer_aux);
////		free(this->buffer);
//	}
	return NULL;
}

RecuperadorNodos::~RecuperadorNodos(){
//	free(this->buffer);
	delete this->handler;
}
