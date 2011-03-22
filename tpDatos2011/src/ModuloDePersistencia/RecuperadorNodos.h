#ifndef RECUPERADORNODOS_H_
#define RECUPERADORNODOS_H_

#include <string>
#include <fstream>
#include <iostream>
#include "../ArbolB+/Nodo.h"
#include "../ArbolB+/NodoHoja.h"
#include "../ArbolB+/NodoInterior.h"
#include "../EstructurasEnComun/Constantes.h"
class RecuperadorNodos {

private:
	std::string path;
	std::ifstream iss;
public:
	RecuperadorNodos();
	RecuperadorNodos (std::string path);
	Nodo * obtenerNodo(int nroNodo, int tipoNodo);
	virtual ~RecuperadorNodos();
	void close(){
		iss.close();
	}
};

#endif /* RECUPERADORNODOS_H_ */
