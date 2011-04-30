#ifndef ESCRITORNODO_H_
#define ESCRITORNODO_H_

#include <string>
#include <fstream>
#include <iostream>
#include <stdlib.h>
#include "../ArbolB+/Nodo.h"
#include "../ArbolB+/NodoInterior.h"
#include "../ArbolB+/NodoHoja.h"
#include "../ManejadoresDeArchivos/HandlerBloques.h"

class EscritorNodo{
private:
	std::string path;
	char* buffer;
	HandlerBloques* handler;
public:
	EscritorNodo();
	EscritorNodo (std::string path);
	void ActualizarArchivoNodo(class Nodo * node, int nro_bloque);
	virtual ~EscritorNodo();
};

#endif /* ESCRITORNODO_H_ */
