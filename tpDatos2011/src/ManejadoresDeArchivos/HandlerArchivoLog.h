
#ifndef HANDLERARCHIVOLOG_H_
#define HANDLERARCHIVOLOG_H_

#include <sstream>
#include <fstream>
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <list>
#include "../EstructurasEnComun/Constantes.h"

using namespace std;

class HandlerArchivoLog {

public:

	HandlerArchivoLog();

	virtual ~HandlerArchivoLog();

	void insertarRegistro(int IDArchivo);

	int  buscarRegistro(int IDArchivo);

	/*
	 *PRE: Recibe:  IDArchivo , parametro ('a'|'e'|'t'|'p')
	 *POST: Guarda en el archivo log la línea con los flags cambiados
	 **/
	void setearIndexado(int IDArchivo, int parametro);

	/*
	 * PRE: Recibe por parámetro listaDeIds donde guarda los IDs de los libros almacenados
	 * POS: Guarda en listaDeIDs los IDs de todos los libros cargados hasta el momento.
	 */
	void obtenerListaIDs(list<int>& listaDeIds);

	/*
	 * PRE: Recibe por parámetro el id de archivo
	 * POS: Devuelve los parametros del archivo de log.
	 */
	bool obtenerIDEstructuras(int IDArchivo, int& a,int& e,int& t,int& p);
	/*
	 * PRE: Recibe parametro para filtrar entre los libros almacenados
	 * POS: Guarda en listaDeIDs (por referencia) los IDs que deben ser indexados
	 */
	void obtenerListaIDsAIndexar(int parametro, list<int>& listaDeIds);


private:

	string crearStringAInsertar(int numero, int ind1, int ind2, int ind3, int ind4);

};

#endif /* HANDLERARCHIVOLOG_H_ */
