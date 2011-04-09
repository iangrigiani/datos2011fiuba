
#include "ArbolBMas.h"
#include <iostream>

ArbolBMas::ArbolBMas(string ruta_archivo, int tamanioMaximoClave){
	this->primeraHoja = 0;
	this->maxTamanioClave = tamanioMaximoClave;
	RecuperadorNodos* recup = new RecuperadorNodos(PATH_NODOS);
	this->raiz = hidratarNodo(0,1);
	if (this->raiz) {
		this->cantidadNodos = recup->getTamanioArchivo() / TAM_TOTAL_NODO;
	} else {
		this->cantidadNodos = 0;
	}
	hidratarDatosConfiguracion();
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
bool ArbolBMas::insertar(Elementos* elemento){
	/* Si el tamanio del registro que quiero insertar es mayor al porcentaje minimo por nodo, lanzo una excepcion */
	if ((int)elemento->getTamanio() > (TAM_EFECTIVO_NODO * PORCENTAJE_NODO / 100)
			|| elemento->getClave()->getTamanio() > maxTamanioClave)
		throw new exception;

	Nodo* nuevoNodoHijo = NULL;
	Clave clavePromocion;
	if (raiz == NULL) {
		raiz = obtenerNodoHoja();
		raiz->numero = primeraHoja = 0;
		grabarDatosConfiguracion();
		(static_cast <NodoHoja*> (raiz))->hojaSiguiente = 0;
		this->cantidadNodos = 1;
	}
	bool resultado = insertarRecursivamente(raiz,*(elemento->getClave()) , elemento, &clavePromocion, &nuevoNodoHijo);

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
		nuevaRaiz->claves[0] = clavePromocion;
		nuevaRaiz->hijos[0] = raiz->numero;
		nuevaRaiz->hijos[1] = nuevoNodoHijo->numero;
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

Elementos* ArbolBMas::buscar(Clave clave) {


//	Nodo *unNodo = raiz;
//
//	if (!unNodo)
//		NULL;
//
//	while (!unNodo->isNodoHoja()) {
//		NodoInterior *unNodoInterior = static_cast<NodoInterior*> (unNodo);
//		int posicion = obtenerPosicion(unNodoInterior, clave);
//		unNodo = hidratarNodo(unNodoInterior->hijos[posicion]);
//		if (unNodoInterior != raiz)
//			liberarMemoriaNodo(unNodoInterior);
//	}
//
//	NodoHoja *unNodoHoja = static_cast<NodoHoja*> (unNodo);
//	Elementos* elemento = NULL;
//	int posicion = obtenerPosicion(unNodoHoja, clave);
//
//	if (posicion < unNodoHoja->cantidadClaves && claveIgual(clave, unNodoHoja->claves[posicion]))
//		elemento = unNodoHoja->datos[posicion];
//	if (unNodoHoja != raiz)
//		liberarMemoriaNodo(unNodoHoja);
//	return elemento;

	//Devuelvo NULL porque debe devolver un elemento
	return NULL;
}


bool ArbolBMas::insertarRecursivamente(Nodo* nodoCorriente, Clave& clave, Elementos* dato, Clave* clavePromocion, Nodo** nuevoNodo){
	if (!nodoCorriente->isNodoHoja()) {
		NodoInterior *nodoInteriorCorriente = static_cast<NodoInterior*> (nodoCorriente);
		Clave nuevaClave;
		Nodo* nuevoNodoHijo = NULL;
		int posicion = obtenerPosicion(nodoInteriorCorriente, clave);
		Nodo* nodoHijo = hidratarNodo(nodoInteriorCorriente->hijos[posicion], 2);

		bool resultado = insertarRecursivamente(nodoHijo, clave, dato, &nuevaClave, &nuevoNodoHijo);

		if (nuevoNodoHijo) {

			if (nodoInteriorCorriente->isOverflow(nuevaClave.getTamanio() + TAM_CONTROL_REGISTRO + maxTamanioClave)) {

				dividirNodoInterior(nodoInteriorCorriente, clavePromocion, nuevoNodo, posicion);

				if (posicion == nodoInteriorCorriente->cantidadClaves + 1
						&& nodoInteriorCorriente->cantidadClaves < (*nuevoNodo)->cantidadClaves) {

					NodoInterior *nuevoNodoInterior = static_cast<NodoInterior*> (*nuevoNodo);
					nodoInteriorCorriente->claves[nodoInteriorCorriente->cantidadClaves] = *clavePromocion;
					nodoInteriorCorriente->hijos[nodoInteriorCorriente->cantidadClaves + 1] = nuevoNodoInterior->hijos[0];
					nodoInteriorCorriente->cantidadClaves++;
					nodoInteriorCorriente->espacioOcupado += (*clavePromocion).getTamanio() + TAM_CONTROL_REGISTRO;
					nuevoNodoInterior->hijos[0] = nuevoNodoHijo->numero;
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
				nodoInteriorCorriente->claves[i] = nodoInteriorCorriente->claves[i - 1];
				nodoInteriorCorriente->hijos[i + 1] = nodoInteriorCorriente->hijos[i];
				i--;
			}
			nodoInteriorCorriente->claves[posicion] = nuevaClave;
			nodoInteriorCorriente->hijos[posicion + 1] = nuevoNodoHijo->numero;
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
		if (posicion < nodoHojaCorriente->cantidadClaves && clave.getClave() == nodoHojaCorriente->claves[posicion].getClave()){
			return false;
		}

		int i = nodoHojaCorriente->cantidadClaves-1;
		while (i >= 0 && clave.getClave() < nodoHojaCorriente->claves[i].getClave()){
			nodoHojaCorriente->claves[i + 1] = nodoHojaCorriente->claves[i];
			nodoHojaCorriente->datos[i + 1] = nodoHojaCorriente->datos[i];
			i--;
		}

		nodoHojaCorriente->datos[i + 1] = *dato;
		nodoHojaCorriente->claves[i + 1] = clave;
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

int ArbolBMas::obtenerPosicion(Nodo *unNodo, Clave clave) {

	if (unNodo->cantidadClaves == 0)
		return 0;
	int inferior = 0;
	int superior = (unNodo->cantidadClaves);

	while (inferior < superior) {
		int medio = (inferior + superior) / 2;
		if (clave.getClave() <= unNodo->claves[medio].getClave()) {
			superior = medio - 1;
		} else {
			inferior = medio + 1;
		}
	}
	if (superior < 0 || (unNodo->claves[superior].getClave() < clave.getClave()))
		superior++;

	return superior;
}

void ArbolBMas::dividirNodoInterior(NodoInterior* nodoInteriorActual, Clave* clavePromocion, Nodo** nuevoNodoInterior, int nuevaPosicion){

	int medio = nodoInteriorActual->cantidadClaves / 2;

	if (nuevaPosicion <= medio && medio > nodoInteriorActual->cantidadClaves - (medio + 1)) {
		medio--;
	}

	NodoInterior *auxNuevoNodoInterior = obtenerNodoInterior(nodoInteriorActual->nivel);
	auxNuevoNodoInterior->numero = obtenerNumeroNodo();
	auxNuevoNodoInterior->cantidadClaves = nodoInteriorActual->cantidadClaves - (medio + 1);
	for (int posicion = medio + 1; posicion < nodoInteriorActual->cantidadClaves; ++posicion) {
		int auxPosicion = posicion - (medio + 1);
		auxNuevoNodoInterior->claves[auxPosicion] = nodoInteriorActual->claves[posicion];
		auxNuevoNodoInterior->hijos[auxPosicion] = nodoInteriorActual->hijos[posicion];
		auxNuevoNodoInterior->espacioOcupado += nodoInteriorActual->claves[posicion].getTamanio() + TAM_CONTROL_REGISTRO;
	}
	auxNuevoNodoInterior->hijos[auxNuevoNodoInterior->cantidadClaves] = nodoInteriorActual->hijos[nodoInteriorActual->cantidadClaves];
	nodoInteriorActual->cantidadClaves = medio;
	nodoInteriorActual->espacioOcupado -= auxNuevoNodoInterior->espacioOcupado;
	*clavePromocion = nodoInteriorActual->claves[medio];
	*nuevoNodoInterior = auxNuevoNodoInterior;
}

void ArbolBMas::dividirNodoHoja(NodoHoja* nodoHojaActual, Clave* clavePromocion, Nodo** nuevoNodoHoja){
	int espacioMedio = (nodoHojaActual->espacioOcupado) / 2;
	int espacioNodoIzquierdo = 0;
	int cantidadClaves = 0;
	while (cantidadClaves < nodoHojaActual->cantidadClaves && espacioNodoIzquierdo < espacioMedio){
		espacioNodoIzquierdo += nodoHojaActual->datos[cantidadClaves].getTamanio() + nodoHojaActual->claves[cantidadClaves].getTamanio() + TAM_CONTROL_REGISTRO;
		cantidadClaves++;
		if (espacioNodoIzquierdo > TAM_EFECTIVO_NODO) {
			cantidadClaves--;
			espacioNodoIzquierdo -= (nodoHojaActual->datos[cantidadClaves].getTamanio() + nodoHojaActual->claves[cantidadClaves].getTamanio() + TAM_CONTROL_REGISTRO);
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
		auxNuevoNodoHoja->claves[auxPosicion] = nodoHojaActual->claves[posicion];
		auxNuevoNodoHoja->datos[auxPosicion] = nodoHojaActual->datos[posicion];
	}

	nodoHojaActual->espacioOcupado -= auxNuevoNodoHoja->espacioOcupado;
	nodoHojaActual->cantidadClaves = cantidadClaves;
	nodoHojaActual->hojaSiguiente = auxNuevoNodoHoja->numero;
	*clavePromocion = nodoHojaActual->claves[nodoHojaActual->cantidadClaves - 1];
	*nuevoNodoHoja = auxNuevoNodoHoja;
}

void ArbolBMas::MostrarArbol (){
	if (raiz){
		toString(raiz,1);
	}
}
void ArbolBMas::toString(Nodo* nodoAmostrar, int tab){
	if(nodoAmostrar){
		if (nodoAmostrar->isNodoHoja()) {
			NodoHoja *nodo = static_cast<NodoHoja*> (nodoAmostrar);
			for(int i=0 ; i<tab ; i++)
				cout   << "Numero: " << nodo->numero << "  Nivel: " << nodo->nivel << "  Cant.Elem: " << nodo->cantidadClaves
				<< " Esp.Libre: " << TAM_EFECTIVO_NODO - nodo->espacioOcupado << "  Hoja.Sig: " << nodo->hojaSiguiente << "    " << endl;
			for (int posicion = 0; posicion < nodo->cantidadClaves; ++posicion){
				cout << "(";
				Clave clave = nodo->claves[posicion];
				cout << clave.getClave() ;
//				clave.toString();
				cout << ";";
				Elementos elemento = nodo->datos[posicion];
//				elemento.toString();
				cout << "Titulo: " << elemento.getClave()->getClave() << "/ Offset: " << elemento.getOffset()  ;
				cout << ")";
			}
			cout << endl;
		} else {

			NodoInterior *nodoInt= static_cast<NodoInterior*> (nodoAmostrar);
			cout << endl;
			for(int i=0; i<tab ; i++)
				cout << "  ";
			cout << "Numero: " << nodoInt->numero << "  Nivel: " << nodoInt->nivel << "  Cant.Elem: " << nodoInt->cantidadClaves
					<< "  Esp.Libre: " << TAM_EFECTIVO_NODO - nodoInt->espacioOcupado << endl;

			for (int posicion = 0; posicion <= nodoInt->cantidadClaves; ++posicion) {

				Nodo *hijo = hidratarNodo(nodoInt->hijos[posicion],2);
				toString(hijo, tab+2);
				if (hijo)
					liberarMemoriaNodo(hijo);

				if (posicion < nodoInt->cantidadClaves) {
					Clave clave = nodoInt->claves[posicion];;

					for(int i=0; i<(tab+1) ; i++)
						cout << "  ";
					cout << "(";
					cout << clave.getClave();
//					clave.toString();
					cout << ")";
					cout << clave.getTamanio();
				}

			}
			cout << endl;
		}
	}
}

void ArbolBMas::hidratarDatosConfiguracion(){
	nodosLibres.clear();
	RecuperadorNodosLibres* recuperador = new RecuperadorNodosLibres(PATH_CONFIGURACION);
	recuperador->obtenerDatos(primeraHoja,nodosLibres);
}
