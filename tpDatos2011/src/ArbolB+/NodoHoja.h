
#ifndef NODOHOJA_H_
#define NODOHOJA_H_

#include "Nodo.h"
using namespace std;

class NodoHoja : public Nodo {
	friend class ArbolBMas;
	friend class IteradorArbol;
private:
	int hojaSiguiente;
	list<Elementos*> datos;

public:
	NodoHoja();
	virtual ~NodoHoja();

	void Serializar(char * buffer, unsigned int &offset);
	void Hidratar(char * buffer, unsigned int &offset);

	list<Elementos*> getDatos() const
    {
        return datos;
    }

    int getHojaSiguiente() const
    {
        return hojaSiguiente;
    }
    void modificarDatos(int posicion, Elementos* dato);
    Elementos* obtenerDato(int posicion);
};

#endif /* NODOHOJA_H_ */
