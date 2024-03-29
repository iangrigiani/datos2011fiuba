#ifndef RECUPERADORNODOSLIBRES_H_
#define RECUPERADORNODOSLIBRES_H_

#include <string>
#include <fstream>
#include <iostream>
#include "../ArbolB+/Nodo.h"
#include "../ArbolB+/NodoHoja.h"
#include "../ManejadoresDeArchivos/HandlerBloques.h"
#include "../ArbolB+/NodoInterior.h"
#include "../EstructurasEnComun/Constantes.h"
class RecuperadorNodosLibres {

private:
	std::string path;
//	char* buffer;
	HandlerBloques* handler;
	void hidratarPrimeraHoja(char* readData, unsigned int &offset, int& primeraHoja);
	void hidratarNodosLibres(char* readData, unsigned int &offset, vector<int>& nodosLibres);
public:
	RecuperadorNodosLibres();
	RecuperadorNodosLibres (std::string path);
	void obtenerDatos(int &primeraHoja, vector<int>& nodosLibres);
	virtual ~RecuperadorNodosLibres();
};

#endif /* RECUPERADORNODOSLIBRES_H_ */
