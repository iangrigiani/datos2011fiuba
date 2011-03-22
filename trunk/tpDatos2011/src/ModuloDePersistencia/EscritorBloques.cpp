#include "EscritorBloques.h"
#include <stdlib.h>

EscritorBloques::EscritorBloques() {
}

EscritorBloques::EscritorBloques(std::string path) {
	this->path  = path;
	this->bufferOffset = 0;
	this->fileOffset = 0;
	this->bloque = new Bloque();
}


int EscritorBloques::GrabarRegistro(Registro * reg){

	if (bloque->agregarRegistro(reg)){
		std::cout << "Grabe registro" << std::endl;
		return BLOQUE_NO_LLENO;
	}
	else {
		GrabarBloqueEnArchivo();
		this->bloque->agregarRegistro(reg);
		GrabarBloqueEnArchivo();
		return BLOQUE_LLENO;
	}
}

void EscritorBloques::GrabarBloqueEnArchivo(){
	this->buffer = (char*)calloc (TAMANIO_BUFFER, sizeof(char));
	this->bloque->serializar(this->buffer, this->bufferOffset);
	std::ofstream archivoSalida;
	archivoSalida.open(this->path.c_str(), std::ios_base::app);
	archivoSalida.write(this->buffer, TAMANIO_BUFFER);
	archivoSalida.close();
	free (this->buffer);
	this->bloque->limpiar();
	this->bufferOffset = 0;
	this->fileOffset += TAMANIO_BUFFER;
}

EscritorBloques::~EscritorBloques() {

}
