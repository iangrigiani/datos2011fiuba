#ifndef NODO_H_
#define NODO_H_

#include "../EstructurasEnComun/ClaveNumerica.h"
#include "../EstructurasEnComun/Constantes.h"
//#include "../ModuloDePersistencia/Persistencia.h"
#include "Elementos.h"
#include <vector>
#include <string.h>
using namespace std;

class Nodo : public Serializable{
	friend class ArbolBMas;
	friend class NodoInterior;
	friend class NodoHoja;
	friend class IteradorArbol;

private:
	int numero;
	int nivel;
	int offset;
	int espacioOcupado;
	int cantidadClaves;
	ClaveNumerica* claves;

public:
	Nodo(int nivel);
	virtual ~Nodo();

	bool isNodoHoja();
	bool isOverflow(int);
	bool isUnderflow();
	bool puedeCederElementos();

    int getCantidadClaves() const
    {
        return cantidadClaves;
    }

    ClaveNumerica* getClaves() const
    {
        return claves;
    }

    int getEspacioOcupado() const
    {
        return espacioOcupado;
    }

    int getNivel() const
    {
        return nivel;
    }

    int getNumero() const
    {
        return numero;
    }
    int getOffset() const{
    	return offset;
    }
};

#endif /* NODO_H_ */
