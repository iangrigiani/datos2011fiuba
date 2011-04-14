#include "EscritorNodo.h"

EscritorNodo::EscritorNodo() {
	this->handler = new HandlerDeBloques();
}

EscritorNodo::EscritorNodo(std::string path){

	this->path  = path;
	this->handler = new HandlerDeBloques(this->path);
}

void EscritorNodo::ActualizarArchivoNodo(Nodo * nodo, int nro_bloque){
	this->buffer = (char*)calloc(TAMANIO_BUFFER, sizeof(char));
	unsigned int offset = 0;
	if (nro_bloque > 0){
		NodoInterior *nodoIntAGuardar = static_cast<NodoInterior*> (nodo);
		nodoIntAGuardar->serializar(buffer, offset);
	}else{
		NodoHoja *nodoHojaAGuardar = static_cast<NodoHoja*> (nodo);
		nodoHojaAGuardar->serializar(buffer, offset);
	}
	this->handler->guardar_bloque(buffer, nro_bloque);

}

EscritorNodo::~EscritorNodo() {
	free(this->buffer);
	delete this->handler;
}
