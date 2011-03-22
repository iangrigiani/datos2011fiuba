#include "EscritorNodo.h"

EscritorNodo::EscritorNodo() {

}

EscritorNodo::EscritorNodo(std::string path){
	this->path  = path;
	this->bufferOffset = 0;
	this->fileOffset = 0;
}

void EscritorNodo::GrabarEnArchivo(Nodo * nodo){
	if (!oss.is_open()){
		oss.open(path.c_str());
	}
	int offsetSum;
	offsetSum = nodo->getNumero()* TAM_TOTAL_NODO;
	this->buffer = (char*)calloc (TAM_TOTAL_NODO, sizeof(char));
	nodo->serializar(this->buffer, this->bufferOffset);
	this->oss.seekp(fileOffset);
	oss.write(this->buffer, offsetSum);
	oss.flush();
	free (this->buffer);
	this->bufferOffset = 0;
	this->fileOffset += offsetSum;
}

void EscritorNodo::ActualizarArchivoNodo(Nodo * nodo){
	if (!oss.is_open()){
		oss.open(path.c_str());
	}
	int offsetSum;
	offsetSum = nodo->getNumero()* TAM_TOTAL_NODO;
	this->buffer = (char*)calloc (TAM_TOTAL_NODO, sizeof(char));
	nodo->serializar(this->buffer, this->bufferOffset);
	oss.seekp(offsetSum);
	oss.write(this->buffer, offsetSum);
	oss.flush();
	free (this->buffer);
	this->bufferOffset = 0;
}

EscritorNodo::~EscritorNodo() {
	close();
}
