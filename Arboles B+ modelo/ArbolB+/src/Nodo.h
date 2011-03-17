/*
 * Nodo.h
 *
 *  Created on: 25/03/2010
 *      Author: Grupo Klow
 */

#ifndef NODO_H_
#define NODO_H_


class Nodo {

public:
	enum Estado {
	  SIN_NOVEDAD,

	  MODIFICADO,

	  OVERFLOW_HOJA, // Se produjo un overflow en un nodo hoja
	  OVERFLOW_INTERNO, // Se produjo un overflow en un nodo interno

	  UNDERFLOW_HOJA,
	  UNDEFLOW_INTERNO,

	  ERROR // Ejemplo, no hay memoria para un nuevo bloque.
	} ;

	enum TipoNodo {
		NODO_HOJA,
		NODO_INTERNO
	};

	typedef unsigned int IDNodo;
	typedef unsigned int TClave;
	typedef unsigned int TLongElem;

	typedef struct {
		TClave separador;
		IDNodo apuntadorDerecho;
	} TRetorno;

	virtual void Cargar(char * bloque) = 0;
	virtual void Guardar(char * bloque) = 0;
	virtual TipoNodo getTipo() = 0;
	virtual unsigned short int getCantidadElementos() = 0;
	virtual IDNodo getID()=0;
	virtual void setID(IDNodo id)=0;
	virtual TClave getClave(unsigned short int posicion) = 0;
	virtual bool isUnderflow()=0;

	virtual void eliminarElemento(unsigned short int pos) = 0;

	virtual unsigned int getPorcentajeOcupacional() = 0;
	virtual ~Nodo(){};
};

#endif /* NODO_H_ */
