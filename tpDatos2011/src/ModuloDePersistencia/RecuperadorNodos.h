#ifndef RECUPERADORNODOS_H_
#define RECUPERADORNODOS_H_

#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include "../ArbolB+/Nodo.h"
#include "../ArbolB+/NodoHoja.h"
#include "../ArbolB+/NodoInterior.h"
#include "../EstructurasEnComun/Constantes.h"
#include "../ManejadoresDeArchivos/HandlerBloques.h"

class RecuperadorNodos {

private:
	std::string path;
//	char* buffer;
	HandlerBloques* handler;
public:
	RecuperadorNodos();
	RecuperadorNodos (std::string path);
	Nodo * obtenerNodo(int nroNodo);
	int getTamanioArchivo(){
		return this->handler->get_tam_arch_bloques();
	}
	virtual ~RecuperadorNodos();
	void setPath(string path){
		this->path = path;
	}
};

#endif /* RECUPERADORNODOS_H_ */
