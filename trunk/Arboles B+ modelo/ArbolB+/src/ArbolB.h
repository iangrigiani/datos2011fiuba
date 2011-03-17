/*
 * ArbolB+.h
 *
 *  Created on: 26/03/2010
 *      Author: Grupo Klow
 */

#ifndef ARBOLB_H_
#define ARBOLB_H_

#include <stdio.h>
#include "Nodo.h"
#include "NodoHoja.h"
#include "../../ControladorIDsLibres/src/ControladorIDsLibres.h"

//tamanio de datos para la persistencia del arbol en bytes
#define BLOQUE_ATRIBUTOS_ARBOL 64
//Comentar para desactivar el doble enlace
#define DOBLE_ENLACE

class ArbolB {

	private:

		//Estructura de control para el recorrido secuencial
		typedef struct {
			Nodo::IDNodo sigNodo;
			Nodo::IDNodo antNodo;
			int sigPos;
			int antPos;
		} RecorridoSecuencial;

		ControladorIDsLibres controladorNodosLibres;
		RecorridoSecuencial recorridoSecuencial;
		//Cantidad de elementos que tiene el arbol (hasta 4,294,967,295)
		unsigned int cantidad_elementos;
		//Altura del arbol.
		unsigned short int altura;
		//Manejador del archivo
		FILE * handleFile;
		// Ultimo nodo creado
		Nodo::IDNodo ultimo_nodo_creado;
		// Longitud del bloque con el cual se va a leer y escribir en el archivo
		unsigned int longitudBloque;
		// Bloque que se va a utilizar para leer y escribir en el archivo
		char * bloque;
		// La raiz la dejmos cargada en memoria
		Nodo * raiz;
		//variable para la actualizacion de atributos persistentes
		bool cambios;

		// FUNCIONES PRIVADAS
		void inicializarArbol();

		void Insertar(Nodo * n, Nodo::TClave clave, void * elemento, unsigned short int longitudElemento,
				Nodo::TRetorno * retorno, Nodo::Estado * estado);

		void resolver_overflow(Nodo * nodo,Nodo* sucesor, Nodo::TClave clave, void * elemento, unsigned short int longitudElemento,
										Nodo::TRetorno * retorno, Nodo::Estado * estado);

		void resolver_overflow_raiz(Nodo::TClave clave, void * elemento, Nodo::TLongElem longitudElemento, Nodo::Estado * estado, Nodo::TRetorno * retorno);

		void suprimir(Nodo* nodo, Nodo::TClave clave, Nodo::TRetorno* retorno, Nodo::Estado* estado);

		void resolver_underflow_raiz(Nodo::Estado * estado);
		void resolver_underflow(Nodo* nodo,Nodo* sucesor,int pos_s, Nodo::TRetorno* retorno, Nodo::Estado* estado);

		bool concatenar(Nodo* nodo_ppal,unsigned int pos_suc, Nodo* nodo_suc);
		bool rotar(Nodo* nodo_ppal,unsigned int pos_suc, Nodo* nodo_suc);
		void suprimir_elemento(NodoHoja* nodo,Nodo::TClave clave,Nodo::TRetorno* retorno, Nodo::Estado* estado);

		void Modificar(Nodo * nodo, Nodo::TClave clave, void * elemento, unsigned short int longitudElemento, Nodo::Estado * estado, Nodo::TRetorno * retorno);
		void * Buscar(Nodo * nodo, Nodo::TClave clave, Nodo::TClave * claveDevuelta);


		Nodo * leerNodo(Nodo::IDNodo numeroNodo);
		void grabarNodo(Nodo * nodo, unsigned int pos);

		void incrAltura();
		void decrAltura();
		void incrCantElem();
		void decrCantElem();
		void actualizarCambios();

		Nodo::IDNodo getIDNodoLibre();
		void addIDNodoLibre(Nodo::IDNodo);

		//Inicia el recorrido secuencial a partir de un nodo y una posicion dada
		void iniciarRecorridoSecuencial(NodoHoja * nodo, unsigned short int pos);

		//visualizacion por consola
		void visualizar(Nodo * n, unsigned short int margen, FILE * salida = stdout);

	public:
		enum Resultado {
		  OPERACION_FALLIDA,
		  OPERACION_EXITOSA
		};

		ArbolB(char * nombre,int tamanoBloque);
		~ArbolB();

		Resultado Insertar(Nodo::TClave clave, void * elemento, unsigned short int longitudElemento);

		Resultado suprimir(Nodo::TClave clave);

		Resultado Modificar(Nodo::TClave clave, void * elemento, unsigned short int longitudElemento);

		void * Buscar(Nodo::TClave claveBuscada, Nodo::TClave * claveDevuelta);

		unsigned int getCantidadElementos();
		unsigned int getAltura();

		//Funciones para el recorrido secuencial
		void iniciarRecorridoSecuencial(); // El equivalente a crear un iterador
		bool tieneSiguiente(); // hasNext()
		void * getSiguiente(Nodo::TClave * claveDevuelta); // next();

		#ifdef DOBLE_ENLACE
		bool tieneAnterior(); // hasPrevious();
		void * getAnterior(Nodo::TClave * claveDevuelta); // previous();
		#endif
		//funcion de visualizacion por consola
		//Si fulL es true imprimi los elementos de ls claves
		void visualizar(bool full = false, FILE * salida = stdout);
};

#endif /* ARBOLB_H_ */
