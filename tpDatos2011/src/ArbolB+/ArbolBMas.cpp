
#include "ArbolBMas.h"
#include <iostream>

ArbolBMas::ArbolBMas(int tipo, string ruta_archivo, int tamanioMaximoClave){
	this->tipo = tipo;
	this->primeraHoja = 0;
	this->path = ruta_archivo;
	this->maxTamanioClave = tamanioMaximoClave;
	inicializarPersistores();
	this->raiz = hidratarNodo(0,1);
	if (this->raiz) {
		this->cantidadNodos = this->recuperador_Nodos->getTamanioArchivo() / TAM_TOTAL_NODO;
	} else {
		this->cantidadNodos = 0;
	}
	hidratarDatosConfiguracion();
}

void ArbolBMas::inicializarPersistores(){
	this->recuperador_Nodos = new RecuperadorNodos(this->path);
	this->escritor_Nodos = new EscritorNodo(this->path);
	if(this->tipo == 1){
		this->escritor_Datos_Configuracion = new EscritorNodosLibres(PATH_CONFIGURACION_AUTORES);
		this->recuperador_Datos_Configuracion = new RecuperadorNodosLibres(PATH_CONFIGURACION_AUTORES);
	}else{
		this->escritor_Datos_Configuracion = new EscritorNodosLibres(PATH_CONFIGURACION_EDITORIAL);
		this->recuperador_Datos_Configuracion = new RecuperadorNodosLibres(PATH_CONFIGURACION_EDITORIAL);
	}

}
ArbolBMas::~ArbolBMas(){
	if	(raiz){
		liberarMemoriaNodo(raiz);
	}
	delete this->escritor_Nodos;
	delete this->recuperador_Nodos;
	delete this->escritor_Datos_Configuracion;
	delete this->recuperador_Datos_Configuracion;
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
	escritor_Datos_Configuracion->GrabarDatosConfig(primeraHoja, nodosLibres);
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
//		this->MostrarArbol(nuevoNodoHijo);
		NodoInterior *nuevaRaiz = obtenerNodoInterior(raiz->nivel + 1);
		// Muevo la raiz a otra posicion y persisto la nueva raiz en la posicion cero
		raiz->numero = obtenerNumeroNodo();
		if (raiz->isNodoHoja()) {
			primeraHoja = raiz->numero;
			grabarDatosConfiguracion();
		}
		persistirNodo(raiz);
//		this->MostrarArbol(raiz);
		nuevaRaiz->claves[0] = clavePromocion;
		nuevaRaiz->hijos[0] = raiz->numero;
		nuevaRaiz->hijos[1] = nuevoNodoHijo->numero;
		nuevaRaiz->cantidadClaves = 1;
		nuevaRaiz->espacioOcupado += clavePromocion.getTamanio() + TAM_CONTROL_REGISTRO;
		nuevaRaiz->numero = 0;
		persistirNodo(nuevaRaiz);
//		this->MostrarArbol(nuevaRaiz);
		liberarMemoriaNodo(raiz);
		liberarMemoriaNodo(nuevoNodoHijo);
		raiz = nuevaRaiz;
	} else {
		persistirNodo(raiz);
	}
	return resultado;
}

//list<Elementos*> ArbolBMas::buscar(Clave clave) {
//
//}


bool ArbolBMas::insertarRecursivamente(Nodo* nodoCorriente, Clave& clave, Elementos* dato, Clave* clavePromocion, Nodo** nuevoNodo){
	if (!nodoCorriente->isNodoHoja()) {
		NodoInterior *nodoInteriorCorriente = static_cast<NodoInterior*> (nodoCorriente);
		Clave nuevaClave;
		Nodo* nuevoNodoHijo = NULL;
		int posicion = obtenerPosicion(nodoInteriorCorriente, clave);
		int tipoNodo = 0;
		if (nodoInteriorCorriente->nivel > 1 ){
			tipoNodo = 2;
		}else{
			tipoNodo = 1;
		}
		Nodo* nodoHijo = hidratarNodo(nodoInteriorCorriente->hijos[posicion], tipoNodo);

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
	escritor_Nodos->ActualizarArchivoNodo(nodo, nodo->getNumero());
}

Nodo* ArbolBMas::hidratarNodo(int nroNodo, int tipoNodo){
	return (recuperador_Nodos->obtenerNodo(nroNodo, tipoNodo));
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
	int superior = (unNodo->cantidadClaves) - 1;

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

void ArbolBMas::dividirNodoHoja(NodoHoja* unNodoHoja, Clave* clavePromocion, Nodo** nuevoNodoHoja){
	int espacioMedio = (unNodoHoja->espacioOcupado) / 2;
	int espacioNodoIzquierdo = 0;
	int cantidadClaves = 0;
	while (cantidadClaves < unNodoHoja->cantidadClaves && espacioNodoIzquierdo < espacioMedio){
		espacioNodoIzquierdo += unNodoHoja->datos[cantidadClaves].getTamanio() + unNodoHoja->claves[cantidadClaves].getTamanio() + TAM_CONTROL_REGISTRO;
		cantidadClaves++;
		if (espacioNodoIzquierdo > TAM_EFECTIVO_NODO) {
			cantidadClaves--;
			espacioNodoIzquierdo -= (unNodoHoja->datos[cantidadClaves].getTamanio() + unNodoHoja->claves[cantidadClaves].getTamanio() + TAM_CONTROL_REGISTRO);
			break;
		}
	}

	NodoHoja *auxNuevoNodoHoja = obtenerNodoHoja();
	auxNuevoNodoHoja->numero = obtenerNumeroNodo();
	auxNuevoNodoHoja->cantidadClaves = unNodoHoja->cantidadClaves - cantidadClaves;
	auxNuevoNodoHoja->espacioOcupado = unNodoHoja->espacioOcupado - espacioNodoIzquierdo;
	auxNuevoNodoHoja->hojaSiguiente = unNodoHoja->hojaSiguiente;

	for (int posicion = cantidadClaves; posicion < unNodoHoja->cantidadClaves; ++posicion) {
		int auxPosicion = posicion - cantidadClaves;
		auxNuevoNodoHoja->claves[auxPosicion] = unNodoHoja->claves[posicion];
		auxNuevoNodoHoja->datos[auxPosicion] = unNodoHoja->datos[posicion];
	}

	unNodoHoja->espacioOcupado -= auxNuevoNodoHoja->espacioOcupado;
	unNodoHoja->cantidadClaves = cantidadClaves;
	unNodoHoja->hojaSiguiente = auxNuevoNodoHoja->numero;
	*clavePromocion = unNodoHoja->claves[unNodoHoja->cantidadClaves - 1];
	*nuevoNodoHoja = auxNuevoNodoHoja;
}

void ArbolBMas::MostrarArbol (Nodo* nodo){
	if (nodo){
		toString(nodo,1);
	}
}
void ArbolBMas::MostrarArbol (){
	if (this->raiz){
		toString(this->raiz,1);
	}
}

void ArbolBMas::toString(Nodo* nodoAmostrar, int tab){
	if(nodoAmostrar){
		if (nodoAmostrar->isNodoHoja()) {
			NodoHoja *nodo = static_cast<NodoHoja*> (nodoAmostrar);
			for(int i=0 ; i<tab ; i++) cout << "  ";
				cout   << "Numero: " << nodo->numero << "  Nivel: " << nodo->nivel << "  Cant.Elem: " << nodo->cantidadClaves
				<< " Esp.Libre: " << TAM_EFECTIVO_NODO - nodo->espacioOcupado << "  Hoja.Sig: " << nodo->hojaSiguiente << "    " << endl;

			for(int i=0 ; i<tab ; i++) cout << "  ";
			for (int posicion = 0; posicion < nodo->cantidadClaves; ++posicion){
				cout << "(";
				Clave clave = nodo->claves[posicion];
				cout << clave.getClave() ;
				cout << ")";
			}
			cout << endl;
		} else {
			NodoInterior *nodoInt= static_cast<NodoInterior*> (nodoAmostrar);
			cout << endl;
			for(int i=0; i<tab ; i++)
				cout << "  ";
			cout << "Numero: " << nodoInt->numero << "  Nivel: " << nodoInt->nivel << "  Cant.Elem: " << nodoInt->cantidadClaves
					<< "  Esp.Libre: " << TAM_EFECTIVO_NODO - nodoInt->espacioOcupado << "  Claves: (";
			for (int posicion = 0; posicion <= nodoInt->cantidadClaves; ++posicion) {
				if (posicion < nodoInt->cantidadClaves) {
					Clave clave = nodoInt->claves[posicion];
					cout << clave.getClave();
					if (posicion == nodoInt->cantidadClaves-1){
						cout << ")" << endl;
					}else{
						cout << "," ;
					}
				}
			}
			for (int posicion = 0; posicion <= nodoInt->cantidadClaves; ++posicion) {
				int tipoNodo = 0;
				if (nodoInt->nivel > 1 ){
					tipoNodo = 2;
				}else{
					tipoNodo = 1;
				}
				Nodo *hijo = hidratarNodo(posicion+1,tipoNodo);
				toString(hijo, tab+2);
				if (hijo)
					liberarMemoriaNodo(hijo);
			}
			cout << endl;
		}
	}
}

void ArbolBMas::hidratarDatosConfiguracion(){
	nodosLibres.clear();
	recuperador_Datos_Configuracion->obtenerDatos(primeraHoja,nodosLibres);
}
