#ifndef ESCRITORNODOSLIBRES_H_
#define ESCRITORNODOSLIBRES_H_

#include "../EstructurasEnComun/Constantes.h"
#include "../ModuloDePersistencia/Persistencia.h"
#include <iostream>
#include <fstream>
#include <list>
#include <string>
#include <vector>
#include "../ManejadoresDeArchivos/HandlerDeBloques.h"
using namespace  std;

class EscritorNodosLibres {
private:
	char * buffer;
	std::string path;
	HandlerDeBloques* handler;
	void serializarPrimeraHoja(int primeraHoja, char * buffer, unsigned int &offset);
	void serializarNodosLibres(vector<int> nodosLibres, char * buffer, unsigned int &offset);
public:
	EscritorNodosLibres();
	EscritorNodosLibres (std::string path);
	void GrabarDatosConfig(int primeraHoja , vector<int> nodosLibres);
	virtual ~EscritorNodosLibres();
};

#endif /* ESCRITORNODOSLIBRES_H_ */
