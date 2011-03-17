
#include "IteradorArbol.h"


IteradorArbol::IteradorArbol() {
	this->nodoActual = NULL;
//	this->persistor = NULL;
	this->posicionActual = 0;
}

//IteradorArbol::IteradorArbol(NodoHoja *hojaCorriente, int posicionActual, Persistor* persistor) {
//	this->nodoActual = hojaCorriente;
//	this->persistor = persistor;
//	this->posicionActual = posicionActual;
//}

IteradorArbol::~IteradorArbol() {
	if (nodoActual)
		delete nodoActual;
}

bool IteradorArbol::hasNext() {
	if (nodoActual) {
		if(posicionActual < nodoActual->cantidadClaves)
			return true;
		else
			if (nodoActual->hojaSiguiente != 0)
				return true;
			else {
				posicionActual = 0;
				delete nodoActual;
				nodoActual = NULL;
				return false;
			}
	}
	return false;
}

Registro* IteradorArbol::next() {
//	if (!hasNext())
//		return NULL;
//
//	if (posicionActual == nodoActual->cantidadClaves){
//		NodoHoja *nuevoNodoHoja = new NodoHoja();
//		CadenaBytes cadena = persistor->leerBloque(nodoActual->hojaSiguiente);
//		nuevoNodoHoja->Hidratar(cadena);
//		nuevoNodoHoja->numero = nodoActual->hojaSiguiente;
//		if (nodoActual)
//			delete nodoActual;
//		nodoActual = nuevoNodoHoja;
//		posicionActual = 0;
//	}
//	Registro* registro = new Registro(nodoActual->claves[posicionActual].Clonar(), new CadenaBytes(nodoActual->datos[posicionActual]));
//	posicionActual++;
//	return registro;
}
