#ifndef SOLUCION_H_
#define SOLUCION_H_

#include "NodoHoja.h"

class Solucion {
private:
	int nodo;
	int posicion;
public:
	Solucion(){
		this->nodo = 0;
		this->posicion = 0;
	}
	virtual ~Solucion(){
	}
    int getNodo() const{
        return nodo;
    }

    int getPosicion() const{
        return posicion;
    }

    void setNodo(int nodo){
        this->nodo = nodo;
    }

    void setPosicion(int posicion){
        this->posicion = posicion;
    }

};

#endif /* SOLUCION_H_ */
