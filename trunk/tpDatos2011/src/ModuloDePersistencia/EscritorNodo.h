#ifndef ESCRITORNODO_H_
#define ESCRITORNODO_H_

#include <string>
#include <fstream>
#include <iostream>
#include <stdlib.h>
#include "../ArbolB+/Nodo.h"
#include "../ArbolB+/NodoInterior.h"
#include "../ArbolB+/NodoHoja.h"

class EscritorNodo {
private:
	char * buffer;
	unsigned int bufferOffset;
	unsigned int fileOffset;
	std::string path;
	std::ofstream oss;
public:
	EscritorNodo();
	EscritorNodo (std::string path);
	void GrabarEnArchivo(class Nodo * node);
	int getOffset(){
		return this->fileOffset;
	}
	void ActualizarArchivoNodo(class Nodo * node);
	void close(){
		this->oss.close();
	}


	virtual ~EscritorNodo();
};

#endif /* ESCRITORNODO_H_ */
