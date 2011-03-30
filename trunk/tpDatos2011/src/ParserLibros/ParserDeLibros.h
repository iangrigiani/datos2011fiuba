#ifndef PARSERDELIBROS_H_
#define PARSERDELIBROS_H_

#include "../EstructurasEnComun/Registro.h"
#include <regex.h>
#include <stdlib.h>
#include <string.h>
#include "../EstructurasEnComun/Constantes.h"

class ParserDeLibros {
public:
private:
	char * libroActual;
	char * getAutor();
	char * getTitulo();
	char * getEditorial();
	char * getPalabras();
	char * getFirstMatch(char * string, char * pattern);

public:
	ParserDeLibros();
	virtual ~ParserDeLibros();
	Registro * obtenerRegistroDeLibro(char * libro);
};

#endif /* PARSERDELIBROS_H_ */
