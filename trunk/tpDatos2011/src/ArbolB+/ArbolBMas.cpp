
#include "ArbolBMas.h"
#include <iostream>

ArbolBMas::ArbolBMas(string ruta_archivo, int tamanioMaximoClave){

}

ArbolBMas::~ArbolBMas(){
	if	(raiz){
		liberarMemoriaNodo(raiz);
	}
}

NodoHoja* ArbolBMas::obtenerNodoHoja(){
	NodoHoja* nodoHoja = new NodoHoja();
	return nodoHoja;
}
NodoInterior* ArbolBMas::obtenerNodoInterior(int nivel){
	NodoInterior* nodoInterior = new NodoInterior(nivel);
	return nodoInterior;
}
void ArbolBMas::grabarDatosConfiguracion(){
	string nombreArchivo = PATH_CONFIGURACION;
	EscritorNodosLibres * escritor = new EscritorNodosLibres(nombreArchivo);
	escritor->GrabarDatosConfig(primeraHoja, nodosLibres);
}
bool ArbolBMas::insertar(Registro* registro){
	/* Si el tamanio del registro que quiero insertar es mayor al porcentaje minimo por nodo, lanzo una excepcion */
	if ((int)registro->getTamanio() > (TAM_EFECTIVO_NODO * PORCENTAJE_NODO / 100)
			|| registro->getClave()->getTamanio() > maxTamanioClave)
		throw new exception;

	Nodo* nuevoNodoHijo = NULL;
	ClaveNumerica clavePromocion;
	if (raiz == NULL) {
		raiz = obtenerNodoHoja();
		raiz->numero = primeraHoja = 0;
		grabarDatosConfiguracion();
		(static_cast <NodoHoja*> (raiz))->hojaSiguiente = 0;
		this->cantidadNodos = 1;
	}
	// TODO: OJO ACA VER EL GETAPELLIDOS SEGUN LO QUE DIGA EL ENUNCIADO.

	bool resultado = insertarRecursivamente(raiz, *(registro->getClave()), new Elementos(), &clavePromocion, &nuevoNodoHijo);
	//////////////////////////////////////////////////////////////////////////

	if (nuevoNodoHijo){
		persistirNodo(nuevoNodoHijo);
		NodoInterior *nuevaRaiz = obtenerNodoInterior(raiz->nivel + 1);
		// Muevo la raiz a otra posicion y persisto la nueva raiz en la posicion cero
		raiz->numero = obtenerNumeroNodo();
		if (raiz->isNodoHoja()) {
			primeraHoja = raiz->numero;
			grabarDatosConfiguracion();
		}
		persistirNodo(raiz);
		nuevaRaiz->claves.push_back(&clavePromocion);
		nuevaRaiz->hijos.push_back(&(raiz->numero));
		nuevaRaiz->hijos.push_back(&(nuevoNodoHijo->numero));
		nuevaRaiz->cantidadClaves = 1;
		nuevaRaiz->espacioOcupado += clavePromocion.getTamanio() + TAM_CONTROL_REGISTRO;
		nuevaRaiz->numero = 0;
		persistirNodo(nuevaRaiz);
		liberarMemoriaNodo(raiz);
		liberarMemoriaNodo(nuevoNodoHijo);
		raiz = nuevaRaiz;
	} else {
		persistirNodo(raiz);
	}
	return resultado;
}

bool ArbolBMas::insertarRecursivamente(Nodo* nodoCorriente, ClaveNumerica clave, Elementos* dato, ClaveNumerica* clavePromocion, Nodo** nuevoNodo){
	if (!nodoCorriente->isNodoHoja()) {
		NodoInterior *nodoInteriorCorriente = static_cast<NodoInterior*> (nodoCorriente);
		ClaveNumerica nuevaClave;
		Nodo* nuevoNodoHijo = NULL;
		int posicion = obtenerPosicion(nodoInteriorCorriente, clave);
		Nodo* nodoHijo = hidratarNodo(nodoInteriorCorriente->obtenerHijo(posicion), 2);

		bool resultado = insertarRecursivamente(nodoHijo, clave, dato, &nuevaClave, &nuevoNodoHijo);

		if (nuevoNodoHijo) {

			if (nodoInteriorCorriente->isOverflow(nuevaClave.getTamanio() + TAM_CONTROL_REGISTRO + maxTamanioClave)) {

				dividirNodoInterior(nodoInteriorCorriente, clavePromocion, nuevoNodo, posicion);

				if (posicion == nodoInteriorCorriente->cantidadClaves + 1
						&& nodoInteriorCorriente->cantidadClaves < (*nuevoNodo)->cantidadClaves) {

					NodoInterior *nuevoNodoInterior = static_cast<NodoInterior*> (*nuevoNodo);
					modificarClave(nodoInteriorCorriente,nodoInteriorCorriente->cantidadClaves, clavePromocion);
					modificarHijo(nodoInteriorCorriente, nodoInteriorCorriente->cantidadClaves + 1,nuevoNodoInterior->obtenerHijo(0));
					nodoInteriorCorriente->cantidadClaves++;
					nodoInteriorCorriente->espacioOcupado += (*clavePromocion).getTamanio() + TAM_CONTROL_REGISTRO;
					modificarHijo(nuevoNodoInterior, 0,nuevoNodoHijo->numero);
					*clavePromocion = nuevaClave;
					persistirNodo(nuevoNodoHijo);
					liberarMemoriaNodo(nuevoNodoHijo);
					persistirNodo(nodoHijo);
					liberarMemoriaNodo(nodoHijo);
					return resultado;
				} else {
					if (posicion >= nodoInteriorCorriente->cantidadClaves + 1) {
						posicion -= (nodoInteriorCorriente->cantidadClaves + 1);
						nodoInteriorCorriente = static_cast<NodoInterior*> (*nuevoNodo);
					}
				}
			}

			int i = nodoInteriorCorriente->cantidadClaves;
			while (i > posicion) {
				modificarClave(nodoInteriorCorriente, i, obtenerClaveNumerica(nodoInteriorCorriente,i - 1));
				modificarHijo(nodoInteriorCorriente, i + 1,nodoInteriorCorriente->obtenerHijo(i));
				i--;
			}
			modificarClave(nodoInteriorCorriente,posicion,&nuevaClave);
			modificarHijo(nodoInteriorCorriente, posicion + 1,nuevoNodoHijo->numero);
			nodoInteriorCorriente->cantidadClaves++;
			nodoInteriorCorriente->espacioOcupado += nuevaClave.getTamanio() + TAM_CONTROL_REGISTRO;
			persistirNodo(nuevoNodoHijo);
			liberarMemoriaNodo(nuevoNodoHijo);
		}
		persistirNodo(nodoHijo);
		liberarMemoriaNodo(nodoHijo);
		return resultado;

	} else {
		NodoHoja *nodoHojaCorriente = static_cast<NodoHoja*> (nodoCorriente);
		int posicion = obtenerPosicion(nodoHojaCorriente, clave);
		// chequea que no exista la clave
		ClaveNumerica* claveNodo = obtenerClaveNumerica(nodoHojaCorriente,posicion);
		if (posicion < nodoHojaCorriente->cantidadClaves && clave.getValorClave() == claveNodo->getValorClave()){
			return false;
		}
		delete claveNodo;
		int i = nodoHojaCorriente->cantidadClaves - 1;
		ClaveNumerica* claveAux = obtenerClaveNumerica(nodoHojaCorriente,i);
		while (i >= 0 && clave.getValorClave() < claveAux->getValorClave()){
			modificarClave(nodoHojaCorriente, i + 1, claveAux);
			nodoHojaCorriente->modificarDatos(i + 1, nodoHojaCorriente->obtenerDato(i));
			i--;
			claveAux = obtenerClaveNumerica(nodoHojaCorriente,i);
		}
		delete claveAux;
		modificarClave(nodoHojaCorriente, i + 1, &clave);

		nodoHojaCorriente->modificarDatos(i + 1, dato);
		nodoHojaCorriente->cantidadClaves++;
		nodoHojaCorriente->espacioOcupado += dato->getTamanio() + clave.getTamanio() + TAM_CONTROL_REGISTRO;
		if (nodoHojaCorriente->isOverflow(maxTamanioClave)) {

			dividirNodoHoja(nodoHojaCorriente, clavePromocion, nuevoNodo);

			if (posicion >= nodoHojaCorriente->cantidadClaves) {
				posicion -= nodoHojaCorriente->cantidadClaves;
				nodoHojaCorriente = static_cast<NodoHoja*> (*nuevoNodo);
			}
		}
		if (nuevoNodo && nodoHojaCorriente != *nuevoNodo && posicion == nodoHojaCorriente->cantidadClaves - 1) {
			*clavePromocion = clave;
		}
		return true;
	}
}

int ArbolBMas::obtenerNumeroNodo(){
	int numeroDeNodo;
	if (nodosLibres.empty()) {
		this->cantidadNodos++;
		numeroDeNodo = this->cantidadNodos-1;
	} else {
		numeroDeNodo = nodosLibres.back();
		nodosLibres.pop_back();
		grabarDatosConfiguracion();
	}
	return numeroDeNodo;
}

void ArbolBMas::persistirNodo(Nodo* nodo){
	EscritorNodo* escritor = new EscritorNodo(PATH_NODOS);
	escritor->ActualizarArchivoNodo(nodo);
}

Nodo* ArbolBMas::hidratarNodo(int nroNodo, int tipoNodo){
	RecuperadorNodos* recuperador = new RecuperadorNodos(PATH_NODOS);
	return recuperador->obtenerNodo(nroNodo, tipoNodo);
}

void ArbolBMas::liberarMemoriaNodo(Nodo* nodo){
	if (nodo->isNodoHoja()) {
		delete static_cast<NodoHoja*> (nodo);
	} else {
		delete static_cast<NodoInterior*> (nodo);
	}
}

int ArbolBMas::obtenerPosicion(Nodo *unNodo, ClaveNumerica clave) {

	if (unNodo->cantidadClaves == 0)
		return 0;
	int inferior = 0;
	int superior = (unNodo->cantidadClaves)-1;

	while (inferior < superior) {
		int medio = (inferior + superior) / 2;
		ClaveNumerica* claveNodo = obtenerClaveNumerica(unNodo,medio);
		if (clave.getValorClave() <= claveNodo->getValorClave()) {
			superior = medio - 1;
		} else {
			inferior = medio + 1;
		}
	}
	ClaveNumerica* claveNodoSup = obtenerClaveNumerica(unNodo,superior);
	if (superior < 0 || (claveNodoSup->getValorClave() < clave.getValorClave()))
		superior++;

	return superior;
}

ClaveNumerica* ArbolBMas::obtenerClaveNumerica(Nodo* nodo, int posicion){
	int cont = 0;
	ClaveNumerica* claveRetornada;
	list<ClaveNumerica*>::iterator it = nodo->getClaves().begin();
	while ( it != nodo->getClaves().end()){
		if (cont == posicion){
			claveRetornada = (*it);
			return claveRetornada;
		}
		++cont;
		++it;
	}
	return NULL;
}

void ArbolBMas::dividirNodoInterior(NodoInterior* nodoInteriorActual, ClaveNumerica* clavePromocion, Nodo** nuevoNodoInterior, int nuevaPosicion){

	int medio = nodoInteriorActual->cantidadClaves / 2;

	if (nuevaPosicion <= medio && medio > nodoInteriorActual->cantidadClaves - (medio + 1)) {
		medio--;
	}

	NodoInterior *auxNuevoNodoInterior = obtenerNodoInterior(nodoInteriorActual->nivel);
	auxNuevoNodoInterior->numero = obtenerNumeroNodo();
	auxNuevoNodoInterior->cantidadClaves = nodoInteriorActual->cantidadClaves - (medio + 1);
	for (int posicion = medio + 1; posicion < nodoInteriorActual->cantidadClaves; ++posicion) {
		int auxPosicion = posicion - (medio + 1);
		modificarClave(auxNuevoNodoInterior, auxPosicion, obtenerClaveNumerica(nodoInteriorActual,posicion));
		modificarHijo(auxNuevoNodoInterior,auxPosicion, nodoInteriorActual->obtenerHijo(posicion));
		auxNuevoNodoInterior->espacioOcupado += obtenerClaveNumerica(nodoInteriorActual,posicion)->getTamanio() + TAM_CONTROL_REGISTRO;
	}
	modificarHijo(auxNuevoNodoInterior,auxNuevoNodoInterior->cantidadClaves,nodoInteriorActual->obtenerHijo(nodoInteriorActual->cantidadClaves));
	nodoInteriorActual->cantidadClaves = medio;
	nodoInteriorActual->espacioOcupado -= auxNuevoNodoInterior->espacioOcupado;
	*clavePromocion = *obtenerClaveNumerica(nodoInteriorActual,medio);
	*nuevoNodoInterior = auxNuevoNodoInterior;
}

void ArbolBMas::dividirNodoHoja(NodoHoja* nodoHojaActual, ClaveNumerica* clavePromocion, Nodo** nuevoNodoHoja){
	int espacioMedio = (nodoHojaActual->espacioOcupado) / 2;
	int espacioNodoIzquierdo = 0;
	int cantidadClaves = 0;
	while (cantidadClaves < nodoHojaActual->cantidadClaves && espacioNodoIzquierdo < espacioMedio){
		espacioNodoIzquierdo += nodoHojaActual->obtenerDato(cantidadClaves)->getTamanio() + obtenerClaveNumerica(nodoHojaActual, cantidadClaves)->getTamanio() + TAM_CONTROL_REGISTRO;
		cantidadClaves++;
		if (espacioNodoIzquierdo > TAM_EFECTIVO_NODO) {
			cantidadClaves--;
			espacioNodoIzquierdo -= nodoHojaActual->obtenerDato(cantidadClaves)->getTamanio() + obtenerClaveNumerica(nodoHojaActual, cantidadClaves)->getTamanio() + TAM_CONTROL_REGISTRO;
			break;
		}
	}

	NodoHoja *auxNuevoNodoHoja = obtenerNodoHoja();
	auxNuevoNodoHoja->numero = obtenerNumeroNodo();
	auxNuevoNodoHoja->cantidadClaves = nodoHojaActual->cantidadClaves - cantidadClaves;
	auxNuevoNodoHoja->espacioOcupado = nodoHojaActual->espacioOcupado - espacioNodoIzquierdo;
	auxNuevoNodoHoja->hojaSiguiente = nodoHojaActual->hojaSiguiente;

	for (int posicion = cantidadClaves; posicion < nodoHojaActual->cantidadClaves; ++posicion) {
		int auxPosicion = posicion - cantidadClaves;
		modificarClave(auxNuevoNodoHoja, auxPosicion, obtenerClaveNumerica(nodoHojaActual, posicion));
		auxNuevoNodoHoja->modificarDatos(auxPosicion, nodoHojaActual->obtenerDato(posicion));
	}

	nodoHojaActual->espacioOcupado -= auxNuevoNodoHoja->espacioOcupado;
	nodoHojaActual->cantidadClaves = cantidadClaves;
	nodoHojaActual->hojaSiguiente = auxNuevoNodoHoja->numero;
	*clavePromocion = *obtenerClaveNumerica(nodoHojaActual, nodoHojaActual->cantidadClaves - 1);
	*nuevoNodoHoja = auxNuevoNodoHoja;
}

void ArbolBMas::modificarClave(Nodo* nodo,int posicion, ClaveNumerica* clave){
	bool encontrado = false;
	int cont = 0;
	list<ClaveNumerica*>::iterator it = nodo->getClaves().begin();
	while ( it != nodo->getClaves().end() && !encontrado){
			if (cont == posicion){
				encontrado = true;
				(*(*it)) = (*clave);
			}
			++it;
			++cont;
	}
}

void ArbolBMas::modificarHijo(NodoInterior* nodo, int posicion, int valor){
	bool encontrado = false;
	int cont = 0;
	list<int*>::iterator it = nodo->getHijos().begin();
	while ( it != nodo->getHijos().end() && !encontrado){
			if (cont == posicion){
				encontrado = true;
				(*(*it)) = valor;
			}
			++it;
			++cont;
	}
}

void ArbolBMas::toString(){

}
