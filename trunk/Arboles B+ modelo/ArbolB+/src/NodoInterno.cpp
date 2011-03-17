/*
 * NodoInterno.cpp
 *
 *  Created on: 25/03/2010
 *      Author: Grupo Klow
 */

#include "NodoInterno.h"
#include "Nodo.h"
#include <string.h>
#include <iostream>


NodoInterno::NodoInterno(unsigned int bytesCapacidad, char * bloque, Nodo::IDNodo id){
	this->iniciar(bytesCapacidad,id);
	this->Cargar(bloque);

}

NodoInterno::NodoInterno(unsigned int bytesCapacidad, Nodo::IDNodo id){
	this->iniciar(bytesCapacidad,id);
}

void NodoInterno::iniciar(unsigned int bytesCapacidad, Nodo::IDNodo id) {
	this->cantidad_elementos_max = (bytesCapacidad - sizeof(unsigned int) - sizeof(Nodo::IDNodo) - 1 )/ (sizeof(Nodo::TClave)+sizeof(Nodo::IDNodo));
	this->IDs = new unsigned int [this->cantidad_elementos_max];
	this->Sucesores = new unsigned int [this->cantidad_elementos_max+1];

	unsigned int i;

	for (i=0; i < this->cantidad_elementos_max; i++) {
		this->IDs[i]=0;
		this->Sucesores[i]=0;
	}
	this->Sucesores[i]=0;

	this->cantidad_elementos = 0;
	this->id = id;
}

// Informacion de bloque de archivo a Nodo
void NodoInterno::Cargar(char * bloque) {

	unsigned int longitud;
	unsigned int actual=0;

	// Recupero
	actual = 1;
	longitud = sizeof(unsigned int);
	memcpy(&this->cantidad_elementos,&bloque[actual], longitud);

	// Incializo los arrays
	//this->IDs = new unsigned int [this->cantidad_elementos_max];
	//this->Sucesores = new unsigned int [this->cantidad_elementos_max+1];

	// Cargo los IDS que tiene el nodo
	actual+=longitud;
	longitud = sizeof(TClave) * cantidad_elementos_max;
	memcpy(this->IDs,&bloque[actual],longitud);

	// Cargo los sucesores
	actual+=longitud;
	longitud = sizeof(IDNodo) * (cantidad_elementos_max+1);
	memcpy(this->Sucesores, &bloque[actual], longitud);
}
// Informacion de Nodo a bloque para escribir en archivo
void NodoInterno::Guardar(char * bloque) {
	unsigned int longitud;
	unsigned int actual=0;

	actual= 1;

	// Copio el tipo de nodo
	bloque[0]= NODO_INTERNO;

	// Copio la cantidad de elementos que tiene
	longitud = sizeof(unsigned int);
	actual = 1;
	memcpy(&bloque[actual],&this->cantidad_elementos,longitud);

	actual+=longitud;
	// Copio los ids
	longitud = sizeof(TClave) * cantidad_elementos_max;
	memcpy(&bloque[actual],this->IDs,longitud);

	actual+=longitud;
	// Copio los sucesores
	longitud = sizeof(IDNodo) * (cantidad_elementos_max+1);
	memcpy(&bloque[actual],this->Sucesores,longitud);
}

void NodoInterno::agregarID(TClave id, IDNodo sucesorIzquierdo, IDNodo sucesorDerecho) {
	int pos = this->cantidad_elementos-1;

	while (pos >= 0 && this->IDs[pos] > id) {
		this->IDs[pos+1] = this->IDs[pos];
		this->Sucesores[pos+2]=this->Sucesores[pos+1];
		pos--;
	}
	this->IDs[pos+1]= id;
	this->Sucesores[pos+1] = sucesorIzquierdo;
	this->Sucesores[pos+2] = sucesorDerecho;

	this->cantidad_elementos++;
}
/* Parte el nodo a la mitad sin tener en cuenta al centro y devuelve a este.
 * La parte izquierda queda en el nodo desde el cual se ejecuto el evento
 * y la parte derecha en el nodo lamado nodo */
Nodo::IDNodo NodoInterno::partir(NodoInterno * nodo, TClave clave, IDNodo sucesorIzquierdo, IDNodo sucesorDerecho) {
	unsigned int medio = (this->cantidad_elementos - 1) / 2;
	unsigned int cantidad_a_Pasar;
	IDNodo sucesorIzquierdo2;

	unsigned short int agregar = 1;
	bool izquierda = true;

	IDNodo centro;


	if (this->IDs[medio] < clave && this->IDs[medio+1] > clave) {
		centro = clave;
		agregar =0;
		sucesorIzquierdo2 = sucesorDerecho;
	} else if (this->IDs[medio]< clave) {
		centro = this->IDs[++medio];
		izquierda=false;
		sucesorIzquierdo2 = this->Sucesores[medio+1];
	} else {
		centro= this->IDs[medio];
		sucesorIzquierdo2 = this->Sucesores[medio+1];
	}

	cantidad_a_Pasar = this->cantidad_elementos - medio - 1;
	this->cantidad_elementos=  this->cantidad_elementos - cantidad_a_Pasar - agregar;
	nodo->cantidad_elementos =  cantidad_a_Pasar;

	//Paso los elementos a la otra mitad
	while (cantidad_a_Pasar > 0) {
		cantidad_a_Pasar--;
		nodo->IDs[cantidad_a_Pasar]= this->IDs[medio + cantidad_a_Pasar+1];
		nodo->Sucesores[cantidad_a_Pasar] = this->Sucesores[medio + cantidad_a_Pasar+1];
		nodo->Sucesores[cantidad_a_Pasar+1] = this->Sucesores[medio + cantidad_a_Pasar+2];
	}
		nodo->Sucesores[0] = sucesorIzquierdo2;
	//Chequeo si el elemento (clave, elemento) se debe agregar a alguna de las dos partes
	// Si es justo el centro, no se agrega.
	if (agregar) {
		if (izquierda) {
			this->agregarID(clave,sucesorIzquierdo,sucesorDerecho);
		} else {
			nodo->agregarID(clave,sucesorIzquierdo,sucesorDerecho);
		}
	}
	//Devuelvo el centro, que no fue puesto en ninguna de las dos partes
	return centro;
}

Nodo::IDNodo NodoInterno::buscarSucesor(TClave id) {
	unsigned int pos=0;
	while (pos < this->cantidad_elementos && this->IDs[pos] <= id) {
			pos++;
	}
	return this->Sucesores[pos];
}

Nodo::IDNodo NodoInterno::buscarPosSucesor(TClave id) {

	unsigned int pos=0;
	while (pos < this->cantidad_elementos && this->IDs[pos] <= id) {
			pos++;
	}
	return pos;
}

Nodo::TipoNodo NodoInterno::getTipo() {
	return Nodo::NODO_INTERNO;
}

Nodo::IDNodo NodoInterno::getID() {
	return this->id;
}

unsigned short int NodoInterno::getCantidadElementos() {
	return this->cantidad_elementos;
}

Nodo::TClave NodoInterno::getClave(unsigned short int posicion ){
	return this->IDs[posicion];
}

Nodo::IDNodo NodoInterno::getSucesor(unsigned short int posicion) {
	if(posicion >= 0)
		return this->Sucesores[posicion];
	else
		return 0;
}

unsigned int NodoInterno::getPorcentajeOcupacional() {
	return (this->cantidad_elementos *100 / this->cantidad_elementos_max);
}

bool NodoInterno::isUnderflow(){

	unsigned int cota = this->cantidad_elementos_max / 2;
	return (this->cantidad_elementos < cota);
}

bool NodoInterno::acepta_clave(){

	return ((this->cantidad_elementos + 1) <= this->cantidad_elementos_max);
}

bool NodoInterno::cede_clave(){

 unsigned int cota = this->cantidad_elementos_max / 2;

 return ((this->cantidad_elementos - 1) >= cota );
}

void NodoInterno::concatenar(NodoInterno * origen) {
	unsigned int cantidad_a_Pasar;
	unsigned int offset;


	cantidad_a_Pasar = origen->cantidad_elementos;
	offset = this->cantidad_elementos;

	//agrego los elementos del nodo sucesor al nodo_0
	while (cantidad_a_Pasar > 0) {
		this->Sucesores[offset + cantidad_a_Pasar] = origen->Sucesores[cantidad_a_Pasar];
		cantidad_a_Pasar--;
		this->IDs[offset + cantidad_a_Pasar]= origen->IDs[cantidad_a_Pasar];

	}
	this->Sucesores[offset] = origen->Sucesores[0];

	this->cantidad_elementos+= origen->cantidad_elementos;
	origen->cantidad_elementos = 0;
}

void NodoInterno::eliminarPrimerSeparador() {
	//muevo los datos
	unsigned int pos = 0;

	//decremento la cant de elementos
	this->cantidad_elementos--;

	//Corro los elementos una posicion
	while(pos < this->cantidad_elementos){
		this->Sucesores[pos] = this->Sucesores[pos+1];
		this->IDs[pos] = this->IDs[pos+1];
		pos++;
	}
	this->Sucesores[pos] = this->Sucesores[pos+1];

}

void NodoInterno::eliminarElemento(unsigned short int pos){

	//muevo los datos
	while(pos < this->getCantidadElementos()-1){

		this->IDs[pos] = this->IDs[pos+1];
		this->Sucesores[pos+1] = this->Sucesores[pos+2];
		pos++;
	}
	//muevo la ultima posicion de sucesores
	//this->Sucesores[pos] = this->Sucesores[pos+1];

	//decremento la cant de elementos
	cantidad_elementos--;
}

void NodoInterno::setClave(Nodo::TClave clave,unsigned short int posicion){

	this->IDs[posicion] = clave;
}

void NodoInterno::setSucesor(Nodo::IDNodo id, unsigned int pos){

	this->Sucesores[pos] = id;
}

void NodoInterno::setID(Nodo::IDNodo id) {
	this->id = id;
}

NodoInterno::~NodoInterno() {
	delete[](this->IDs);
	delete[](this->Sucesores);
}

