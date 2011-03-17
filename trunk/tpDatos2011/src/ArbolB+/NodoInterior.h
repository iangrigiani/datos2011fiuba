
#ifndef NODOINTERIOR_H_
#define NODOINTERIOR_H_

#include "Nodo.h"
using namespace std;

class NodoInterior : public Nodo {
	friend class ArbolBMas;
	friend class IteradorArbol;
private:
	list<int*> hijos;

public:
	NodoInterior(int nivel);
	virtual ~NodoInterior();

	void serializar(char * buffer, unsigned int &offset);
	void hidratar(char * buffer, unsigned int &offset);
    list<int*> getHijos() const
    {
        return hijos;
    }
};

#endif /* NODOINTERIOR_H_ */
