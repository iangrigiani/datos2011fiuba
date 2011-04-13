#ifndef ESCRITORNODO_H_
#define ESCRITORNODO_H_

#include <string>
#include <fstream>
#include <iostream>
#include <stdlib.h>
#include "../ArbolB+/Nodo.h"
#include "../ArbolB+/NodoInterior.h"
#include "../ArbolB+/NodoHoja.h"
#include "../ManejadoresDeArchivos/HandlerBloquesOtraVersion.h"

class EscritorNodo{
private:
	std::string path;
	std::string pathEspacioLibre;
	char* buffer;
	HandlerBloquesOtraVersion* handler;
public:
	EscritorNodo();
	EscritorNodo (std::string path , std::string pathEspaciosLibres);
	void ActualizarArchivoNodo(class Nodo * node, int nivel);
	virtual ~EscritorNodo();
};

#endif /* ESCRITORNODO_H_ */
