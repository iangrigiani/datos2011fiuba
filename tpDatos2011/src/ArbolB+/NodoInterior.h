
#ifndef NODOINTERIOR_H_
#define NODOINTERIOR_H_

#include "Nodo.h"
using namespace std;

class NodoInterior : public Nodo {
	friend class ArbolBMas;

private:
	int* hijos;

public:
	NodoInterior(int nivel);
	NodoInterior();
	virtual ~NodoInterior();

	void serializar(char * buffer, unsigned int &offset);
	void hidratar(char * buffer, unsigned int &offset);
    int* getHijos() const
    {
        return hijos;
    }
    int obtenerHijo(int posicion);
    int obtenerNivel (char* buffer);
};

#endif /* NODOINTERIOR_H_ */
