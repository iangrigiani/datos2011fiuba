/*
 * ArbolB+.cpp
 *
 *  Created on: 26/03/2010
 *      Author: Grupo Klow
 */
#include <cmath>
#include <iostream>
#include "ArbolB.h"
#include "NodoInterno.h"
#include "NodoHoja.h"
#include "Nodo.h"
#include "../../ControladorIDsLibres/src/ControladorIDsLibres.c"


ArbolB::ArbolB(char * nombre, int tamanoBloque) {
	//El bloque minimo es de 32 bytes
	if (tamanoBloque < 32) {
		tamanoBloque = 32;
	} else {
		//Validacion de la longitud de tamaño de bloque ingresado.
		// Si no es correcta se pone la longitud correcta mas cercana.
		float aux = log2(tamanoBloque);
		if (aux - floor(aux)) {
			this->longitudBloque =  pow(2,ceil(aux));
		} else {
			this->longitudBloque = tamanoBloque;
		}
	}

	//inicializo el controlador de nodos libres
	int long_Nombre= strlen(nombre);
	char extension[] = "-NodosLibres";
	char * nombre_controlador = new char[long_Nombre + strlen(extension)+1];

	nombre_controlador[0] = '\0';
	strcat(nombre_controlador,nombre);
	strcat(nombre_controlador,extension);

	//Se divide por 2 la longitud del bloque ya que el buffer del controlador va a usar un bloque
	//del doble seleccionado
	ControladorIDsLibres_Iniciar(&this->controladorNodosLibres,nombre_controlador,this->longitudBloque/2);

	delete[](nombre_controlador);

	//Creo el bloque que voy a utilizar para leer y escribir en el archivo
	this->bloque = new char[this->longitudBloque];
	//TODO
	//memset(this->bloque,' ',this->longitudBloque);

	//Intento abrir el archivo. Si existe cargo la raiz. Sino la creo.
	if ( (this->handleFile  = fopen(nombre,"r+"))==NULL){
		//No se pudo abrir el archivo, se crea.
		this->handleFile  = fopen(nombre,"w+");
		//Creo la raiz
		this->raiz = new NodoHoja(this->longitudBloque,0);
		// La grabo
		this->grabarNodo(raiz,0);
		this->altura = 0;
		this->cantidad_elementos = 0;
		this->ultimo_nodo_creado = 0;
		this->cambios = true;

		this->iniciarRecorridoSecuencial();

	} else {
		// El archivo existe. Se lee la raiz.
		inicializarArbol();
		this->raiz = this->leerNodo(0);
		this->cambios= false;
	}

}

void ArbolB::inicializarArbol(){

	//creo el bloque para leer y ecsribir los atributos en el archivo
	char* bloque_atributos= (char*) malloc(BLOQUE_ATRIBUTOS_ARBOL);
	memset(bloque_atributos,0,BLOQUE_ATRIBUTOS_ARBOL);
	// Voy hacia la posicion
	fseek(this->handleFile,0,SEEK_SET);
	// Leo el bloque de atributos
	fread(bloque_atributos,BLOQUE_ATRIBUTOS_ARBOL,1,this->handleFile);

	unsigned int longitud;
	unsigned int actual=0;

	longitud = sizeof(Nodo::IDNodo);
	memcpy(&this->recorridoSecuencial.sigNodo,&bloque_atributos[actual],longitud);

	actual += longitud;
	memcpy(&this->recorridoSecuencial.antNodo,&bloque_atributos[actual],longitud);

	actual += longitud;
	longitud = sizeof(int);
	memcpy(&this->recorridoSecuencial.sigPos,&bloque_atributos[actual],longitud);

	actual += longitud;
	memcpy(&this->recorridoSecuencial.antPos,&bloque_atributos[actual],longitud);

	actual += longitud;
	longitud = sizeof(Nodo::IDNodo);
	memcpy(&this->ultimo_nodo_creado,&bloque_atributos[actual],longitud);

	actual += longitud;
	longitud = sizeof(unsigned short int);
	memcpy(&this->altura,&bloque_atributos[actual],longitud);

	actual += longitud;
	longitud = sizeof(unsigned int);
	memcpy(&this->cantidad_elementos,&bloque_atributos[actual],longitud);

	free(bloque_atributos);
}

/* GETTERS PUBLICOS */
unsigned int ArbolB::getCantidadElementos() {
	return this->cantidad_elementos;
}

unsigned int ArbolB::getAltura() {
	return this->altura;
}

/* GETTERS Y SETTERS PRIVADOS */
Nodo::IDNodo ArbolB::getIDNodoLibre() {

	if(ControladorIDsLibres_tieneIDLibre(&this->controladorNodosLibres))
		return ControladorIDsLibres_getIDLibre(&this->controladorNodosLibres);
	else{
		this->cambios = true;
		return ++this->ultimo_nodo_creado;
	}
}

void ArbolB::addIDNodoLibre(Nodo::IDNodo id) {
	ControladorIDsLibres_addIDLibre(&this->controladorNodosLibres, id);
}

void ArbolB::incrCantElem(){
	this->cantidad_elementos++;
	this->cambios = true;
}

void ArbolB::decrCantElem(){
	if(this->cantidad_elementos > 0){
		this->cantidad_elementos--;
		this->cambios = true;
	}
}

void ArbolB::incrAltura(){

	this->altura++;
	this->cambios = true;
}

void ArbolB::decrAltura(){

	if(this->altura > 0){
		this->altura--;
		this->cambios = true;
	}
}

void ArbolB::actualizarCambios(){

	if(this->cambios == true){

		//creo el bloque para leer y ecsribir los atributos en el archivo
		char* bloque_atributos= (char*) malloc(BLOQUE_ATRIBUTOS_ARBOL);

		//Completo con caracteres vacios para que no escriba basura
		memset(bloque_atributos,0,BLOQUE_ATRIBUTOS_ARBOL);

		unsigned int longitud = 0;
		unsigned int actual = 0;

		//copio el atributo de recorrido secuencial
		//copio los atributos de recorrido secuencial
		longitud = sizeof(Nodo::IDNodo);
		memcpy(&bloque_atributos[actual],&this->recorridoSecuencial.sigNodo,longitud);
		actual += longitud;
		longitud = sizeof(Nodo::IDNodo);
		memcpy(&bloque_atributos[actual],&this->recorridoSecuencial.antNodo,longitud);
		actual += longitud;
		longitud = sizeof(int);
		memcpy(&bloque_atributos[actual],&this->recorridoSecuencial.sigPos,longitud);
		actual += longitud;
		longitud = sizeof(int);
		memcpy(&bloque_atributos[actual],&this->recorridoSecuencial.antPos,longitud);

		actual += longitud;
		longitud = sizeof(Nodo::IDNodo);
		//copio el atributo del ultimo nodo creado en el bloque de atrib
		memcpy(&bloque_atributos[actual],&this->ultimo_nodo_creado,longitud);
		actual += longitud;
		longitud = sizeof(unsigned short int);
		//copio el atributo de la altura del arbol en el bloque de atrib
		memcpy(&bloque_atributos[actual],&this->altura,longitud);
		actual += longitud;
		longitud = sizeof(unsigned int);
		//copio el atributo de cantidad de elementos  en el bloque de atrib
		memcpy(&bloque_atributos[actual],&this->cantidad_elementos,longitud);
		// Me posiciono en el archivo
		fseek(this->handleFile,0,SEEK_SET);
		// Escribo
		fwrite(bloque_atributos,BLOQUE_ATRIBUTOS_ARBOL,1,this->handleFile);
		fflush(this->handleFile);
		//seteo la variable de cambios en false
		this->cambios = false;

		free(bloque_atributos);
	}
}

Nodo * ArbolB::leerNodo(Nodo::IDNodo numeroNodo) {
	unsigned int offset;
	Nodo * n;

	// Obtengo la posicion donde se encuentra el bloque necesitado
	offset  = numeroNodo * this->longitudBloque + BLOQUE_ATRIBUTOS_ARBOL;
	// Voy hacia la posicion
	fseek(this->handleFile,offset,SEEK_SET);
	// Leo el bloque
	fread(bloque,this->longitudBloque,1,this->handleFile);
	// Que tipo de bloque lei?
	if (bloque[0]==Nodo::NODO_INTERNO) {
		n = new NodoInterno(this->longitudBloque,bloque,numeroNodo);
	} else {
		n =  new NodoHoja(this->longitudBloque,bloque,numeroNodo);
	}
	return n;
}

void ArbolB::grabarNodo(Nodo * nodo, unsigned int pos) {
	unsigned int offset;
	// Obtengo la posicion donde debo escribir
	offset = pos * this->longitudBloque + BLOQUE_ATRIBUTOS_ARBOL;

	memset(this->bloque,0,this->longitudBloque);
	//Obtengo el nodo convertido en un array de bytes.
	nodo->Guardar(this->bloque);
	// Me posiciono en el archivo
	fseek(this->handleFile,offset,SEEK_SET);
	// Escribo
	fwrite(bloque,this->longitudBloque,1,this->handleFile);
	fflush(this->handleFile);
}

/* Funcion publica insertar. Inserta un elemento e en el arbol. */
ArbolB::Resultado ArbolB::Insertar(Nodo::TClave clave, void * elemento, unsigned short int longitudElemento) {
	Nodo::Estado estado;
	Nodo::TRetorno retorno;
	// Este insertar maneja la raiz que tiene un trato especial. La raiz siempre esta en la
	// posicion 0 del archivo.
	//La raiz queda cargada en memoria.

	this->Insertar(raiz,clave,elemento,longitudElemento,&retorno,&estado);
	if (estado == Nodo::MODIFICADO) {
		this->grabarNodo(raiz,0);
	} else if (estado== Nodo::OVERFLOW_HOJA || estado == Nodo::OVERFLOW_INTERNO) {
		this->resolver_overflow_raiz(clave,elemento,longitudElemento,&estado,&retorno);
	} else if (estado == Nodo::ERROR){
		return this->OPERACION_FALLIDA;
	}

	this->incrCantElem();
	this->actualizarCambios();

	//Si llego hasta aqui es por que la inserscion se hizo correctamente
	return this->OPERACION_EXITOSA;
}

/* Insertar privado */
void ArbolB::Insertar(Nodo * nodo, Nodo::TClave clave, void * elemento, unsigned short int longitudElemento,
		Nodo::TRetorno * retorno, Nodo::Estado * estado) {

		if (nodo->getTipo() == Nodo::NODO_HOJA) {
			//Control de unicidad
			if (nodo->getCantidadElementos() > 0 && ((NodoHoja*)nodo)->BuscarExacto(clave)!=nodo->getCantidadElementos()) {
				*estado = Nodo::ERROR;
			} else {
				//Si le agrego el elemento, el nodo hace overflow?
				if (((NodoHoja*)nodo)->isOverflow(longitudElemento)) {
					retorno->separador = ((NodoHoja*) nodo)->buscarMedio(clave,longitudElemento);
					(*estado) = Nodo::OVERFLOW_HOJA;
				} else {
					//Si la funcion no devuelve 0, hubo algun problema.
					if (((NodoHoja*)nodo)->agregarElemento(clave,elemento,longitudElemento)!=0) {
						*estado = Nodo::ERROR;
					} else {
						*estado = Nodo::MODIFICADO;
					}
				}
			}

		} else { // Es un nodo interior
				Nodo::IDNodo idSucesor;
				Nodo * sucesor;
				idSucesor = ((NodoInterno*)nodo)->buscarSucesor(clave);

				if (idSucesor==0) {
					*estado = Nodo::ERROR;
					return;
				}

				sucesor = this->leerNodo(idSucesor);

				this->Insertar(sucesor,clave,elemento,longitudElemento,retorno,estado);
				if (*estado == Nodo::MODIFICADO) {
					this->grabarNodo(sucesor,idSucesor);
				} else if (*estado == Nodo::OVERFLOW_HOJA || *estado == Nodo::OVERFLOW_INTERNO) {
					this->resolver_overflow(nodo,sucesor,clave,elemento,longitudElemento,retorno,estado);
				} // Sino es ninguna es que no se modifico, no necesito guardarlo.

				//Se libera de memoria
				delete(sucesor);
		}
}

void ArbolB::resolver_overflow(Nodo * nodo,Nodo* sucesor, Nodo::TClave clave, void * elemento, unsigned short int longitudElemento,	Nodo::TRetorno * retorno, Nodo::Estado * estado){

	Nodo::IDNodo idNodo1;
	if (*estado == Nodo::OVERFLOW_HOJA) {
			idNodo1 = this->getIDNodoLibre();
			NodoHoja * nodo1 = new NodoHoja (this->longitudBloque,idNodo1);
			//Parto al nodo que hizo overflow
			((NodoHoja*) sucesor)->partir(nodo1,retorno->separador,clave,elemento,longitudElemento);
			//Establezco las relaciones secuenciales
			nodo1->setSucesorDerecho(((NodoHoja*) sucesor)->getSucesorDerecho());
			#ifdef DOBLE_ENLACE
				nodo1->setSucesorIzquierdo(sucesor->getID());
				//El nodo que se partio tiene un sucesor a la derecha?
				if (((NodoHoja*) sucesor)->getSucesorDerecho() > 0) {
					//Obtengo el nodo a la derecha
					NodoHoja * auxNodo = (NodoHoja*) this->leerNodo(((NodoHoja*) sucesor)->getSucesorDerecho());
					//A este nodo le asino el nodo nuevo que se genero al partir el nodo actual
					auxNodo->setSucesorIzquierdo(idNodo1);
					//Grabo el nodo
					this->grabarNodo(auxNodo, ((NodoHoja*) sucesor)->getSucesorDerecho());
					delete(auxNodo);
				}
			#endif
			((NodoHoja*) sucesor)->setSucesorDerecho(idNodo1);

			//Los guardo
			this->grabarNodo(nodo1,idNodo1);
			delete(nodo1);
	} else {
		idNodo1 = retorno->apuntadorDerecho;
	}

	// Me entra el elemento que subio?
	if (!((NodoInterno*)nodo)->acepta_clave()) {
		//No me entra, la hoja interna hizo overflow
		Nodo::IDNodo idNodo2 = this->getIDNodoLibre();

		NodoInterno * nodo2 = new NodoInterno(this->longitudBloque,idNodo2);
		retorno->separador = ((NodoInterno*)nodo)->partir(nodo2,retorno->separador,sucesor->getID(),idNodo1);
		retorno->apuntadorDerecho = idNodo2;

		this->grabarNodo(nodo2,idNodo2);
		delete(nodo2);

		*estado = Nodo::OVERFLOW_INTERNO;
	} else {
		((NodoInterno*)nodo) ->agregarID(retorno->separador,sucesor->getID(),idNodo1);
		*estado = Nodo::MODIFICADO;
	}

	this->grabarNodo(sucesor,sucesor->getID());
}

void ArbolB::resolver_overflow_raiz(Nodo::TClave clave, void * elemento, Nodo::TLongElem longitudElemento, Nodo::Estado * estado, Nodo::TRetorno * retorno) {

	Nodo::IDNodo idNodo1;
	Nodo::IDNodo idNodo2;

	if (*estado== Nodo::OVERFLOW_HOJA) {
		// Obtengo un nuevo espacio de bloque
		idNodo1 = this->getIDNodoLibre();
		idNodo2 = this->getIDNodoLibre();
		//Creo un nodo donde voy a poner la mitad que parta
		NodoHoja * nodo2 = new NodoHoja (this->longitudBloque,idNodo2);
		// Parto la raiz
		((NodoHoja*) raiz)->partir(nodo2,retorno->separador,clave,elemento,longitudElemento);
		//Establezco la relacion secuencial
		nodo2->setSucesorIzquierdo(idNodo1);
		((NodoHoja*) raiz)->setSucesorDerecho(idNodo2);
		// Grabo el nodo que contiene la mitad de la raiz que parti anteriormente
		this->grabarNodo(nodo2,idNodo2);
		delete(nodo2);
	} else {
		//La raiz se abre en dos.
		idNodo1 = this->getIDNodoLibre();
		idNodo2 = retorno->apuntadorDerecho;
		this->grabarNodo(this->raiz,idNodo1);
	}

	// La que era la raiz ahora la guardo como un nodo comun en una de las posiciones que
	// obtuve anteriormente
	this->grabarNodo(this->raiz,idNodo1);
	//Se libera la memoria que ocupaba la vieja raiz
	delete(this->raiz);
	// Creo una nueva raiz que es un nodo interno
	this->raiz = new NodoInterno(this->longitudBloque,0);
	// Le agrego el elemento que me retorno la funcion, que hace de separador
	((NodoInterno*) raiz)->agregarID(retorno->separador,idNodo1,idNodo2);
	//Se actualiza la raiz
	this->grabarNodo(this->raiz,0);
	//Si se abrio creco en altura
	this->incrAltura();
}

void * ArbolB::Buscar(Nodo * nodo, Nodo::TClave clave, Nodo::TClave * claveDevuelta) {
	void * resultado;

	if (nodo->getTipo() ==Nodo::NODO_HOJA) {
		unsigned int pos;
		//Intento buscar la clave en el nodo. La busqueda no es exacta entonces
		// si la clave no se encuentra va a devolver la posicion del elemento que sea
		// superior. Si no puede ninguna de las dos, devuelve una posicion invalida
		// que es la cantidad de elementos del vector.
		pos  = ((NodoHoja*) nodo)->Buscar(clave,false);
		// Posicion devuelta valida?
		if (pos == nodo->getCantidadElementos()) {
			//El elemento no existe, ni tiene un superior EN ESTE NODO.
			//Me fjo si el nodo tiene un hermano, entonces el primer elemento
			//sera el superior del buscado
			if (((NodoHoja*)nodo)->getSucesorDerecho()!=0) {

				NodoHoja * n = (NodoHoja*) this->leerNodo(((NodoHoja*)nodo)->getSucesorDerecho());
				resultado = n->getElemento(0);
				*claveDevuelta = n->getClave(0);
				//Seteo de busqueda secuencial.
				this->iniciarRecorridoSecuencial(n,0);
				//Libero la memoria
				delete(n);

				return resultado;
			} else {
				//No existe un elemeno con esa clave ni tiene un elemento superior
				*claveDevuelta=0;
				return NULL;
			}
		} else {
			//Seteo de busqueda secuencial.
			this->iniciarRecorridoSecuencial((NodoHoja*)nodo,pos);
			//La busqueda fue exacta?
			if ( nodo->getClave(pos)==clave) {
				*claveDevuelta = clave;
			} else{
				*claveDevuelta = nodo->getClave(pos);
			}

			// Devuelvo el elemento
			return ((NodoHoja*)nodo)->getElemento(pos);
		}
	} else {
		Nodo * sucesor;
		sucesor = this->leerNodo(((NodoInterno*)nodo)->buscarSucesor(clave));
		resultado = this->Buscar(sucesor,clave,claveDevuelta);
		//Libero la memoria
		delete(sucesor);
		//Devuelvo el resultado
		return resultado;
	}
}

/* Funcion privada buscar. El buscar es aproximado. Si no encuentra el elemento
 * devuelve el siguiente superior. Devuelve un puntero al elemento. */
void * ArbolB::Buscar(Nodo::TClave clave, Nodo::TClave * claveDevuelta) {
	return Buscar(this->raiz,clave, claveDevuelta);
}

void ArbolB::Modificar(Nodo * nodo, Nodo::TClave clave, void * elemento, unsigned short int longitudElemento, Nodo::Estado * estado, Nodo::TRetorno * retorno) {

	if (nodo->getTipo() == Nodo::NODO_HOJA) {

		unsigned int pos;
		pos  = ((NodoHoja*) nodo)->Buscar(clave,false);
		// Posicion devuelta valida?
		if (pos < nodo->getCantidadElementos()) {
			//El elemento no existe, ni tiene un superior EN ESTE NODO.
			//Me fjo si el nodo tiene un hermano.
			((NodoHoja*)nodo)->cambiarElemento(pos,elemento,longitudElemento,estado,retorno);
		} else {		// La clave no existe.
			*estado=Nodo::ERROR;
		}
	} else {
		Nodo::IDNodo idSucesor;	Nodo * sucesor;

		idSucesor = ((NodoInterno*)nodo)->buscarSucesor(clave);
		sucesor = this->leerNodo(idSucesor);

		this->Modificar(sucesor,clave, elemento, longitudElemento,estado,retorno);

		//Si se modifico lo guardo
		if (*estado==Nodo::MODIFICADO) {
			this->grabarNodo(sucesor,idSucesor);
			*estado=Nodo::SIN_NOVEDAD;
		} else if (*estado == Nodo::UNDEFLOW_INTERNO || *estado == Nodo::UNDERFLOW_HOJA) {
			//veo la pos del sucesor que estoy utilizando
			int pos_s = ((NodoInterno*)nodo)->buscarPosSucesor(clave);
			this->resolver_underflow(nodo,sucesor,pos_s,retorno,estado);
		} else if (*estado == Nodo::OVERFLOW_HOJA || *estado == Nodo::OVERFLOW_INTERNO) {
			this->resolver_overflow(nodo,sucesor,clave,elemento,longitudElemento,retorno,estado);
		}

		//Libero la memoria
		delete(sucesor);
	}
}

/* Modificar publico. */
ArbolB::Resultado ArbolB::Modificar(Nodo::TClave clave, void * elemento, unsigned short int longitudElemento) {
	Nodo::Estado estado;
	Nodo::TRetorno retorno;

	this->Modificar(this->raiz,clave,elemento,longitudElemento,&estado, &retorno);

	if (estado == Nodo::MODIFICADO) {
		this->grabarNodo(this->raiz,0);
	} else if (estado == Nodo::OVERFLOW_HOJA || estado == Nodo::OVERFLOW_INTERNO) {
		this->resolver_overflow_raiz(clave,elemento,longitudElemento,&estado,&retorno);
	} else if (estado == Nodo::UNDERFLOW_HOJA || estado == Nodo::UNDEFLOW_INTERNO) {
		this->resolver_underflow_raiz(&estado);
	} else if (estado == Nodo::ERROR) {
		return this->OPERACION_FALLIDA;
	}
	//Se actualizan los cambios
	this->actualizarCambios();
	//Si se llego hasta aqui es que la modificacion se hizo correctamente.
	return this->OPERACION_EXITOSA;

}

bool ArbolB::concatenar(Nodo* nodo_ppal,unsigned int pos_suc, Nodo* nodo_suc){
	Nodo::IDNodo idOrigen, idDestino;
	Nodo * origen;
	Nodo  * destino;

	unsigned int posReferenciaEliminar;
	Nodo::TClave separadorBaja;

	// Tiene un nodo vecino a la izquierda?
	if (pos_suc>0) {
		// El origen va a ser el nodo sucesor y los elementos van a ser pasados
		// al nodo que tiene a su izquierda
		idDestino =  ((NodoInterno*)nodo_ppal)->getSucesor(pos_suc - 1);
		destino =  this->leerNodo( idDestino );

		idOrigen = nodo_suc->getID();
		origen = nodo_suc;

		posReferenciaEliminar = pos_suc - 1;
	} else { // Concateneo con el vecino de la derecha
		//El origen va a ser el nodo que tiene a la derecha y van a ser pasados la sucesor
		idDestino = nodo_suc->getID();
		destino = nodo_suc;

		idOrigen =  ((NodoInterno*)nodo_ppal)->getSucesor(1);
		origen =  this->leerNodo( idOrigen );

		posReferenciaEliminar = 0;
	}
	//Obtengo la clave que baja
	separadorBaja = ((NodoInterno*)nodo_ppal)->getClave(posReferenciaEliminar);
	//Se elimina la clave que referenciaba al nodo concatenado
	((NodoInterno*)nodo_ppal)->eliminarElemento(posReferenciaEliminar);

	//Que tipo de nodos estoy concatenando?
	if (nodo_suc->getTipo() == Nodo::NODO_HOJA) {
			Nodo::IDNodo sucesorDerecho = 0;

			((NodoHoja*)destino)->concatenar( ((NodoHoja*)origen));
			sucesorDerecho = ((NodoHoja*)origen)->getSucesorDerecho()  ;

			((NodoHoja*)destino)->setSucesorDerecho(sucesorDerecho);
			//Como es un nodo hoja se actualizan la relacion secuencial

			#ifdef DOBLE_ENLACE
				if ( sucesorDerecho ) {
					Nodo* derecho = this->leerNodo(sucesorDerecho);
					((NodoHoja*)derecho)->setSucesorIzquierdo(idDestino);
					this->grabarNodo(derecho, sucesorDerecho);
					//Libero memoria
					delete(derecho);
				}
			#endif
	} else {
		//Agrego al clave que baja
		//No importa el sucesor izquierdo ya que va a ser remplazado por la referencia del nodo que
		//origen
			((NodoInterno*)destino)->agregarID(separadorBaja, ((NodoInterno*)destino)->getSucesor(destino->getCantidadElementos()),0);
		//agrego el elemento al nodo
			((NodoInterno*)destino)->concatenar( ((NodoInterno*)origen));
	}

	//libero los ids de los nodos que ya no utilizo
	this->addIDNodoLibre(idOrigen);
	//Grabo el nodo que fue modificado ya que se le pasaron elementos
	this->grabarNodo(destino,idDestino);

	//Solo se elimina el nodo que fue leido dentro de esta funcion
	if (destino == nodo_suc){
		delete(origen);
	} else {
		delete(destino);
	}

	return true ;
}

void ArbolB::suprimir_elemento(NodoHoja* nodo,Nodo::TClave clave,Nodo::TRetorno* retorno, Nodo::Estado* estado){

	//obtengo la posicion en el nodo
	unsigned int pos = nodo->BuscarExacto(clave);

	// El elemento se encuentra?
	if(pos != nodo->getCantidadElementos()){
		//elimino la clave del nodo
		nodo->eliminarElemento(pos);
		this->decrCantElem();


		if(((NodoHoja*)nodo)->isUnderflow()) {
			*estado = Nodo::UNDERFLOW_HOJA;
		} else {
			*estado = Nodo::MODIFICADO;
		}
	}else {
		//El elemento no existe, no se puede eliminar
		*estado = Nodo::ERROR;
	}
}

void ArbolB::resolver_underflow(Nodo* nodo,Nodo* sucesor,int pos_s,Nodo::TRetorno* retorno, Nodo::Estado* estado){

	int underf_resuelto = true;

	//intento rotar, sino se puede concateno nodos
	if( ! rotar(nodo,pos_s,sucesor))
		underf_resuelto = concatenar(nodo,pos_s,sucesor);

	//modifico la variable de estado chequeando si hay underflow
	if(!underf_resuelto){
		*estado= Nodo::ERROR;
	}else if(((NodoInterno*)nodo)->isUnderflow()){
		*estado = Nodo::UNDEFLOW_INTERNO;
	}else{
		*estado = Nodo::MODIFICADO;
	}

}

void ArbolB::resolver_underflow_raiz(Nodo::Estado * estado) {
	//La raiz recibe un tratamiento especial en caso de underflow siendo nodo interno
	if (*estado == Nodo::UNDEFLOW_INTERNO) {
		//La raiz tiene menos de la minima cantidad que puede tener?
		if (this->raiz->getCantidadElementos() < 1) {
			//La debe bajar un nivel.
			//La raiz quedo con 0 elementos, solo tiene un sucesor.
			Nodo::IDNodo idSucesor = ((NodoInterno*) this->raiz)->getSucesor(0);
			//Este sucesor ahora se convertira en la raiz.
			//Libero la raiz vieja
			delete(this->raiz);
			//Cargo la nueva raiz.
			this->raiz = this->leerNodo(idSucesor);
			this->raiz->setID(0);
			//Se libera el ID del sucesor que paso a ser la raiz
			this->addIDNodoLibre(idSucesor);
			//Se reduce la altura del nodo.
			this->decrAltura();
		}
	}
	//Se graba la raiz.
	this->grabarNodo(this->raiz,0);
}

void ArbolB::suprimir(Nodo* nodo, Nodo::TClave clave, Nodo::TRetorno* retorno, Nodo::Estado* estado) {

	if(nodo->getTipo() == Nodo::NODO_HOJA){

		this->suprimir_elemento((NodoHoja*)nodo,clave,retorno,estado);

	}else {

		//Obtengo el sucesor correspondiente
		Nodo::IDNodo id_sucesor = ( (NodoInterno*) nodo)->buscarSucesor(clave);
		Nodo* sucesor = this->leerNodo( id_sucesor);

		//mando a suprimir por la rama sucesora
		this->suprimir(sucesor,clave,retorno,estado);

		if( *estado == Nodo::MODIFICADO){
				this->grabarNodo(sucesor,id_sucesor);
				*estado = Nodo::SIN_NOVEDAD;
		} else if (*estado == Nodo::UNDEFLOW_INTERNO || *estado ==  Nodo::UNDERFLOW_HOJA){
				//Obtengo la posicion del sucesor
				int pos_s = ((NodoInterno*)nodo)->buscarPosSucesor(clave);
				resolver_underflow(nodo,sucesor,pos_s,retorno,estado);
		}

		delete(sucesor);
	}
}

ArbolB::Resultado ArbolB::suprimir(Nodo::TClave clave) {

	Nodo::Estado estado;
	Nodo::TRetorno retorno;

	//El arbol tiene elementos?
	if (this->cantidad_elementos>0) {

		this->suprimir(raiz,clave,&retorno,&estado);

		if ( estado == Nodo::MODIFICADO) {
			this->grabarNodo(this->raiz,0);
		} else if (estado == Nodo::UNDEFLOW_INTERNO || estado == Nodo::UNDERFLOW_HOJA) {
			this->resolver_underflow_raiz(&estado);
		} else if (estado == Nodo::ERROR) {
			//Devuevo codigo de error;
			return this->OPERACION_FALLIDA;
		}
	} else {
		//No hay elementos en el arbrol
		return this->OPERACION_FALLIDA;
	}

	//Se actualizan los cambios en el arbol
	this->actualizarCambios();
	return this->OPERACION_EXITOSA;
}

bool ArbolB::rotar(Nodo* nodo_ppal,unsigned int pos_suc, Nodo* nodo_suc){

	//variable de retorno
	bool rotado = false;

	if( pos_suc > 0){
		//intento pedir del nodo izq
		Nodo* nodo_izq = this->leerNodo( ((NodoInterno*)nodo_ppal)->getSucesor(pos_suc-1));
		int nueva_clave;
		int pos_ultimo = nodo_izq->getCantidadElementos()-1;

		if(nodo_izq->getTipo() == Nodo::NODO_HOJA ){

			NodoHoja* izq = (NodoHoja*) nodo_izq;

			if(izq->cede_ultimo()){
				//Obtengo el elemento que va a cambiar de nodo
				char * elemento = (char *) izq->getElemento(pos_ultimo);
				//agrego el elemento al nodo que hizo underflow
				((NodoHoja*)nodo_suc)->agregarElemento(izq->getClave(pos_ultimo),elemento, izq->getLongitudElem(pos_ultimo));
				delete[](elemento);

				nueva_clave = izq->getClave(pos_ultimo);
				//elimino el elemento del nodo izquierdo
				izq->eliminarElemento(pos_ultimo);

				((NodoInterno*)nodo_ppal)->setClave(nueva_clave,pos_suc-1);
				this->grabarNodo(nodo_suc,((NodoInterno*)nodo_ppal)->getSucesor(pos_suc));
				this->grabarNodo(nodo_izq,((NodoInterno*)nodo_ppal)->getSucesor(pos_suc-1));

				rotado = true;
			}

		} else {

			NodoInterno* izq = (NodoInterno*) nodo_izq;

			if(izq->cede_clave()){
				//agrego el elemento al nodo sucesor
				((NodoInterno*)nodo_suc)->agregarID(((NodoInterno*)nodo_ppal)->getClave(pos_suc-1),izq->getSucesor(pos_ultimo + 1),
										 ((NodoInterno*)nodo_suc)->getSucesor(0));
				nueva_clave = izq->getClave(pos_ultimo);
				int nueva_ref = izq->getSucesor(pos_ultimo);
				//elimino el elemento del nodo izquierdo
				izq->eliminarElemento(pos_ultimo);
				izq->setSucesor(nueva_ref,izq->getCantidadElementos());

				((NodoInterno*)nodo_ppal)->setClave(nueva_clave,pos_suc-1);
				this->grabarNodo(nodo_suc,((NodoInterno*)nodo_ppal)->getSucesor(pos_suc));
				this->grabarNodo(nodo_izq,((NodoInterno*)nodo_ppal)->getSucesor(pos_suc-1));

				rotado = true;
			}
		}

		//El elimino el nodo leido.
		delete(nodo_izq);
	}

	//si no se pudo rotar pido del nodo derecho
	if ( !rotado &&  (pos_suc < nodo_ppal->getCantidadElementos())){

		Nodo* nodo_der = this->leerNodo( ((NodoInterno*)nodo_ppal)->getSucesor(pos_suc + 1) );
		int nueva_clave;

		if(nodo_der->getTipo() == Nodo::NODO_HOJA){

			NodoHoja* der = (NodoHoja*) nodo_der;

			if(der->cede_primero()){
				//agrego el elemento al nodo sucesor
				char * elemento = (char *) der->getElemento(0);
				((NodoHoja*)nodo_suc)->agregarElemento(der->getClave(0), elemento, der->getLongitudElem(0));
				delete[](elemento);
				//elimino el elemento del nodo der
				der->eliminarElemento(0);
				nueva_clave = der->getClave(0);
				((NodoInterno*)nodo_ppal)->setClave(nueva_clave,pos_suc);

				this->grabarNodo(nodo_suc,((NodoInterno*)nodo_ppal)->getSucesor(pos_suc));
				this->grabarNodo(nodo_der,((NodoInterno*)nodo_ppal)->getSucesor(pos_suc+1));
				rotado = true;
			}
		} else {

			NodoInterno* der = (NodoInterno*) nodo_der;
			if( der->cede_clave()){
				//agrego el elemento al nodo sucesor
				((NodoInterno*)nodo_suc)->agregarID(((NodoInterno*)nodo_ppal)->getClave(pos_suc),((NodoInterno*)nodo_suc)->getSucesor(nodo_suc->getCantidadElementos()),
										 der->getSucesor(0));
				nueva_clave = der->getClave(0);
				//elimino el elemento del nodo izquierdo
				der->eliminarPrimerSeparador();
				((NodoInterno*)nodo_ppal)->setClave(nueva_clave,pos_suc);

				this->grabarNodo(nodo_suc,((NodoInterno*)nodo_ppal)->getSucesor(pos_suc));
				this->grabarNodo(nodo_der,((NodoInterno*)nodo_ppal)->getSucesor(pos_suc+1));
				rotado = true;
			}
		}

		delete(nodo_der);
	}

	return rotado;
}

/* RECORRIDO SET SECUENCIAL */
bool ArbolB::tieneSiguiente() {
	return (this->recorridoSecuencial.sigPos >= 0);
}

/* Inicia el recorrido secuencial  apartir del nodo y posicion dados */
void ArbolB::iniciarRecorridoSecuencial(NodoHoja * nodo, unsigned short int pos) {

	//Para el siguiente
	/// Si la pos es menor que la cantidad - 1 de elemetos.
	if (pos < nodo->getCantidadElementos()-1) {
			// el nodoSig es el actual
			this->recorridoSecuencial.sigNodo = nodo->getID();
			// la pos, es pos1
			this->recorridoSecuencial.sigPos = pos+1;
	} else {
			// Veo si tiene hermano a derecha.
			if (nodo->getSucesorDerecho()!=0) {
				this->recorridoSecuencial.sigNodo = nodo->getSucesorDerecho();
				this->recorridoSecuencial.sigPos = 0;
			} else {
				this->recorridoSecuencial.sigPos = -1;
			}
	}
	//Para el anterior
	//Si la pos es mayor a 0.
	if (pos > 0) {
		this->recorridoSecuencial.antNodo= nodo->getID();
		this->recorridoSecuencial.antPos=pos-1;
	} else {
		//Me fijo si tiene vecino a izquierda
		if (nodo->getSucesorIzquierdo()!=0) {
			//Si tiene empieza de ahi con -3
			this->recorridoSecuencial.antNodo = nodo->getSucesorIzquierdo();
			this->recorridoSecuencial.antPos=-3;
		} else { //No tiene nada a izquierda
			this->recorridoSecuencial.antNodo= nodo->getID();
			this->recorridoSecuencial.antPos=-2;
		}
	}
	//persisto los cambios
	this->cambios = true;
	actualizarCambios();
}

/* Inicia el recorrido secuencial a partir de la raiz */
void ArbolB::iniciarRecorridoSecuencial(){

	//Por como se parte a los nodos el primer elemento puede estar en el nodo hoja
	// o en el nodo 1
	this->recorridoSecuencial.antPos=-2;

	if (this->raiz->getTipo()== Nodo::NODO_HOJA) {

		this->recorridoSecuencial.sigNodo=0;
		this->recorridoSecuencial.antNodo=0;

		if (this->raiz->getCantidadElementos()==0) {
			//El Arbol no tiene elementos
			this->recorridoSecuencial.sigPos=-1;
		} else {
			this->recorridoSecuencial.sigPos=0;
		}
	} else {
		this->recorridoSecuencial.sigNodo=1;
		this->recorridoSecuencial.sigPos=0;
		this->recorridoSecuencial.antNodo=1;
	}
	//persisto los cambios
	this->cambios = true;
	actualizarCambios();

}

/* Devuelve el elemento y aumenta una posicion el puntero al siguiente */
void * ArbolB::getSiguiente(Nodo::TClave * claveDevuelta) {
	NodoHoja * aux;
	void * elemento;

	//¡Hay siguiente?
	if (this->tieneSiguiente()) {

		//Leo el nodo
		aux = (NodoHoja*) this->leerNodo(this->recorridoSecuencial.sigNodo);

		elemento = aux->getElemento(this->recorridoSecuencial.sigPos);
		*claveDevuelta =  aux->getClave(this->recorridoSecuencial.sigPos);
		//Avazo una posicion
		this->recorridoSecuencial.sigPos++;

		if (this->recorridoSecuencial.sigPos==2) {
			//Si estoy en la segunda posicion del nodo el anterior va a ser el 0 de este nodo
			// y va a dejar de ser la ultima posicion del anterior nodo
			this->recorridoSecuencial.antNodo = this->recorridoSecuencial.sigNodo;
			this->recorridoSecuencial.antPos = 0;
		} else {
			//Tambien avanza el anterior
			this->recorridoSecuencial.antPos++;
		}

		// Esta posicion no es valida? No hay mas elementos en el nodo que recorrer?
		if (aux->getCantidadElementos() <= this->recorridoSecuencial.sigPos) {
			// Tiene un nodo a su derecha?
			if (aux->getSucesorDerecho()!=0) {
				this->recorridoSecuencial.sigPos=0;
				this->recorridoSecuencial.sigNodo=aux->getSucesorDerecho();
			} else {
				this->recorridoSecuencial.sigPos=-1;
			}
		}

		//persisto los cambios
		this->cambios = true;
		actualizarCambios();

		delete(aux);
		return elemento;
	} else {
		return NULL;
	}
}

#ifdef DOBLE_ENLACE
bool ArbolB::tieneAnterior(){
	return (this->recorridoSecuencial.antPos!=-1 && this->recorridoSecuencial.antPos!=-2);
}

void * ArbolB::getAnterior(Nodo::TClave * claveDevuelta) {
	NodoHoja * aux;
	void * elemento;

	//¡Hay anterior?
	if (this->tieneAnterior()) {
		//Leo el nodo
		aux = (NodoHoja*) this->leerNodo(this->recorridoSecuencial.antNodo);

		if (this->recorridoSecuencial.antPos==-3) {
			this->recorridoSecuencial.antPos= aux->getCantidadElementos()-1;
		}

		elemento = aux->getElemento(this->recorridoSecuencial.antPos);
		*claveDevuelta = aux->getClave(this->recorridoSecuencial.antPos);

		//retrocedo una posicion
		this->recorridoSecuencial.antPos--;
		this->recorridoSecuencial.sigPos--;
		//retrocedo tambien el siguient
		if (this->recorridoSecuencial.sigPos<=-1) {
			this->recorridoSecuencial.sigNodo=this->recorridoSecuencial.antNodo;
			this->recorridoSecuencial.sigPos=aux->getCantidadElementos()-1;
		}
		//No hay nada mas que recorrer en este nodo. Me fijo si puedo ir para
		//la izquierda con otro nodo.
		if (this->recorridoSecuencial.antPos==-1) {
			// Tiene un nodo a su izquierda
			if (aux->getSucesorIzquierdo()!=0) {
				//El -3 es un flag que avisa que va a empezar desde la
				// ultima posicion de ese nodo. Con esto se ahorra un acceso a disco
				// para obtener la cantidad de elementos que tiene ese nodo
				this->recorridoSecuencial.antPos=-3;
				this->recorridoSecuencial.antNodo=aux->getSucesorIzquierdo();
			} else {
				//No tiene anterior
				this->recorridoSecuencial.antPos=-1;
			}
		}
		//persisto los cambios
		this->cambios = true;
		actualizarCambios();

		delete(aux);
		return elemento;
	} else {
		return NULL;
	}
}
#endif

/* FUNCION PARA VISUALIZACION  */
//PRIVADA
void ArbolB::visualizar(Nodo * n, unsigned short int margen, FILE * salida) {
	unsigned int i;

	fprintf(salida,"\n%*sNodo %i: ", margen, " ", n->getID());

	if (n->getTipo() == Nodo::NODO_HOJA) {

		NodoHoja * hoja = (NodoHoja*) n;

		#ifdef DOBLE_ENLACE
			fprintf(salida,"(%i)", hoja->getSucesorIzquierdo());
		#endif

		for (i = 0; i < hoja->getCantidadElementos(); i++) {
			fprintf(salida,"%i ",hoja->getClave(i));
		}

		fprintf(salida, "(%i) > %i%%", hoja->getSucesorDerecho(), hoja->getPorcentajeOcupacional());

	} else {
		NodoInterno * interno = (NodoInterno*) n;
		Nodo * aux;

		fprintf(salida, "(%i)",interno->getSucesor(0));

		for (i = 0; i < interno->getCantidadElementos(); i++) {
			fprintf(salida,"%i (%i) ",interno->getClave(i), interno->getSucesor(i+1));
		}

		fprintf(salida, "> %i%%", interno->getPorcentajeOcupacional());

		for (i = 0; i <= interno->getCantidadElementos(); i++) {
			aux =this->leerNodo(interno->getSucesor(i)),
			this->visualizar(aux, margen+3,salida);
			delete(aux);
		}
	}
}
// PUBLICA
void ArbolB::visualizar(bool full,FILE * salida) {
	unsigned int cantNodosLibres;
	unsigned int* data;
	unsigned int i;

	/* Se imprime la estructura del arbol */
	if (this->cantidad_elementos==0){
		fprintf(salida,"El Arbol esta vacio.\n");
	} else {
		fprintf(salida, "Cantidad de elementos: %i  Altura: %i", this->cantidad_elementos, this->altura);

		this->visualizar(this->raiz,0,salida);
	}

	/* Elementos que corresponden a las claves */
	if (full && this->cantidad_elementos > 0) {
		char * elemento;
		Nodo::TClave clave;
		this->iniciarRecorridoSecuencial();

		fprintf(salida,"\n(Clave;Elemento)\n");
		while (this->tieneSiguiente()) {
			elemento = (char*) this->getSiguiente(&clave);
			fprintf(salida,"(%i;%s)\n",clave, elemento);
			delete[](elemento);
		}
	}

	/* Informacion de los nodos libres */
	data = ControladorIDsLibres_getAllLibres(&this->controladorNodosLibres,&cantNodosLibres);

	if (cantNodosLibres > 0) {
		fprintf(salida,"\nNodos libres (%i): ",cantNodosLibres);

		for (i=0; i < cantNodosLibres - 1; i++) {
			fprintf(salida,"%i - ", data[i]);
		}
		fprintf(salida,"%i",data[i]);
	} else {
		fprintf(salida, "\nNo hay nodos libres.\n");
	}
	free(data);
}

/* DESTRUCTOR */
ArbolB::~ArbolB(){
	this->actualizarCambios();
	//Ciero el archivo
	fclose(this->handleFile);
	//Guardo el controlador de nodos libres.
	ControladorIDsLibres_cerrar(&this->controladorNodosLibres);
	//Libero la memoria utilizada
	delete(this->raiz);
	delete[](this->bloque);
}
