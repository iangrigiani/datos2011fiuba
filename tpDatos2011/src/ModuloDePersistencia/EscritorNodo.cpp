#include "EscritorNodo.h"

EscritorNodo::EscritorNodo() {
	this->handler = new HandlerBloques(TAMANIO_BUFFER);
}

EscritorNodo::EscritorNodo(std::string path){
	this->path  = path;
	this->handler = new HandlerBloques(TAMANIO_BUFFER, this->path);
}

void EscritorNodo::ActualizarArchivoNodo(Nodo * nodo, int nro_bloque){
//	this->buffer = (char*)calloc(TAMANIO_BUFFER, sizeof(char));
	char buffer[TAMANIO_BUFFER];
	for (int i = 0 ; i < TAMANIO_BUFFER ; ++i){
		buffer[i] = NULL;
	}
	unsigned int offset = 0;
	if (nro_bloque > 0){
		NodoInterior *nodoIntAGuardar = static_cast<NodoInterior*> (nodo);
		nodoIntAGuardar->serializar(buffer, offset);
	}else{
		NodoHoja *nodoHojaAGuardar = static_cast<NodoHoja*> (nodo);
		nodoHojaAGuardar->serializar(buffer, offset);
	}
	this->handler->guardar_bloque_arbol(buffer, nro_bloque);
//	free(this->buffer);
}

EscritorNodo::~EscritorNodo() {
//	free(this->buffer);
	delete this->handler;
}
