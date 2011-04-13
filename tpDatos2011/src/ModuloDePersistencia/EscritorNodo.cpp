#include "EscritorNodo.h"

EscritorNodo::EscritorNodo() {
	this->handler = new HandlerBloquesOtraVersion();
}

EscritorNodo::EscritorNodo(std::string path, std::string pathEspacioLibre){

	this->path  = path;
	this->pathEspacioLibre = pathEspacioLibre;
	this->handler = new HandlerBloquesOtraVersion(this->path, this->pathEspacioLibre);
}

void EscritorNodo::ActualizarArchivoNodo(Nodo * nodo, int nivel){
	this->buffer = (char*)calloc(TAMANIO_BUFFER, sizeof(char));
	unsigned int offset = 0;
	if (nivel > 0){
		NodoInterior *nodoIntAGuardar = static_cast<NodoInterior*> (nodo);
		nodoIntAGuardar->serializar(buffer, offset);
	}else{
		NodoHoja *nodoHojaAGuardar = static_cast<NodoHoja*> (nodo);
		nodoHojaAGuardar->serializar(buffer, offset);
	}
	this->handler->guardar_bloque(buffer, nivel);

}

EscritorNodo::~EscritorNodo() {
	free(this->buffer);
	delete this->handler;
}
