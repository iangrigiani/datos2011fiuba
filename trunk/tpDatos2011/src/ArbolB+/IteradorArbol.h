
#ifndef ITERADORARBOL_H_
#define ITERADORARBOL_H_

#include "NodoHoja.h"
#include "../EstructurasEnComun/Registro.h"
#include "../ModuloDePersistencia/Persistencia.h"

class IteradorArbol {

private:
	NodoHoja* nodoActual;
	int posicionActual;

public:
	IteradorArbol();
//	IteradorArbol(NodoHoja *hojaCorriente, int posicionActual, Persistor* persistor);
	virtual ~IteradorArbol();
	bool hasNext();
	Registro* next();
};

#endif /* ITERADORARBOL_H_ */