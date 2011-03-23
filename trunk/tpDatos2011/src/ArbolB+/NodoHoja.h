
#ifndef NODOHOJA_H_
#define NODOHOJA_H_

#include "Nodo.h"
using namespace std;

class NodoHoja : public Nodo {
	friend class ArbolBMas;
	friend class IteradorArbol;
private:
	int hojaSiguiente;
	Elementos* datos;

public:
	NodoHoja();
	virtual ~NodoHoja();

	void serializar(char * buffer, unsigned int &offset);
	void hidratar(char * buffer, unsigned int &offset);

	Elementos* getDatos() const{
        return datos;
    }

    int getHojaSiguiente() const{
        return hojaSiguiente;
    }
};

#endif /* NODOHOJA_H_ */
