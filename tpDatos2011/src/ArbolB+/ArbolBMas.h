
#ifndef _ARBOLBMAS_H_
#define _ARBOLBMAS_H_

#include "../EstructurasEnComun/Clave.h"
#include "../EstructurasEnComun/Registro.h"
#include "../ModuloDePersistencia/Persistencia.h"
#include "NodoInterior.h"
#include "NodoHoja.h"
#include "IteradorArbol.h"
#include "Resultado.h"
#include "../EstructurasEnComun/Constantes.h"
#include "../ModuloDePersistencia/EscritorNodosLibres.h"
#include "../ModuloDePersistencia/EscritorNodo.h"
#include "../ModuloDePersistencia/RecuperadorNodos.h"
#include "../ModuloDePersistencia/RecuperadorNodosLibres.h"

#include <fstream>
#include <vector>
#include <stdio.h>
#include <string>
using namespace std;



class ArbolBMas {

	friend class Nodo;
	friend class NodoInterior;
	friend class NodoHoja;

private:
	Nodo* raiz;
	string path;
	/*
	 * Si es un 1 guarda Autores,
	 * si es un 2 guarda editoriales
	 */

	int tipo;
	int primeraHoja;
	RecuperadorNodos* recuperador_Nodos;
	EscritorNodo* escritor_Nodos;
	RecuperadorNodosLibres* recuperador_Datos_Configuracion;
	EscritorNodosLibres* escritor_Datos_Configuracion;
	int cantidadNodos;
	vector<int> nodosLibres;
//	Persistor* persistor;

public:

	/*
	 * Constructor
	 * Recibe ruta del archivo donde voy a guardar el arbol y el tamanio
	 * maximo de clave que puede almacenar y el tipo de arbol.
	 */
	ArbolBMas(int tipo, std::string ruta_archivo);
	~ArbolBMas();

	/*
	 * Insertar un registro al arbol
	 * Pos: Devuelve TRUE si se inserto correctamente y FALSE en caso contrario.
	 */
	bool insertar(Elementos* elemento);

	/*
	 * Devuelve un IteradorArbol al primer nodo hoja del arbol.
	 * Pos: Devuelve el iterador en caso de que exista algun registro en el arbol.
	 */
	IteradorArbol* obtenerIterador();


	/*
	 * Buscar una clave en el archivo
	 * Pre: Recibo la clave del elemento a buscar.
	 * Pos: Si lo encontro, devuelve el elemento, sino, devuelve NULL.
	 */
	list<Elementos*> buscar(Clave clave);

	/*
	 * Metodo recursivo que se encarga de borrar un elemento del arbol, y realizar los balanceos o fusiones correspondientes.
	 * clave es la clave del elemento a borrar.
	 * nodoCorriente es el nodo que se esta procesado.
	 * nodoIzquierda y nodoDerecha son los nodos que se encuentran al los lados del corriente, NULL en caso de no existir ninguno.
	 * nodoPadreIzquierda y nodoPadreDerecha representan al nodoPadre en la mayoria de los casos, y en los casos en que el nodo en cuestion
	 * se encuentra en alguno de los extremos, representan al padre del padre, segun se encuentre en el extremo izquierdo o derecho.
	 * nodoPadre representa al padre del corriente y posicionPadre la ubicacion del nodoCorriente en el padre.
	 * Puede devolver OK, NO_ENCONTRADO, ACTUALIZAR_ULTIMA_CLAVE o FUSION_NODOS segun sea el caso.
	 */
	Resultado borrarRecursivo(Clave clave, Nodo *nodoCorriente, Nodo *nodoIzquierda, Nodo *nodoDerecha,
			NodoInterior *nodoPadreIzquierda, NodoInterior *nodoPadreDerecha, NodoInterior *nodoPadre, int posicionPadre);


	/*
	 * Se encarga de fusionar dos nodos hoja.
	 * hojaIzquierda y hojaDerecha son los nodos en cuestion. En hoja izquierda se pasan todos los elementos de hojaDerecha.
	 * Devuelve Resultado::FUSION_NODOS.
	 */
	Resultado fusionarHojas(NodoHoja* hojaIzquierda, NodoHoja* hojaDerecha);


	/*
	 * Se encarga de fusionar dos nodos interiores.
	 * nodoIzquierda y nodoDerecha son los nodos en cuestion. En nodoIzquierda se pasan todos los elementos de nodoDerecha.
	 * Si se produce la fusion devuelve Resultado::FUSION_NODOS, sino Resultado::OK
	 */
	Resultado fusionarNodosInteriores(NodoInterior* nodoIzquierda, NodoInterior* nodoDerecha, NodoInterior* nodoPadre, int posicionPadre);


	/*
	 * Se encarga de balancear un nodo interior derecho, con su izquierdo, pasando elementos a este ultimo.
	 * nodoIzquierda y nodoDerecha son los nodos en cuestion, nodoPadre es el padre de ambos y posicionPadre es la ubicacion en el
	 * padre, del nodo actual.
	 */
	void pasarElementosNodoInteriorIzquierdo(NodoInterior *nodoIzquierda, NodoInterior *nodoDerecha, NodoInterior *nodoPadre, int posicionPadre);


	/*
	 * Se encarga de balancear un nodo interior izquierdo, con su derecho, pasando elementos a este ultimo.
	 * nodoIzquierda y nodoDerecha son los nodos en cuestion, nodoPadre es el padre de ambos y posicionPadre es la ubicacion en el
	 * padre, del nodo actual.
	 */
	void pasarElementosNodoInteriorDerecho(NodoInterior *nodoIzquierda, NodoInterior *nodoDerecha, NodoInterior *nodoPadre, int posicionPadre);


	/*
	 * Se encarga de balancear un nodo hoja derecho, con su izquierdo, pasando elementos a este ultimo.
	 * hojaIzquierda y hojaDerecha son los nodos en cuestion, nodoPadre es el padre de ambos y posicionPadre es la ubicacion en el
	 * padre, del nodo que contiene al elemento a ser borrado.
	 * Si cambia la ultima clave del padre (lo que implicaria cambiar la clave tambien en el padre del padre) se devuelve
	 * Resultado::ACTUALIZAR_ULTIMA_CLAVE, caso contrario se devuelve Resultado::OK
	 */
	Resultado pasarElementosHojaIzquierda(NodoHoja *hojaIzquierda, NodoHoja *hojaDerecha, NodoInterior *nodoPadre, int posicionPadre);


	/*
	 * Se encarga de balancear un nodo hoja izquierdo, con su derecho, pasando elementos a este ultimo.
	 * hojaIzquierda y hojaDerecha son los nodos en cuestion, nodoPadre es el padre de ambos y posicionPadre es la ubicacion en el
	 * padre, del nodo que contiene al elemento a ser borrado.
	 */
	void pasarElementosHojaDerecha(NodoHoja *hojaIzquierda, NodoHoja *hojaDerecha, NodoInterior *nodoPadre, int posicionPadre);



	/*
	 * Modifico un registro
	 * Pos: Devuelve TRUE si se modifico correctamente y FALSE en caso de que no exista
	 * 	el mismo.
	 */
	bool modificar(Registro* registro);

	/*
	 * Primitiva que elimina un registro de la estructura.
	 * Pos: Devuelve TRUE si se pudo borrar correctamente y FALSE en caso contrario.
	 */
	bool borrar(Clave clave);

	/*
	 * Devuelve el nodo con n�mero "numeroDeNodo".
	 * Pos: Devuelve un puntero al Nodo buscado. Si el numero de nodo es invalido
	 * 		devuelve NULL.
	 */
	Nodo* leerNodo(int numeroDeNodo);

	void MostrarArbol(Nodo* nodo);

	void MostrarArbol ();

	int getCantidadBloques();

	int getTipo(){
		return this->tipo;
	}
private:
	void grabarDatosConfiguracion();
	void refactorizarNodoFrontCoding(NodoHoja** nodoHojaCorriente);
	void refactorizarNodoNoHojaFrontCoding(Nodo** nodo);
	NodoHoja* obtenerNodoHoja();
	NodoInterior* obtenerNodoInterior(int nivel);
	int obtenerNumeroNodo();
	bool insertarRecursivamente(Nodo* nodoCorriente, Clave& claveNum, Elementos* dato, Clave* clavePromocion, Nodo** nuevoNodo);
	void persistirNodo(Nodo* nodo);
	void toString(Nodo* nodo, int tab, ofstream& fo);
	void liberarMemoriaNodo(Nodo* nodo);
	int obtenerPosicion(Nodo *unNodo, Clave clave);
	Nodo* hidratarNodo(int nroNodo);
	void sacarFrontCodingNodo (Nodo ** nodo);
	void sacarFrontCodingNodoHoja (NodoHoja ** nodo);
	void dividirNodoInterior(NodoInterior* unNodoInterior, Clave* clavePromocion, Nodo** nuevoNodoInterior, int nuevaPosicion);
	void dividirNodoHoja(NodoHoja* unNodoHoja, Clave* clavePromocion, Nodo** nuevoNodoHoja);
	void hidratarDatosConfiguracion();
	void inicializarPersistores();
};

#endif // _ARBOLBMAS_H_
