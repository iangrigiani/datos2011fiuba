#ifndef PARSERDELIBROS_H_
#define PARSERDELIBROS_H_

#include "../EstructurasEnComun/Registro.h"
#include <regex.h>
#include <stdlib.h>
#include <string.h>
#include <fstream>
#include <sstream>
#include "../EstructurasEnComun/Constantes.h"
#include <vector>

class ParserDeLibros {
public:
private:
	vector<string> listaStopWords;
	char * libroActual;
	/*
	 * Arma la cadena de match para el autor
	 * pre: -
	 * post: genera la cadena y se fija el match
	 */
	char * obtenerAutor();
	/*
	 * Arma la cadena de match para el titulo
	 * pre: -
	 * post: genera la cadena y se fija el match
	 */
	char * obtenerTitulo();
	/*
	 * Arma la cadena de match para la editorial
	 * pre: -
	 * post: genera la cadena y se fija el match
	 */
	char * obtenerEditorial();
	/*
	 * Arma la cadena de match para las palabras
	 * pre: -
	 * post: genera la cadena y se fija el match
	 */
	char * obtenerPalabras();
	/*
	 * Encuentra el primer match que cumple según las
	 * características de la expresión regular pasada como patrón
	 * pre: pasar patrón de match
	 * post: genera la cadena obtenida
	 */
	char * obtenerPrimerMatch(char * string, char * patronDeFiltro);
	/*
	 * Se fija en la lista de stopWords si la palabra correspondiente
	 * es o no un stopWord
	 * pre: pasar una palabra. Debe existir la lista de stopWords
	 * post: Retorna true, si la palabra se encuentra en la lista.
	 */
	bool esStopWords(char* pch);
	/*
	 * Transforma la palabra a solo minusculas y sin acento
	 * pre: pasar la palabra
	 * post: palabra convertida
	 */
	string caseFolding(char* pch);
	/*
	 * Obtiene desde archivo la lista de stopWords
	 * pre: -
	 * post: lista obtenida
	 */
	void obtenerListaStopWords();

public:
	ParserDeLibros();
	virtual ~ParserDeLibros();
	/*
	 * Metodo que se le pasa el buffer con el libro y devuelve el parseo
	 * en un registro.
	 * pre: pasar el registro
	 * post: parsea y contruye el registro a devolver.
	 */
	Registro * obtenerRegistroDeLibro(char * libro);

	void mostrarLista(){
		vector<string>::iterator it = this->listaStopWords.begin();
		while ( it != this->listaStopWords.end()){
			cout << (*it) << endl;
			++it;
		}
	}
};

#endif /* PARSERDELIBROS_H_ */
