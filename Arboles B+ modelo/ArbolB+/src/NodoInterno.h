/*
 * NodoInterno.h
 *
 *  Created on: 25/03/2010
 *      Author: Grupo Klow
 */

#ifndef NODOINTERNO_H_
#define NODOINTERNO_H_

#include "Nodo.h"

class NodoInterno: public Nodo {

private:
	IDNodo id;
	//Cantidad de indentificadores que tiene el nodo.
	unsigned int cantidad_elementos;
	unsigned short int cantidad_elementos_max;
	// Claves del index set
	TClave * IDs;
	IDNodo * Sucesores;

	void iniciar(unsigned int bytesCapacidad, Nodo::IDNodo id);
public:

	NodoInterno(unsigned int bytesCapacidad, char * bloque, Nodo::IDNodo id);
	NodoInterno(unsigned int bytesCapacidad, Nodo::IDNodo id);

	void Cargar(char * bloque);
	void Guardar(char * bloque);
	void agregarID(TClave id, IDNodo sucesorIzquierdo, IDNodo sucesorDerecho);

	IDNodo partir(NodoInterno *nodo,TClave clave, IDNodo sucesorIzquierdo, IDNodo sucesorDerecho);
	void concatenar(NodoInterno * nodo);

	IDNodo buscarSucesor(TClave id);
	Nodo::IDNodo buscarPosSucesor(TClave id);

	TipoNodo getTipo();
	unsigned short int getCantidadElementos();
	IDNodo getSucesor(unsigned short int posicion);
	TClave getClave(unsigned short int posicion);
	IDNodo getID();

	void setID(IDNodo);

	void setClave(TClave clave,unsigned short int posicion);
	void setSucesor(Nodo::IDNodo id, unsigned int pos);
	bool isUnderflow();
	bool acepta_clave();
	bool cede_clave();

	void eliminarElemento(unsigned short int pos);
	void eliminarPrimerSeparador();

	unsigned int getPorcentajeOcupacional();

	~NodoInterno();
};

#endif /* NODOINTERNO_H_ */
