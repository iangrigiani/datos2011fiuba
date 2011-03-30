#ifndef ACTUALIZADORARCHIVOREGLONGVARIABLE_H_
#define ACTUALIZADORARCHIVOREGLONGVARIABLE_H_
#include <string>
#include <iostream>
#include <list>
#include <stdlib.h>
#include <fstream>
#include "../EstructurasEnComun/Constantes.h"
using namespace std;
class ActualizadorArchivoRegLongVariable {
private:
	string pathLibro;
public:
	ActualizadorArchivoRegLongVariable();
	ActualizadorArchivoRegLongVariable(string pathLibro);
	/*
	 * Este metodo es el que debo llamar desde afuera una vez que le pase el path o se lo setee
	 * para que en el libro que encuentra en ese path, lo grabe en el archivo de registros
	 * de longitud Variable
	 * pre: debe existir un path
	 * post: Graba en el archivo un nuevo libro y genera un ID de libro, estado (procesado = 1
	 * indexado = 2), tamanio y offset. Retorna -1 en caso de Error.
	 */
	int actualizarLibro();
	virtual ~ActualizadorArchivoRegLongVariable();
};

#endif /* ACTUALIZADORARCHIVOREGLONGVARIABLE_H_ */
