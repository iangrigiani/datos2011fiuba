#include "ArbolBMas.h"
#include <iostream>

ArbolBMas::ArbolBMas(int tipo, string ruta_archivo){
	this->tipo = tipo;
	this->primeraHoja = 0;
	this->path = ruta_archivo;
	inicializarPersistores();
	this->raiz = hidratarNodo(0);
	if (this->raiz) {
		this->cantidadNodos = this->recuperador_Nodos->getTamanioArchivo() / TAM_TOTAL_NODO;
	} else {
		this->cantidadNodos = 0;
	}
	hidratarDatosConfiguracion();
}

void ArbolBMas::inicializarPersistores(){
	this->recuperador_Nodos = new RecuperadorNodos(PATH_NODOS);
	this->escritor_Nodos = new EscritorNodo(PATH_NODOS);

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
	Nodo* nuevoNodoHijo = NULL;

	Clave nuevaClaveRaiz;
	if (raiz == NULL) {
		raiz = obtenerNodoHoja();
		raiz->numero = primeraHoja = 0;
		grabarDatosConfiguracion();
		(static_cast <NodoHoja*> (raiz))->hojaSiguiente = 0;
		this->cantidadNodos = 1;
	}
	string palabra = elemento->getClave()->getClave();

	// Saco el frontcoding antes de insertar recursivamente
	elemento->sacarElFrontCoding(palabra);

	Clave* clave = new Clave(elemento->getClave()->getClave());
	// Inserto recursivamente
	bool resultado = insertarRecursivo(raiz,*(clave) , elemento, &nuevaClaveRaiz, &nuevoNodoHijo);

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

		nuevaRaiz->claves[0] = nuevaClaveRaiz;
		nuevaRaiz->hijos[0] = raiz->numero;
		nuevaRaiz->hijos[1] = nuevoNodoHijo->numero;
		nuevaRaiz->cantidadClaves = 1;
		nuevaRaiz->espacioOcupado += nuevaClaveRaiz.getTamanio() + TAM_CONTROL_REGISTRO;
		nuevaRaiz->numero = 0;
		persistirNodo(nuevaRaiz);

		// Libero memoria
		liberarMemoriaNodo(raiz);
		liberarMemoriaNodo(nuevoNodoHijo);

		// Asigno la nueva raiz
		raiz = nuevaRaiz;
	} else {
		persistirNodo(raiz);
	}
	return resultado;
}


bool ArbolBMas::insertarRecursivo(Nodo* nodoCorriente, Clave& clave, Elementos* dato, Clave* nuevaClaveRaiz, Nodo** nuevoNodo){
	if (!nodoCorriente->isNodoHoja()) {
		// Si no es nodo hoja, casteo a nodo interior
		NodoInterior *nodoInteriorCorriente = static_cast<NodoInterior*> (nodoCorriente);
		Clave nuevaClave;
		Nodo* nuevoNodoHijo = NULL;
		// Obtengo la posicion a insertar
		int posicion = obtenerPosicion(nodoInteriorCorriente, clave);
		Nodo* nodoHijo = hidratarNodo(nodoInteriorCorriente->hijos[posicion]);

		// Vuelvo a insertar recursivamente
		bool resultado = insertarRecursivo(nodoHijo, clave, dato, &nuevaClave, &nuevoNodoHijo);

		if (nuevoNodoHijo) {

			if (nodoInteriorCorriente->isOverflow(nuevaClave.getTamanio() + TAM_CONTROL_REGISTRO + TAM_CONTROL_NODO)) {

				// Si hay overflow, tengo que hacer split del nodo interior
				dividirNodoInterior(nodoInteriorCorriente, nuevaClaveRaiz, nuevoNodo, posicion);

				if (posicion == nodoInteriorCorriente->cantidadClaves + 1
						&& nodoInteriorCorriente->cantidadClaves < (*nuevoNodo)->cantidadClaves) {

					NodoInterior *nuevoNodoInterior = static_cast<NodoInterior*> (*nuevoNodo);
					nodoInteriorCorriente->claves[nodoInteriorCorriente->cantidadClaves] = *nuevaClaveRaiz;
					nodoInteriorCorriente->hijos[nodoInteriorCorriente->cantidadClaves + 1] = nuevoNodoInterior->hijos[0];
					nodoInteriorCorriente->cantidadClaves++;
					nodoInteriorCorriente->espacioOcupado += (*nuevaClaveRaiz).getTamanio() + TAM_CONTROL_REGISTRO;
					nuevoNodoInterior->hijos[0] = nuevoNodoHijo->numero;
					*nuevaClaveRaiz = nuevaClave;
					// Persisto el nodo y libero memoria
					persistirNodo(nuevoNodoHijo);
					liberarMemoriaNodo(nuevoNodoHijo);
					// Persisto el nodo y libero memoria
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
			// Persisto el nodo y libero memoria
			persistirNodo(nuevoNodoHijo);
			liberarMemoriaNodo(nuevoNodoHijo);
		}

		// Persisto el nodo y libero memoria
		persistirNodo(nodoHijo);
		liberarMemoriaNodo(nodoHijo);
		return resultado;

	} else {
		NodoHoja *nodoHojaCorriente = static_cast<NodoHoja*> (nodoCorriente);

		// Saco el frontcoding antes de calcular la posicion
		sacarFrontCodingNodoHoja(&nodoHojaCorriente);
		int posicion = obtenerPosicion(nodoHojaCorriente, clave);


		int i = nodoHojaCorriente->cantidadClaves-1;
		while (i >= 0 && clave.getClave() < nodoHojaCorriente->claves[i].getClave()){
			nodoHojaCorriente->claves[i + 1] = nodoHojaCorriente->claves[i];
			nodoHojaCorriente->datos[i + 1] = nodoHojaCorriente->datos[i];
			i--;
		}

		nodoHojaCorriente->datos[i + 1] = *dato;
		nodoHojaCorriente->claves[i + 1] = clave;
		nodoHojaCorriente->cantidadClaves++;

		if (nodoHojaCorriente->cantidadClaves > 1){
			refactorizarNodoFrontCoding(&nodoHojaCorriente);
		}
		nodoHojaCorriente->espacioOcupado += nodoHojaCorriente->datos[i + 1].getTamanio() + clave.getTamanio() + TAM_CONTROL_REGISTRO;

		if (nodoHojaCorriente->isOverflow(TAM_CONTROL_NODO)) {

			dividirNodoHoja(nodoHojaCorriente, nuevaClaveRaiz, nuevoNodo);
			refactorizarNodoFrontCoding(&nodoHojaCorriente);
			refactorizarNodoNoHojaFrontCoding(&(*nuevoNodo));
			if (posicion >= nodoHojaCorriente->cantidadClaves) {
				posicion -= nodoHojaCorriente->cantidadClaves;
				nodoHojaCorriente = static_cast<NodoHoja*> (*nuevoNodo);
			}
		}
		else{
			if (nodoHojaCorriente->nivel == 0){
				refactorizarNodoFrontCoding(&nodoHojaCorriente);
			}
		}
		if (nuevoNodo && nodoHojaCorriente != *nuevoNodo && posicion == nodoHojaCorriente->cantidadClaves - 1) {
			*nuevaClaveRaiz = clave;
		}

		return true;
	}
}

void ArbolBMas::refactorizarNodoFrontCoding(NodoHoja** nodo){
	// Resto el tamaño del 1er dato
    (*nodo)->espacioOcupado -= ((*nodo))->datos[0].getTamanio();
    // Le saco el frontcoding a esa clave
    (*nodo)->datos[0].sacarElFrontCoding(((*nodo))->datos[0].getClave()->getClave());
    // Le sumo al nodo el tamaño del dato con la clave nueva
    (*nodo)->espacioOcupado += (*nodo)->datos[0].getTamanio();
	string primera = (*nodo)->datos[0].getClave()->getClave();

	// Hago lo mismo con el resto de las claves, pasandolas a frontcoding con respecto a la primera
	for (int i = 1; i < (*nodo)->cantidadClaves ; i++){
		(*nodo)->espacioOcupado -= ((*nodo))->datos[i].getTamanio();
		(*nodo)->datos[i].transformarAFrontCoding(primera);
		(*nodo)->espacioOcupado += ((*nodo))->datos[i].getTamanio();
	}
}

void ArbolBMas::refactorizarNodoNoHojaFrontCoding(Nodo** nodo){
	// Resto el tamaño del 1er dato
	static_cast<NodoHoja*>(*nodo)->espacioOcupado -= (static_cast<NodoHoja*>(*nodo))->datos[0].getTamanio();
	// Le saco el frontcoding a esa clave
	static_cast<NodoHoja*>(*nodo)->datos[0].sacarElFrontCoding((static_cast<NodoHoja*>(*nodo))->datos[0].getClave()->getClave());
	// Le sumo al nodo el tamaño del dato con la clave nueva
	static_cast<NodoHoja*>(*nodo)->espacioOcupado += static_cast<NodoHoja*>(*nodo)->datos[0].getTamanio();
	string primera = static_cast<NodoHoja*>(*nodo)->datos[0].getClave()->getClave();

	// Hago lo mismo con el resto de las claves, pasandolas a frontcoding con respecto a la primera
	for (int i = 1; i < static_cast<NodoHoja*>(*nodo)->cantidadClaves ; i++){
		static_cast<NodoHoja*>(*nodo)->espacioOcupado -= (static_cast<NodoHoja*>(*nodo))->datos[i].getTamanio();
		static_cast<NodoHoja*>(*nodo)->datos[i].transformarAFrontCoding(primera);
		static_cast<NodoHoja*>(*nodo)->espacioOcupado += (static_cast<NodoHoja*>(*nodo))->datos[i].getTamanio();
	}
}

int ArbolBMas::obtenerNumeroNodo(){
	int numeroDeNodo;

	// Si no hay nodos libres en la lista nodosLibres, devuelvo el siguiente de los que estan siendo usados
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

Nodo* ArbolBMas::hidratarNodo(int nroNodo){
	Nodo * nodo = recuperador_Nodos->obtenerNodo(nroNodo);
	return nodo;
}

void ArbolBMas::liberarMemoriaNodo(Nodo* nodo){
	if (nodo->isNodoHoja()) {
		delete static_cast<NodoHoja*> (nodo);
	} else {
		delete static_cast<NodoInterior*> (nodo);
	}
}

int ArbolBMas::obtenerPosicion(Nodo *nodo, Clave clave) {

	if (nodo->cantidadClaves == 0)
		return 0;
	int inferior = 0;
	int superior = (nodo->cantidadClaves) - 1;

	while (inferior < superior) {
		int medio = (inferior + superior) / 2;
		if (clave.getClave() <= nodo->claves[medio].getClave()) {
			superior = medio - 1;
		} else {
			inferior = medio + 1;
		}
	}
	if (superior < 0 || (nodo->claves[superior].getClave() < clave.getClave()))
		superior++;

	return superior;
}

void ArbolBMas::dividirNodoInterior(NodoInterior* nodoInteriorActual, Clave* nuevaClaveRaiz, Nodo** nuevoNodoInterior, int nuevaPosicion){

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
	*nuevaClaveRaiz = nodoInteriorActual->claves[medio];
	*nuevoNodoInterior = auxNuevoNodoInterior;
}

void ArbolBMas::sacarFrontCodingNodo (Nodo ** nodo){
	// Resto el tamaño original en el nodo
	static_cast<NodoHoja*>(*nodo)->espacioOcupado -= (static_cast<NodoHoja*>(*nodo))->datos[0].getTamanio();
	// Le saco el frontcoding
	static_cast<NodoHoja*>(*nodo)->datos[0].sacarElFrontCoding((static_cast<NodoHoja*>(*nodo))->datos[0].getClave()->getClave());
	// Sumo el nuevo tamaño sin el frontcoding en el nodo
	static_cast<NodoHoja*>(*nodo)->espacioOcupado += static_cast<NodoHoja*>(*nodo)->datos[0].getTamanio();

	// Hago lo mismo con el resto de las claves
	for (int i = 1; i < static_cast<NodoHoja*>(*nodo)->cantidadClaves ; i++){
		static_cast<NodoHoja*>(*nodo)->espacioOcupado -= (static_cast<NodoHoja*>(*nodo))->datos[i].getTamanio();
		static_cast<NodoHoja*>(*nodo)->datos[i].sacarElFrontCoding(static_cast<NodoHoja*>(*nodo)->datos[i].getClave()->getClave());
		static_cast<NodoHoja*>(*nodo)->espacioOcupado += (static_cast<NodoHoja*>(*nodo))->datos[i].getTamanio();
	}
}

void ArbolBMas::sacarFrontCodingNodoHoja (NodoHoja ** nodo){
	// Resto el tamaño original en el nodo
    (*nodo)->espacioOcupado -= ((*nodo))->datos[0].getTamanio();
    // Le saco el frontcoding
    (*nodo)->datos[0].sacarElFrontCoding(((*nodo))->datos[0].getClave()->getClave());
    // Sumo el nuevo tamaño sin el frontcoding en el nodo
    (*nodo)->espacioOcupado += (*nodo)->datos[0].getTamanio();

    // Hago lo mismo con el resto de las claves
	for (int i = 1; i < (*nodo)->cantidadClaves ; i++){
		(*nodo)->espacioOcupado -= ((*nodo))->datos[i].getTamanio();
		(*nodo)->datos[i].sacarElFrontCoding((*nodo)->datos[i].getClave()->getClave());
		(*nodo)->espacioOcupado += ((*nodo))->datos[i].getTamanio();
	}
}
void ArbolBMas::dividirNodoHoja(NodoHoja* unNodoHoja, Clave* clavePromocion, Nodo** nuevoNodoHoja){
	sacarFrontCodingNodoHoja(&unNodoHoja);
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
	ofstream fo;
	fo.open(PATH_ARBOL, ios_base::app);
	fo << "---------------------------------" << endl << endl;
	if (this->tipo == 1){
		fo << "-      ARBOL B+ DE AUTORES      -" << endl << endl;
		fo << "Tamanio de Nodo:  " << TAM_TOTAL_NODO << "Bytes" << endl;
		fo << "Primer Hoja, Nodo N°:  " << primeraHoja << endl;
	}
	if (nodo){
		toString(nodo,1, fo);
	}
	fo.flush();
	fo.close();
}
void ArbolBMas::MostrarArbol (){
	ofstream fo;
	fo.open(PATH_ARBOL, ios_base::out);
	fo << "*********************************************************************" << endl << endl;
	if (this->tipo == 1){
	fo << "*                       ARBOL B+ DE AUTORES                         *" << endl << endl;
	fo << "*********************************************************************" << endl << endl;
	fo << "Tamanio de Nodo:  " << TAM_TOTAL_NODO << endl;
		fo << "Primer Hoja:  " << primeraHoja << endl;
	}
	fo << "---------------------------------------------------------------------" << endl << endl;
	if (this->raiz){
		toString(this->raiz,1, fo);
	}
	fo.flush();
	fo.close();
}

void ArbolBMas::toString(Nodo* nodoAmostrar, int tab, ofstream& fo){

	if(nodoAmostrar){
		if (nodoAmostrar->isNodoHoja()) {
			NodoHoja *nodo = static_cast<NodoHoja*> (nodoAmostrar);
			for(int i=0 ; i<tab ; i++) fo << "  ";
				fo   << "Numero: " << nodo->numero <<  "  Nivel: " << nodo->nivel << "  Cant.Elem: " << nodo->cantidadClaves
				<< " Esp.Libre: " << TAM_EFECTIVO_NODO - nodo->espacioOcupado << "  Hoja.Sig: " << nodo->hojaSiguiente << "    " << endl;

			for(int i=0 ; i<tab ; i++) fo << "  ";
			for (int posicion = 0; posicion < nodo->cantidadClaves; ++posicion){
				fo << "(";
				Clave clave = (*nodo->datos[posicion].getClave());
				fo << clave.getClave();
				fo << ")";
			}
			fo << endl;
		} else {
			NodoInterior *nodoInt= static_cast<NodoInterior*> (nodoAmostrar);
			fo << endl;
			for(int i=0; i<tab ; i++)
				fo << "  ";
			fo << "Numero: " << nodoInt->numero << "  Nivel: " << nodoInt->nivel << "  Cant.Elem: " << nodoInt->cantidadClaves
					<< "  Esp.Libre: " << TAM_EFECTIVO_NODO - nodoInt->espacioOcupado << "  Claves: (";
			for (int posicion = 0; posicion <= nodoInt->cantidadClaves; ++posicion) {
				if (posicion < nodoInt->cantidadClaves) {
					Clave clave = nodoInt->claves[posicion];
					fo << clave.getClave();
					if (posicion == nodoInt->cantidadClaves-1){
						fo << ")" << endl;
					}else{
						fo << "," ;
					}
				}
			}
			int * hijos;
			Nodo *hijo;
			for (int posicion = 0; posicion <= nodoInt->cantidadClaves; ++posicion) {

				hijos = nodoInt->getHijos();
				hijo = hidratarNodo(hijos[posicion]);
				toString(hijo, tab+2, fo);
				if (hijo)
					liberarMemoriaNodo(hijo);
			}
			fo << endl;
		}
	}
}

void ArbolBMas::hidratarDatosConfiguracion(){
	nodosLibres.clear();
	recuperador_Datos_Configuracion->obtenerDatos(primeraHoja,nodosLibres);
}


bool ArbolBMas::borrar(Clave clave){
	if (!raiz)
		return false;
	int resultado = ArbolBMas::borrarRecursivo(clave, raiz, NULL, NULL, NULL, NULL, NULL, 0);
	return resultado != NO_ENCONTRADO;
	//return !resultado.contiene(Resultado::NO_ENCONTRADO);
}

int ArbolBMas::borrarRecursivo(Clave clave, Nodo *nodoCorriente, Nodo *nodoIzquierda, Nodo *nodoDerecha,
		NodoInterior *nodoPadreIzquierda, NodoInterior *nodoPadreDerecha, NodoInterior *nodoPadre, int posicionPadre) {
	if (nodoCorriente->isNodoHoja()) {
		sacarFrontCodingNodo(&nodoCorriente);
		NodoHoja *nodoHojaCorriente = static_cast<NodoHoja*> (nodoCorriente);
		NodoHoja *nodoHojaIzquierda = static_cast<NodoHoja*> (nodoIzquierda);
		NodoHoja *nodoHojaDerecha = static_cast<NodoHoja*> (nodoDerecha);
		int posicion = obtenerPosicion(nodoHojaCorriente, clave);
		if (posicion >= nodoHojaCorriente->cantidadClaves || clave.getClave() != nodoHojaCorriente->claves[posicion].getClave()) {
			return NO_ENCONTRADO;
		}

		nodoHojaCorriente->espacioOcupado -= (nodoHojaCorriente->datos[posicion].getTamanio() + nodoHojaCorriente->claves[posicion].getTamanio() + TAM_CONTROL_REGISTRO);
		nodoHojaCorriente->cantidadClaves--;
		for (int i = posicion; i < nodoHojaCorriente->cantidadClaves; i++) {
			nodoHojaCorriente->claves[i] = nodoHojaCorriente->claves[i + 1];
			nodoHojaCorriente->datos[i] = nodoHojaCorriente->datos[i + 1];
		}

		int resultado = RESULTADO_OK;

		// si se borro el elemento de la ultima posicion y no es la raiz
		if (posicion == nodoHojaCorriente->cantidadClaves && nodoPadre) {
			if (posicionPadre < nodoPadre->cantidadClaves) {
				if (nodoHojaCorriente->cantidadClaves >= 1) {
					nodoPadre->espacioOcupado -= nodoPadre->claves[posicionPadre].getTamanio();
					nodoPadre->espacioOcupado += nodoHojaCorriente->claves[nodoHojaCorriente->cantidadClaves - 1].getTamanio();
					nodoPadre->claves[posicionPadre] = nodoHojaCorriente->claves[nodoHojaCorriente->cantidadClaves - 1];
				}
			} else {
				if (nodoHojaCorriente->cantidadClaves >= 1) {
					resultado = ACTUALIZAR_ULTIMA_CLAVE;
					ultimaClave = nodoHojaCorriente->claves[nodoHojaCorriente->cantidadClaves - 1];
				} else {
					resultado = ACTUALIZAR_ULTIMA_CLAVE;
					ultimaClave = nodoHojaIzquierda->claves[nodoHojaIzquierda->cantidadClaves - 1];
				}
			}
		}
		refactorizarNodoFrontCoding(&nodoHojaCorriente);
		if (nodoHojaCorriente->isUnderflow() && !(nodoHojaCorriente == raiz && nodoHojaCorriente->cantidadClaves >= 1)) {
			sacarFrontCodingNodoHoja(&nodoHojaCorriente);
			if (nodoHojaIzquierda == NULL && nodoHojaDerecha == NULL) {
				if (raiz)
					liberarMemoriaNodo(raiz);
				raiz = nodoHojaCorriente = NULL;
				primeraHoja = 0;
				string archivoConfiguracion = PATH_CONFIGURACION_AUTORES;
				remove(archivoConfiguracion.c_str());
				return RESULTADO_OK;

			} else if (((nodoHojaIzquierda == NULL || !nodoHojaIzquierda->puedeCederElementos())
					&& (nodoHojaDerecha == NULL || !nodoHojaDerecha->puedeCederElementos()))
					|| nodoHojaCorriente->cantidadClaves == 0) {

				if (nodoPadreIzquierda == nodoPadre) {
					resultado = fusionarHojas(nodoHojaIzquierda, nodoHojaCorriente);
				} else {
					resultado = fusionarHojas(nodoHojaCorriente, nodoHojaDerecha);
				}

			} else if ((nodoHojaIzquierda != NULL && !nodoHojaIzquierda->puedeCederElementos())
					&& (nodoHojaDerecha != NULL && nodoHojaDerecha->puedeCederElementos())) {

				if (nodoPadreDerecha == nodoPadre) {
					resultado = pasarElementosHojaIzquierda(nodoHojaCorriente, nodoHojaDerecha, nodoPadreDerecha, posicionPadre);
				} else {
					resultado = fusionarHojas(nodoHojaIzquierda, nodoHojaCorriente);
				}

			} else if ((nodoHojaIzquierda != NULL && nodoHojaIzquierda->puedeCederElementos())
					&& (nodoHojaDerecha != NULL && !nodoHojaDerecha->puedeCederElementos())) {

				if (nodoPadreIzquierda == nodoPadre) {
					pasarElementosHojaDerecha(nodoHojaIzquierda, nodoHojaCorriente, nodoPadreIzquierda, posicionPadre - 1);
				} else {
					resultado = fusionarHojas(nodoHojaCorriente, nodoHojaDerecha);
				}

			} else if (nodoPadreIzquierda == nodoPadreDerecha) {
				if (nodoHojaIzquierda->espacioOcupado <= nodoHojaDerecha->espacioOcupado) {
					resultado = pasarElementosHojaIzquierda(nodoHojaCorriente, nodoHojaDerecha, nodoPadreDerecha, posicionPadre);
				} else {
					pasarElementosHojaDerecha(nodoHojaIzquierda, nodoHojaCorriente, nodoPadreIzquierda, posicionPadre - 1);
				}

			} else {
				if (nodoPadreIzquierda == nodoPadre) {
					pasarElementosHojaDerecha(nodoHojaIzquierda, nodoHojaCorriente, nodoPadreIzquierda, posicionPadre	- 1);
				} else {
					resultado = pasarElementosHojaIzquierda(nodoHojaCorriente, nodoHojaDerecha, nodoPadreDerecha, posicionPadre);
				}
			}
		} else {
			refactorizarNodoFrontCoding(&nodoHojaCorriente);
			persistirNodo(nodoHojaCorriente);
		}
		return resultado;

	} else {

		NodoInterior *nodoInteriorCorriente = static_cast<NodoInterior*> (nodoCorriente);
		NodoInterior *nodoInteriorIzquierda = static_cast<NodoInterior*> (nodoIzquierda);
		NodoInterior *nodoInteriorDerecha = static_cast<NodoInterior*> (nodoDerecha);
		Nodo *auxNodoIzquierda, *auxNodoDerecha;
		NodoInterior *auxPadreIzquierda, *auxPadreDerecha;

		int posicion = obtenerPosicion(nodoInteriorCorriente, clave);
		if (posicion == 0) {
			auxNodoIzquierda = (nodoIzquierda == NULL) ? NULL : hidratarNodo((static_cast<NodoInterior*> (nodoIzquierda))->hijos[nodoIzquierda->cantidadClaves]);
			auxPadreIzquierda = nodoPadreIzquierda;
		} else {
			auxNodoIzquierda = hidratarNodo(nodoInteriorCorriente->hijos[posicion - 1]);
			auxPadreIzquierda = nodoInteriorCorriente;
		}

		if (posicion == nodoInteriorCorriente->cantidadClaves) {
			auxNodoDerecha = (nodoDerecha == NULL) ? NULL : hidratarNodo((static_cast<NodoInterior*> (nodoDerecha))->hijos[0]);
			auxPadreDerecha = nodoPadreDerecha;
		} else {
			auxNodoDerecha = hidratarNodo(nodoInteriorCorriente->hijos[posicion + 1]);
			auxPadreDerecha = nodoInteriorCorriente;
		}
		Nodo* auxNodoCorriente = hidratarNodo(nodoInteriorCorriente->hijos[posicion]);
		int resultadoParcial = borrarRecursivo(clave, auxNodoCorriente, auxNodoIzquierda, auxNodoDerecha, auxPadreIzquierda, auxPadreDerecha, nodoInteriorCorriente, posicion);
		int resultado = RESULTADO_OK;

		if (auxNodoIzquierda)
			liberarMemoriaNodo(auxNodoIzquierda);
		if (auxNodoDerecha)
			liberarMemoriaNodo(auxNodoDerecha);
		if (auxNodoCorriente)
			liberarMemoriaNodo(auxNodoCorriente);

		if (resultadoParcial == NO_ENCONTRADO) {
			return resultadoParcial;
		}

		if ( resultadoParcial == ACTUALIZAR_ULTIMA_CLAVE ) {
			if (nodoPadre && posicionPadre < nodoPadre->cantidadClaves) {
				nodoPadre->espacioOcupado -= nodoPadre->claves[posicionPadre].getTamanio();
				nodoPadre->espacioOcupado += ultimaClave.getTamanio();
				nodoPadre->claves[posicionPadre] = ultimaClave;
			}
		}

		if (resultadoParcial == FUSION) {
			Nodo* nodoHijo = hidratarNodo(nodoInteriorCorriente->hijos[posicion]);
			if (nodoHijo->cantidadClaves != 0)
				posicion++;

			Clave claveInteriorBorrada = nodoInteriorCorriente->claves[posicion - 1];
			for (int i = posicion; i < nodoInteriorCorriente->cantidadClaves; i++) {
				nodoInteriorCorriente->claves[i - 1] = nodoInteriorCorriente->claves[i];
				nodoInteriorCorriente->hijos[i] = nodoInteriorCorriente->hijos[i + 1];
			}
			nodoInteriorCorriente->cantidadClaves--;
			nodoInteriorCorriente->espacioOcupado -= (claveInteriorBorrada.getTamanio() + TAM_CONTROL_REGISTRO);
			nodoInteriorCorriente->espacioOcupado -= nodoInteriorCorriente->claves[nodoInteriorCorriente->cantidadClaves].getTamanio();

			if (nodoHijo)
				liberarMemoriaNodo(nodoHijo);
			if (nodoInteriorCorriente->nivel == 1) {
				posicion--;
				nodoHijo = hidratarNodo(nodoInteriorCorriente->hijos[posicion]);
				nodoInteriorCorriente->espacioOcupado -= nodoInteriorCorriente->claves[posicion].getTamanio();
				nodoInteriorCorriente->espacioOcupado += nodoHijo->claves[nodoHijo->cantidadClaves - 1].getTamanio();
				nodoInteriorCorriente->claves[posicion] = nodoHijo->claves[nodoHijo->cantidadClaves - 1];
				if (nodoHijo)
					liberarMemoriaNodo(nodoHijo);
			}
		}

		if (resultadoParcial == FUSION
				&& nodoInteriorCorriente->isUnderflow()
				&& !(nodoInteriorCorriente == raiz && nodoInteriorCorriente->cantidadClaves >= 1)) {

			if (nodoInteriorIzquierda == NULL && nodoInteriorDerecha == NULL) {
				raiz = hidratarNodo(nodoInteriorCorriente->hijos[0]);
				raiz->numero = 0;
				persistirNodo(raiz);
				nodosLibres.push_back(nodoInteriorCorriente->hijos[0]);
				grabarDatosConfiguracion();
				return RESULTADO_OK;

			} else if ((nodoInteriorIzquierda == NULL || !nodoInteriorIzquierda->puedeCederElementos())
					&& (nodoInteriorDerecha == NULL || !nodoInteriorDerecha->puedeCederElementos())) {

				if (nodoPadreIzquierda == nodoPadre) {
					resultado = fusionarNodosInteriores(nodoInteriorIzquierda, nodoInteriorCorriente, nodoPadreIzquierda, posicionPadre - 1);
				} else {
					resultado = fusionarNodosInteriores(nodoInteriorCorriente, nodoInteriorDerecha, nodoPadreDerecha, posicionPadre);
				}

			} else if ((nodoInteriorIzquierda != NULL && !nodoInteriorIzquierda->puedeCederElementos())
					&& (nodoInteriorDerecha != NULL && nodoInteriorDerecha->puedeCederElementos())) {

				if (nodoPadreDerecha == nodoPadre) {
					pasarElementosNodoInteriorIzquierdo(nodoInteriorCorriente, nodoInteriorDerecha, nodoPadreDerecha, posicionPadre);
				} else {
					resultado = fusionarNodosInteriores(nodoInteriorIzquierda, nodoInteriorCorriente, nodoPadreIzquierda, posicionPadre - 1);
				}

			} else if ((nodoInteriorIzquierda != NULL && nodoInteriorIzquierda->puedeCederElementos())
					&& (nodoInteriorDerecha != NULL && !nodoInteriorDerecha->puedeCederElementos())) {

				if (nodoPadreIzquierda == nodoPadre) {
					pasarElementosNodoInteriorDerecho(nodoInteriorIzquierda, nodoInteriorCorriente, nodoPadreIzquierda, posicionPadre - 1);
				} else {
					resultado = fusionarNodosInteriores(nodoInteriorCorriente, nodoInteriorDerecha, nodoPadreDerecha, posicionPadre);
				}

			} else if (nodoPadreIzquierda == nodoPadreDerecha) {

				if (nodoInteriorIzquierda->cantidadClaves <= nodoInteriorDerecha->cantidadClaves) {
					pasarElementosNodoInteriorIzquierdo(nodoInteriorCorriente, nodoInteriorDerecha, nodoPadreDerecha, posicionPadre);
				} else {
					pasarElementosNodoInteriorDerecho(nodoInteriorIzquierda, nodoInteriorCorriente, nodoPadreIzquierda, posicionPadre - 1);
				}

			} else {

				if (nodoPadreIzquierda == nodoPadre) {
					pasarElementosNodoInteriorDerecho(nodoInteriorIzquierda, nodoInteriorCorriente, nodoPadreIzquierda, posicionPadre - 1);
				} else {
					pasarElementosNodoInteriorIzquierdo(nodoInteriorCorriente, nodoInteriorDerecha, nodoPadreDerecha, posicionPadre);
				}
			}

		} else {
			persistirNodo(nodoInteriorCorriente);
		}

		return resultado;
	}
}


int ArbolBMas::fusionarHojas(NodoHoja* hojaIzquierda, NodoHoja* hojaDerecha) {
	sacarFrontCodingNodoHoja(&hojaIzquierda);
	sacarFrontCodingNodoHoja(&hojaDerecha);
	for (int i = 0; i < hojaDerecha->cantidadClaves; i++) {
		hojaIzquierda->claves[hojaIzquierda->cantidadClaves + i] = hojaDerecha->claves[i];
		hojaIzquierda->datos[hojaIzquierda->cantidadClaves + i] = hojaDerecha->datos[i];
	}
	hojaIzquierda->cantidadClaves += hojaDerecha->cantidadClaves;
	hojaIzquierda->espacioOcupado += hojaDerecha->espacioOcupado;
	hojaIzquierda->hojaSiguiente = hojaDerecha->hojaSiguiente;

	hojaDerecha->cantidadClaves = 0;
	hojaDerecha->espacioOcupado = 0;

	nodosLibres.push_back(hojaDerecha->numero);
	grabarDatosConfiguracion();

	refactorizarNodoFrontCoding(&hojaDerecha);
	refactorizarNodoFrontCoding(&hojaIzquierda);
	persistirNodo(hojaIzquierda);
	persistirNodo(hojaDerecha);

	return FUSION;
}


int ArbolBMas::fusionarNodosInteriores(NodoInterior* nodoIzquierda, NodoInterior* nodoDerecha, NodoInterior* nodoPadre, int posicionPadre) {

	int espacioOcupadoTotal = (nodoIzquierda->espacioOcupado + nodoDerecha->espacioOcupado + nodoPadre->claves[posicionPadre].getTamanio() + TAM_CONTROL_REGISTRO);

	enumReturn resultado;
	if (espacioOcupadoTotal > TAM_EFECTIVO_NODO) {
		resultado = RESULTADO_OK;
	} else {
		nodoIzquierda->claves[nodoIzquierda->cantidadClaves] = nodoPadre->claves[posicionPadre];
		nodoIzquierda->cantidadClaves++;
		nodoIzquierda->espacioOcupado += nodoPadre->claves[posicionPadre].getTamanio() + TAM_CONTROL_REGISTRO;
		for (int i = 0; i < nodoDerecha->cantidadClaves; i++) {
			nodoIzquierda->claves[nodoIzquierda->cantidadClaves + i] = nodoDerecha->claves[i];
			nodoIzquierda->hijos[nodoIzquierda->cantidadClaves + i] = nodoDerecha->hijos[i];
		}
		nodoIzquierda->cantidadClaves += nodoDerecha->cantidadClaves;
		nodoIzquierda->espacioOcupado += nodoDerecha->espacioOcupado;
		nodoIzquierda->hijos[nodoIzquierda->cantidadClaves] = nodoDerecha->hijos[nodoDerecha->cantidadClaves];
		nodoDerecha->cantidadClaves = 0;
		nodoDerecha->espacioOcupado = 0;

		nodosLibres.push_back(nodoDerecha->numero);
		grabarDatosConfiguracion();

		resultado = FUSION;
	}
	persistirNodo(nodoIzquierda);
	persistirNodo(nodoDerecha);

	return resultado;
}


int ArbolBMas::pasarElementosHojaIzquierda(NodoHoja *hojaIzquierda, NodoHoja *hojaDerecha, NodoInterior *nodoPadre, int posicionPadre) {

	int tamanioMedio = (hojaDerecha->espacioOcupado - hojaIzquierda->espacioOcupado) / 2;
	int espacioDesplazado = 0;
	int cantidadClavesDesplazadas = 0;
	while (cantidadClavesDesplazadas < hojaDerecha->cantidadClaves && espacioDesplazado < tamanioMedio){
		espacioDesplazado += hojaDerecha->datos[cantidadClavesDesplazadas].getTamanio()
						   + hojaDerecha->claves[cantidadClavesDesplazadas].getTamanio()
						   + TAM_CONTROL_REGISTRO;
		cantidadClavesDesplazadas++;
		if (espacioDesplazado + hojaIzquierda->espacioOcupado > TAM_EFECTIVO_NODO) {
			cantidadClavesDesplazadas--;
			espacioDesplazado -= (hojaDerecha->datos[cantidadClavesDesplazadas].getTamanio()
							   + hojaDerecha->claves[cantidadClavesDesplazadas].getTamanio()
							   + TAM_CONTROL_REGISTRO);
			break;
		}
	}

	if (cantidadClavesDesplazadas > 0) {
		for (int i = 0; i < cantidadClavesDesplazadas; i++) {
			hojaIzquierda->claves[hojaIzquierda->cantidadClaves + i] = hojaDerecha->claves[i];
			hojaIzquierda->datos[hojaIzquierda->cantidadClaves + i] = hojaDerecha->datos[i];
		}

		hojaIzquierda->cantidadClaves += cantidadClavesDesplazadas;
		hojaIzquierda->espacioOcupado += espacioDesplazado;
		hojaDerecha->cantidadClaves -= cantidadClavesDesplazadas;
		hojaDerecha->espacioOcupado -= espacioDesplazado;
		for (int i = 0; i < hojaDerecha->cantidadClaves; i++) {
			hojaDerecha->claves[i] = hojaDerecha->claves[i + cantidadClavesDesplazadas];
			hojaDerecha->datos[i] = hojaDerecha->datos[i + cantidadClavesDesplazadas];
		}
	}
	refactorizarNodoFrontCoding(&hojaDerecha);
	refactorizarNodoFrontCoding(&hojaIzquierda);
	persistirNodo(hojaIzquierda);
	persistirNodo(hojaDerecha);

	if (cantidadClavesDesplazadas > 0) {
		if (posicionPadre < nodoPadre->cantidadClaves) {
			nodoPadre->espacioOcupado -= nodoPadre->claves[posicionPadre].getTamanio();
			nodoPadre->espacioOcupado += hojaIzquierda->claves[hojaIzquierda->cantidadClaves - 1].getTamanio();
			nodoPadre->claves[posicionPadre] = hojaIzquierda->claves[hojaIzquierda->cantidadClaves - 1];
			return RESULTADO_OK;
		} else {
			ultimaClave = hojaIzquierda->claves[hojaIzquierda->cantidadClaves - 1];
			return ACTUALIZAR_ULTIMA_CLAVE;
		}
	} else {
		return RESULTADO_OK;
	}
}


void ArbolBMas::pasarElementosNodoInteriorIzquierdo(NodoInterior *nodoIzquierda, NodoInterior *nodoDerecha,	NodoInterior *nodoPadre, int posicionPadre) {

	int tamanioMedio = (nodoDerecha->espacioOcupado - nodoIzquierda->espacioOcupado) / 2;
	int espacioDesplazado = 0;
	int cantidadClavesDesplazadas = 0;
	while (cantidadClavesDesplazadas < nodoDerecha->cantidadClaves && espacioDesplazado < tamanioMedio){
		espacioDesplazado += nodoDerecha->claves[cantidadClavesDesplazadas].getTamanio()
						   + TAM_CONTROL_REGISTRO;
		cantidadClavesDesplazadas++;
		if (espacioDesplazado + nodoIzquierda->espacioOcupado > TAM_EFECTIVO_NODO) {
			cantidadClavesDesplazadas--;
			espacioDesplazado -= (nodoDerecha->claves[cantidadClavesDesplazadas].getTamanio()
							   + TAM_CONTROL_REGISTRO);
			break;
		}
	}

	if (cantidadClavesDesplazadas > 0) {
		espacioDesplazado = 0;

		nodoIzquierda->claves[nodoIzquierda->cantidadClaves] = nodoPadre->claves[posicionPadre];
		nodoIzquierda->cantidadClaves++;
		nodoIzquierda->espacioOcupado += nodoPadre->claves[posicionPadre].getTamanio() + TAM_CONTROL_REGISTRO;

		for (int i = 0; i < cantidadClavesDesplazadas - 1; i++) {
			nodoIzquierda->claves[nodoIzquierda->cantidadClaves + i] = nodoDerecha->claves[i];
			nodoIzquierda->hijos[nodoIzquierda->cantidadClaves + i] = nodoDerecha->hijos[i];
			espacioDesplazado += nodoDerecha->claves[i].getTamanio() + TAM_CONTROL_REGISTRO;
		}

		nodoIzquierda->cantidadClaves += cantidadClavesDesplazadas - 1;
		nodoIzquierda->espacioOcupado += espacioDesplazado;
		nodoIzquierda->hijos[nodoIzquierda->cantidadClaves] = nodoDerecha->hijos[cantidadClavesDesplazadas - 1];
		nodoPadre->espacioOcupado -= nodoPadre->claves[posicionPadre].getTamanio();
		nodoPadre->espacioOcupado += nodoDerecha->claves[cantidadClavesDesplazadas - 1].getTamanio();
		nodoPadre->claves[posicionPadre] = nodoDerecha->claves[cantidadClavesDesplazadas - 1];
		nodoDerecha->cantidadClaves -= cantidadClavesDesplazadas;
		nodoDerecha->espacioOcupado -= espacioDesplazado;
		nodoDerecha->espacioOcupado -= nodoDerecha->claves[cantidadClavesDesplazadas - 1].getTamanio();

		for (int i = 0; i < nodoDerecha->cantidadClaves; i++) {
			nodoDerecha->claves[i] = nodoDerecha->claves[i + cantidadClavesDesplazadas];
			nodoDerecha->hijos[i] = nodoDerecha->hijos[i + cantidadClavesDesplazadas];
		}
		nodoDerecha->hijos[nodoDerecha->cantidadClaves] = nodoDerecha->hijos[nodoDerecha->cantidadClaves + cantidadClavesDesplazadas];
	}
	persistirNodo(nodoIzquierda);
	persistirNodo(nodoDerecha);
}


void ArbolBMas::pasarElementosHojaDerecha(NodoHoja *hojaIzquierda, NodoHoja *hojaDerecha, NodoInterior *nodoPadre, int posicionPadre) {

	int espacioOcupadoMedio = (hojaIzquierda->espacioOcupado - hojaDerecha->espacioOcupado) / 2;
	int espacioDesplazado = 0;
	int cantidadClavesDesplazadas = 0;
	for (int i = hojaIzquierda->cantidadClaves; i > 0 && espacioDesplazado < espacioOcupadoMedio; i--) {
		espacioDesplazado += hojaIzquierda->datos[i-1].getTamanio() + hojaIzquierda->claves[i-1].getTamanio() + TAM_CONTROL_REGISTRO;
		cantidadClavesDesplazadas++;
		if (espacioDesplazado + hojaDerecha->espacioOcupado > TAM_EFECTIVO_NODO) {
			espacioDesplazado -= (hojaIzquierda->datos[i-1].getTamanio() + hojaIzquierda->claves[i-1].getTamanio() + TAM_CONTROL_REGISTRO);
			cantidadClavesDesplazadas--;
			break;
		}
	}

	if (cantidadClavesDesplazadas > 0) {
		for (int i = hojaDerecha->cantidadClaves; i >= 0; i--) {
			hojaDerecha->claves[i + cantidadClavesDesplazadas] = hojaDerecha->claves[i];
			hojaDerecha->datos[i + cantidadClavesDesplazadas] = hojaDerecha->datos[i];
		}
		hojaDerecha->cantidadClaves += cantidadClavesDesplazadas;
		hojaDerecha->espacioOcupado += espacioDesplazado;

		for (int i = 0; i < cantidadClavesDesplazadas; i++) {
			hojaDerecha->claves[i] = hojaIzquierda->claves[hojaIzquierda->cantidadClaves - cantidadClavesDesplazadas + i];
			hojaDerecha->datos[i] = hojaIzquierda->datos[hojaIzquierda->cantidadClaves - cantidadClavesDesplazadas + i];
		}
		hojaIzquierda->cantidadClaves -= cantidadClavesDesplazadas;
		hojaIzquierda->espacioOcupado -= espacioDesplazado;
		nodoPadre->espacioOcupado -= nodoPadre->claves[posicionPadre].getTamanio();
		nodoPadre->espacioOcupado += hojaIzquierda->claves[hojaIzquierda->cantidadClaves - 1].getTamanio();
		nodoPadre->claves[posicionPadre] = hojaIzquierda->claves[hojaIzquierda->cantidadClaves - 1];
	}
	refactorizarNodoFrontCoding(&hojaDerecha);
	refactorizarNodoFrontCoding(&hojaIzquierda);
	persistirNodo(hojaIzquierda);
	persistirNodo(hojaDerecha);
}


void ArbolBMas::pasarElementosNodoInteriorDerecho(NodoInterior *nodoIzquierda, NodoInterior *nodoDerecha, NodoInterior *nodoPadre, int posicionPadre) {

	int espacioOcupadoMedio = (nodoIzquierda->espacioOcupado - nodoDerecha->espacioOcupado) / 2;
	int espacioDesplazado = 0;
	int cantidadClavesDesplazadas = 0;
	for (int i = nodoIzquierda->cantidadClaves; i > 0 && espacioDesplazado < espacioOcupadoMedio; i--) {
		espacioDesplazado += nodoIzquierda->claves[i-1].getTamanio() + TAM_CONTROL_REGISTRO;
		cantidadClavesDesplazadas++;
		if (espacioDesplazado + nodoDerecha->espacioOcupado > TAM_EFECTIVO_NODO) {
			espacioDesplazado -= (nodoIzquierda->claves[i-1].getTamanio() + TAM_CONTROL_REGISTRO);
			cantidadClavesDesplazadas--;
			break;
		}
	}

	if (cantidadClavesDesplazadas > 0) {
		espacioDesplazado = 0;

		nodoDerecha->hijos[nodoDerecha->cantidadClaves + cantidadClavesDesplazadas] = nodoDerecha->hijos[nodoDerecha->cantidadClaves];

		for (int i = nodoDerecha->cantidadClaves - 1; i >= 0; i--) {
			nodoDerecha->claves[i + cantidadClavesDesplazadas] = nodoDerecha->claves[i];
			nodoDerecha->hijos[i + cantidadClavesDesplazadas] = nodoDerecha->hijos[i];
		}

		nodoDerecha->cantidadClaves += cantidadClavesDesplazadas;
		nodoDerecha->claves[cantidadClavesDesplazadas - 1] = nodoPadre->claves[posicionPadre];
		nodoDerecha->hijos[cantidadClavesDesplazadas - 1] = nodoIzquierda->hijos[nodoIzquierda->cantidadClaves];
		nodoDerecha->espacioOcupado += nodoPadre->claves[posicionPadre].getTamanio()+ TAM_CONTROL_REGISTRO;

		for (int i = 0; i < cantidadClavesDesplazadas - 1; i++) {
			nodoDerecha->claves[i] = nodoIzquierda->claves[nodoIzquierda->cantidadClaves - cantidadClavesDesplazadas + i + 1];
			nodoDerecha->hijos[i] = nodoIzquierda->hijos[nodoIzquierda->cantidadClaves - cantidadClavesDesplazadas + i + 1];
			espacioDesplazado += nodoDerecha->claves[i].getTamanio() + TAM_CONTROL_REGISTRO;
		}
		nodoDerecha->espacioOcupado += espacioDesplazado;

		nodoPadre->espacioOcupado -= nodoPadre->claves[posicionPadre].getTamanio();
		nodoPadre->espacioOcupado += nodoIzquierda->claves[nodoIzquierda->cantidadClaves - cantidadClavesDesplazadas].getTamanio();
		nodoPadre->claves[posicionPadre] = nodoIzquierda->claves[nodoIzquierda->cantidadClaves - cantidadClavesDesplazadas];
		nodoIzquierda->cantidadClaves -= cantidadClavesDesplazadas;
		nodoIzquierda->espacioOcupado -= espacioDesplazado;
		nodoIzquierda->espacioOcupado -= (nodoIzquierda->claves[nodoIzquierda->cantidadClaves - cantidadClavesDesplazadas].getTamanio());
	}
	persistirNodo(nodoIzquierda);
	persistirNodo(nodoDerecha);
}
