/*
 * NodaHoja.cpp
 *
 *  Created on: 26/03/2010
 *      Author: Grupo Klow
 */


#include "NodoHoja.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>

// Creo el nodo a partir del bloque leido
NodoHoja::NodoHoja(unsigned int bytesCapacidad, char * bloque, Nodo::IDNodo id) {
	this->iniciar(bytesCapacidad, id);
	this->Cargar(bloque);
}

// Creo un NodoHoja vacio.
NodoHoja::NodoHoja(unsigned int bytesCapacidad, Nodo::IDNodo id) {
	this->iniciar(bytesCapacidad,id);
}

void NodoHoja::iniciar(unsigned int bytesCapacidad, Nodo::IDNodo id) {
	this->cantidad_elementos = 0;

	this->sucesorDerecho = 0;
	this->sucesorIzquierdo = 0;

	this->ID=id;

	this->registros=NULL;

	//La capacidad del nodo es igual a la capacidad general menos lo que utiliza el nodo
	this->bytesCapacidad=bytesCapacidad - sizeof(IDNodo) - sizeof(IDNodo) - sizeof(unsigned int) - 1;
	this->bytesUtilizados=0;
}

// Informacion de bloque de archivo a Nodo
void NodoHoja::Cargar(char * bloque) {
	unsigned int longitud;
	unsigned int actual=1;
	unsigned int i;

	// Copio la cantidad de elementos que tiene
	longitud = sizeof(unsigned int);
	actual = 1;
	memcpy(&this->cantidad_elementos,&bloque[actual],longitud);

	// Copio el sucesor derecho
	actual+=longitud;
	longitud = sizeof(IDNodo);
	memcpy(&this->sucesorDerecho,&bloque[actual],longitud);

	// Copio el sucesor izquierdo
	actual+=longitud;
	longitud = sizeof(IDNodo);
	memcpy(&this->sucesorIzquierdo,&bloque[actual],longitud);

	this->bytesUtilizados = actual+longitud;

	this->registros= (TRegistro*) malloc(sizeof(TRegistro) * this->cantidad_elementos);

	for (i = 0; i < this->cantidad_elementos; i++) {
		actual+=longitud;

		longitud=sizeof(TClave);
		memcpy(&this->registros[i].ID ,&bloque[actual],longitud);

		actual+=longitud;

		longitud=sizeof(TLongElem);
		memcpy(&this->registros[i].longitudDato,&bloque[actual],longitud);

		actual+=longitud;

		longitud=this->registros[i].longitudDato;
		this->registros[i].dato = new char[longitud];
		memcpy(this->registros[i].dato,&bloque[actual] ,longitud);
	}

	actual+=longitud;

	this->bytesUtilizados = actual - this->bytesUtilizados;
}

// Informacion de Nodo a bloque para escribir en archivo
void NodoHoja::Guardar(char * bloque) {
	unsigned int longitud;
	unsigned int actual=1;
	unsigned int i;

	// Copio el tipo de nodo
	bloque[0]= NODO_HOJA;

	// Copio la cantidad de elementos que tiene
	longitud = sizeof(unsigned int);
	actual = 1;
	memcpy(&bloque[actual],&this->cantidad_elementos,longitud);

	// Copio el sucesor derecho
	actual+=longitud;
	longitud = sizeof(IDNodo);
	memcpy(&bloque[actual],&this->sucesorDerecho,longitud);

	// Copio el sucesor izquierdo
	actual+=longitud;
	longitud = sizeof(IDNodo);
	memcpy(&bloque[actual],&this->sucesorIzquierdo,longitud);


	for (i = 0; i < this->cantidad_elementos; i++) {
		actual+=longitud;

		longitud=sizeof(TClave);
		memcpy(&bloque[actual],&this->registros[i].ID ,longitud);

		actual+=longitud;

		longitud=sizeof(TLongElem);
		memcpy(&bloque[actual],&this->registros[i].longitudDato ,longitud);

		actual+=longitud;

		longitud=this->registros[i].longitudDato;
		memcpy(&bloque[actual],this->registros[i].dato ,longitud);
	}
	actual+=longitud;
}

/* Devuelve 0 si pudo agregar el elemento correctamente.
 * Caso contrario (no respeta unicidad/falta memoria) devuelve 1 */
unsigned short int NodoHoja::agregarElemento(TClave id, void * elemento, unsigned int longitudElemento) {

	//Tiene un tamanio permitido?
	if (longitudElemento <= this->bytesCapacidad * (PORCENTAJE_MAX_ELEM * 0.01) ) {
		//Pido memoria para el nuevo elemento
		this->registros = (TRegistro*) realloc(this->registros,sizeof(TRegistro) * (this->cantidad_elementos+1));

		int pos = this->cantidad_elementos-1;

		while (pos >= 0 && this->registros[pos].ID > id) {
			this->registros[pos+1] = this->registros[pos];
			pos--;
		}

		this->registros[pos+1].ID= id;
		this->registros[pos+1].longitudDato = longitudElemento;
		this->registros[pos+1].dato = new char [longitudElemento];

		memcpy(this->registros[pos+1].dato,elemento,longitudElemento);

		this->bytesUtilizados+= sizeof(TClave) + sizeof(TLongElem) + longitudElemento;
		this->cantidad_elementos++;
		return 0;
	} else {
		return 1;
	}
}

void NodoHoja::setSucesorDerecho(IDNodo idnodo) {
	this->sucesorDerecho=idnodo;
}

void NodoHoja::setSucesorIzquierdo(IDNodo idnodo) {
	this->sucesorIzquierdo=idnodo;
}

void NodoHoja::partir(NodoHoja * nodo, TClave centro, TClave clave, void * elemento, unsigned int longitudElemento) {
	int i = this->cantidad_elementos-1;
	bool izquierda = false;

	if (clave < centro) {
		izquierda = true;
	}

	while ( i >= 0 && this->registros[i].ID >= centro) {
			nodo->agregarElemento(this->registros[i].ID, this->registros[i].dato, this->registros[i].longitudDato);
			this->eliminarElemento(i);
			i--;
	}

	if (izquierda) {
		this->agregarElemento(clave, elemento,longitudElemento);
	} else {
		nodo->agregarElemento(clave,elemento,longitudElemento);
	}
}

/* Obtiene la clave del centro teniendo en cuenta los pesos */
Nodo::TClave NodoHoja::buscarMedio(TClave clave, TLongElem longitudElemento){

	unsigned int bytesAgregar = sizeof(TClave) + sizeof(TLongElem) + longitudElemento;
	unsigned int peso = 0;
	unsigned int pesoAnterior = 0;
	unsigned int i = 0;
	unsigned int posClave= this->cantidad_elementos+1; //Este valor sirve para indicar que la clave no fue puesta
	unsigned int pesoMedio = (this->bytesUtilizados+bytesAgregar) / 2;

	while (peso < pesoMedio && this->registros[i].ID < clave && i < this->cantidad_elementos) {
			pesoAnterior=peso;
			peso+= this->registros[i].longitudDato + sizeof(TClave) + sizeof(TLongElem);
			i++;
	}

	if (peso < pesoMedio) {
		pesoAnterior = peso;
		peso+=longitudElemento + sizeof(TClave) + sizeof(TLongElem);
		posClave = i;
	}

	while (peso < pesoMedio) {
		i++;
		pesoAnterior = peso;
		peso+=this->registros[i-1].longitudDato +  sizeof(TClave) + sizeof(TLongElem);
	}

	if (peso - pesoMedio >= pesoMedio - pesoAnterior) {
		//Combiene la distribucion anterior a la ultima
		//El ultimo que se agrego fue la clave y estaba de mas
		if (i==posClave) {
			return clave;
		} else {
			return this->registros[i-1].ID;
		}
	} else {
		//La clave no llego a ponerse. Puede ser el centro. Puede ser el ultimo elemento o no
		if (posClave == this->cantidad_elementos+1 && this->registros[i-1].ID < clave && (i == this->cantidad_elementos || this->registros[i].ID > clave)) {
			return clave;
		} else {
			return this->registros[i].ID;
		}
	}
	return 0;
}

/* Cambia el elemento que se encuentra en la posicion "pos", liberando
 * la memoria que este utilizaba, por el pasado por parametro */
void NodoHoja::cambiarElemento(unsigned short int pos, void * elemento, unsigned int longitudElemento, Nodo::Estado * estado, Nodo::TRetorno * retorno) {

	// Diferencia en bytes entre el tamaño actual y por el cual se lo quiere cambiar
	//Si es m{as grande el nuevo elemento diferenciaBytes va a ser postivio
	int diferenciaBytes = longitudElemento - this->registros[pos].longitudDato;
	Nodo::TClave clave =  this->registros[pos].ID;
	//Tiene un tamanio permitido?
	if (longitudElemento <= this->bytesCapacidad * (PORCENTAJE_MAX_ELEM * 0.01) ) {
		//La modificacion en el dato hace que este sobrepasa la capacidad del nodo?
		if (this->bytesUtilizados + diferenciaBytes > this->bytesCapacidad ) {
			//El elemento no entra. Lo elimino
			this->eliminarElemento(pos);
			//
			retorno->separador = this->buscarMedio(clave,longitudElemento);
			//Informo que el nodo hizo overflow
			*estado = Nodo::OVERFLOW_HOJA;
		} else {
			//Si el elemento entra en el nodo lo remplazo

			//Libero el espacio de memoria que utilizaba el elemento viejo
			delete[](this->registros[pos].dato);

			this->registros[pos].longitudDato = longitudElemento;
			this->registros[pos].dato = new char [longitudElemento];

			memcpy(this->registros[pos].dato,elemento,longitudElemento);

			//Actualizo el espacio utilizado en el nodo
			this->bytesUtilizados+= diferenciaBytes;

			//Luego del remplazo el nodo puede quedar en underflow o sin problemas.
			if (this->isUnderflow()) {
				*estado = Nodo::UNDERFLOW_HOJA;
			} else {
				*estado = Nodo::MODIFICADO;
			}
		}
	} else {
		*estado = Nodo::ERROR;
	}
}

Nodo::IDNodo NodoHoja::getSucesorDerecho() {
	return this->sucesorDerecho;
}

Nodo::IDNodo NodoHoja::getSucesorIzquierdo() {
	return this->sucesorIzquierdo;
}

Nodo::TipoNodo NodoHoja::getTipo() {
	return Nodo::NODO_HOJA;
}

Nodo::IDNodo NodoHoja::getID() {
	return this->ID;
}

unsigned short int NodoHoja::getCantidadElementos() {
	return this->cantidad_elementos;
}

Nodo::TClave NodoHoja::getClave(unsigned short int posicion) {
	return this->registros[posicion].ID;
}

/* Dada una clave, si existe, devuelve la posicion en la cual se encuentra
 * caso contrario devuelve una posicion invalida, la cantidad de elementos que tiene */
unsigned short int NodoHoja::BuscarExacto(Nodo::TClave clave) {
	return this->Buscar(clave,true);
}

unsigned short int NodoHoja::Buscar(Nodo::TClave clave,bool busquedaExacta) {
	//Como los elementos del nodo estan ordenados
	// para optimizar se realiza una busqueda binaria

	// La busqueda no tiene sentido si el nodo no tiene nada.
	if (this->cantidad_elementos > 0) {
		unsigned short int centro =this->cantidad_elementos;
		int inicio = 0;
		int fin= this->cantidad_elementos-1;

		//Tampoco tiene sentido si el elemento es mayor que el ultimo
		if (this->registros[fin].ID >= clave) {
			//Se inicia la busqueda binaria
			while (inicio <= fin) {
				centro = (fin + inicio) / 2;

				if (this->registros[centro].ID==clave) {
					return centro;
				} else if (this->registros[centro].ID > clave){
					fin = centro - 1;
				} else {
					inicio = centro + 1;
				}
			}
			if (!busquedaExacta) { return centro; }
		}


	}
	return this->cantidad_elementos;
}

/* Hace una copia del elemento que se encuentra en "pos"
 * y la devuelve. */
void * NodoHoja::getElemento(unsigned short int pos) {
	//Hago una copia
	char * buffer;
	buffer = new char[this->registros[pos].longitudDato];
	memcpy(buffer,this->registros[pos].dato,this->registros[pos].longitudDato);
	return buffer;
}

unsigned int NodoHoja::getLongitudElem(unsigned short int pos){
	return this->registros[pos].longitudDato;
}

bool NodoHoja::isOverflow(unsigned int longitudNuevoElemento) {
	unsigned int bytesAgregar;

	bytesAgregar = sizeof(TClave) + sizeof(TLongElem) + longitudNuevoElemento;
	return ((this->bytesUtilizados + bytesAgregar) > (this->bytesCapacidad) );
}

bool NodoHoja::isUnderflow(){
	// Se considera un nodo en underflow si la capacidad utilizada del nodo	es menor a un (50-T)% de su tamanio
	return (this->bytesUtilizados < ( this->bytesCapacidad * (0.5 - (PORCENTAJE_MAX_ELEM*0.01) ) ) );

}

bool NodoHoja::cede_primero(){

	unsigned int tam_cedido = sizeof(TClave) + sizeof(TLongElem) + this->registros[0].longitudDato;
	return ((bytesUtilizados - tam_cedido) > ( this->bytesCapacidad * (0.5 - (PORCENTAJE_MAX_ELEM*0.01) ) ));
}

bool NodoHoja::cede_ultimo(){

	unsigned int tam_cedido = sizeof(TClave) + sizeof(TLongElem) + this->registros[getCantidadElementos()-1].longitudDato;
	return ((bytesUtilizados - tam_cedido) > ( this->bytesCapacidad * (0.5 - (PORCENTAJE_MAX_ELEM*0.01) ) ));
}

unsigned int NodoHoja::getPorcentajeOcupacional() {
	return (this->bytesUtilizados*100/ this->bytesCapacidad);
}

void NodoHoja::eliminarElemento(unsigned short int pos){

	//decremento la cant de elementos
	cantidad_elementos--;

	//Actualizo la cantidad de bytes utilizados
	this->bytesUtilizados-= sizeof(TClave) + sizeof(TLongElem) + this->registros[pos].longitudDato;

	//libero recursos dinamicos
	delete[](this->registros[pos].dato);

	//Elimino el elemento
	while(pos < this->cantidad_elementos){
		this->registros[pos] = this->registros[pos+1];
		pos++;
	}

	//Redimensiono la cantidad de registros
	this->registros = (TRegistro*) realloc(this->registros,sizeof(TRegistro)* (this->cantidad_elementos));
}

void NodoHoja::setID(Nodo::IDNodo id) {
	this->ID = id;
}

void NodoHoja::concatenar(NodoHoja * origen) {

	unsigned int cantidadAPasar = origen->cantidad_elementos;
	unsigned int cantidad = this->cantidad_elementos;

	//Pido memoria para el nuevo elemento
	this->registros = (TRegistro*) realloc(this->registros,sizeof(TRegistro) * (this->cantidad_elementos+origen->cantidad_elementos));

	while (cantidadAPasar > 0) {
		cantidadAPasar--;
		this->registros[cantidad + cantidadAPasar] = origen->registros[cantidadAPasar];
	}

	this->cantidad_elementos+= origen->cantidad_elementos;
	this->bytesUtilizados+= origen->bytesUtilizados;

	origen->cantidad_elementos=0;
	origen->bytesUtilizados=0;
}

NodoHoja::~NodoHoja() {
	for (unsigned int i=0; i < this->cantidad_elementos;i++) {
		delete[](this->registros[i].dato);
	}
	free(this->registros);
}
