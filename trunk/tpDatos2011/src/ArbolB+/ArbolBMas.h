
#ifndef _ARBOLBMAS_H_
#define _ARBOLBMAS_H_

#include "../EstructurasEnComun/ClaveNumerica.h"
#include "../EstructurasEnComun/Registro.h"
#include "../ModuloDePersistencia/Persistencia.h"
#include "NodoInterior.h"
#include "NodoHoja.h"
#include "IteradorArbol.h"
//#include "Resultado.h"
#include "../EstructurasEnComun/Constantes.h"
//#include "ComparadorClavesContexto.h"

#include <fstream>
#include <vector>

using namespace std;


class ArbolBMas {

	friend class Nodo;
	friend class NodoInterior;
	friend class NodoHoja;

private:
	Nodo* raiz;
	int primeraHoja;
	int cantidadNodos;
	int maxTamanioClave;
	vector<int> nodosLibres;
//	Persistor* persistor;

public:

	/*
	 * Constructor
	 * Recibe ruta del archivo donde voy a guardar el arbol y el tamanio
	 * maximo de clave que puede almacenar.
	 */
	ArbolBMas(string ruta_archivo, int tamanioMaximoClave);
	~ArbolBMas();

	/*
	 * Insertar un registro al arbol
	 * Pos: Devuelve TRUE si se inserto correctamente y FALSE en caso contrario.
	 */
	bool insertar(Registro* registro);

	/*
	 * Devuelve un IteradorArbol al primer nodo hoja del arbol.
	 * Pos: Devuelve el iterador en caso de que exista algun registro en el arbol.
	 */
	IteradorArbol* obtenerIterador();

	/*
	 * Buscar una clave en el archivo
	 * Pre: Recibo la clave del registro a buscar.
	 * Pos: Si lo encontro, devuelve el registro, sino, devuelve NULL.
	 */
	pair<Registro*, IteradorArbol*> buscar(ClaveNumerica clave);

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
	bool borrar(ClaveNumerica clave);

	/*
	 * Devuelve el nodo con número "numeroDeNodo".
	 * Pos: Devuelve un puntero al Nodo buscado. Si el numero de nodo es invalido
	 * 		devuelve NULL.
	 */
	Nodo* leerNodo(int numeroDeNodo);

	int getCantidadBloques();


};

#endif // _ARBOLBMAS_H_
