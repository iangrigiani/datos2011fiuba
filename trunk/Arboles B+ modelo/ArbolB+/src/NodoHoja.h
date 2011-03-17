/*
 * NodoHoja.h
 *
 *  Created on: 26/03/2010
 *      Author: Grupo Klow
 */

#ifndef NODOHOJA_H_
#define NODOHOJA_H_

#include "Nodo.h"

//Porcentaje del nodo maximo que puede ocupar un elemento
#define PORCENTAJE_MAX_ELEM 20

class NodoHoja: public Nodo {

private:

	//Un nodo contiene registros
	typedef struct {
		TClave ID;
		TLongElem longitudDato;
		char * dato;
	} TRegistro;

	TRegistro * registros;

	unsigned int bytesUtilizados;
	unsigned int bytesCapacidad;

	IDNodo ID;
	//Cantidad de indentificadores que tiene el nodo
	unsigned int cantidad_elementos;
	// Relacion secuencial
	IDNodo sucesorIzquierdo;
	IDNodo sucesorDerecho;

	void iniciar(unsigned int bytesCapacidad, IDNodo id);

public:
	NodoHoja(unsigned int bytesCapacidad, char * bloque, Nodo::IDNodo id);
	NodoHoja(unsigned int bytesCapacidad, Nodo::IDNodo id);

	void Cargar(char * bloque);
	void Guardar(char * bloque);

	unsigned short int agregarElemento(TClave clave, void * elemento, unsigned int longitudElemento);

	void partir(NodoHoja * nodo,TClave medio, TClave clave, void * elemento, unsigned int longitudElemento);

	void concatenar(NodoHoja * nodo);

	IDNodo buscarMedio(TClave clave,TLongElem longitudElemento);
	unsigned short int BuscarExacto(TClave clave);
	unsigned short int Buscar(TClave clave, bool busquedaExacta = false);

	void cambiarElemento(unsigned short int pos, void * elemento, unsigned int longitudElemento, Nodo::Estado * estado, Nodo::TRetorno * retorno);

	void setSucesorDerecho(IDNodo idNodo);
	void setSucesorIzquierdo(IDNodo idNodo);

	TipoNodo getTipo();
	unsigned short int getCantidadElementos();
	TClave getClave(unsigned short int posicion);
	void * getElemento(unsigned short int pos);
	unsigned int getLongitudElem(unsigned short int pos);
	IDNodo getSucesorDerecho();
	IDNodo getSucesorIzquierdo();
	IDNodo getID();

	void setID(IDNodo id);

	void eliminarElemento(unsigned short int pos);

	bool isOverflow(unsigned int longitudNuevoElemento);
	bool isUnderflow();
	bool cede_primero();
	bool cede_ultimo();

	unsigned int getPorcentajeOcupacional();

	//Destructor
	~NodoHoja();
};

#endif /* NODOHOJA_H_ */
