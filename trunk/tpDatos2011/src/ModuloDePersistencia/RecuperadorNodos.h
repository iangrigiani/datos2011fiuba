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
#include "../ManejadoresDeArchivos/HandlerBloquesOtraVersion.h"

class RecuperadorNodos {

private:
	std::string path;
	std::string pathEspaciosLibres;
	char* buffer;
	HandlerBloquesOtraVersion* handler;
public:
	RecuperadorNodos();
	RecuperadorNodos (std::string path, std::string pathEspaciosLibres);
	Nodo * obtenerNodo(int nroNodo, int tipoNodo);
	int getTamanioArchivo(){
		return this->handler->get_tam_arch_bloques();
	}
	virtual ~RecuperadorNodos();
};

#endif /* RECUPERADORNODOS_H_ */
