#ifndef HANDLERARBOL_H_
#define HANDLERARBOL_H_
#include "../ArbolB+/ArbolBMas.h"
#include "../Hash/Hash.h"
#include "../ParserLibros/ParserDeLibros.h"
#include "../ManejadoresDeArchivos/HandlerArchivoRLV.h"
#include "../ManejadoresDeArchivos/HandlerArchivoLog.h"


class HandlerComandos {

private:
	ParserDeLibros* parser;
	HandlerArchivoRLV* handler;
	HandlerArchivoLog* log;
/*	ArbolBMas* arbol_autores;
	ArbolBMas* arbol_editoriales;
	Hash* hash_titulos;
	Hash* hash_palabras;*/

public:

	HandlerComandos();

	/*
	 * Toma un path donde se encuentra el libro original guardado, procesa el libro
	 * y lo agrega al Archivo Maestro de libros.
	 * Además, agrega una línea al Archivo de Log con los Flags de indexado en 0
	 * */
	void guardarLibroEnArchivoMaestro(const string& path_nuevo_libro);

	/*
	 * PRE: int parametro ('a'|'e'|'t'|'p')
	 * POS: Agrega segun parametro en el indice correspondiente todos los libros agregados recientemente al Archivo Maestro
	 *
	 * */
	void indexar(int parametro);

	/*
	 * Muestra el log de todos los archivos ingresados recientemente
	 * */
	void listarLibrosIngresados();

	/*
	 * Busca y muestra un libro por ID
	 */
	void obtenerLibro(int IDArchivo);

	/*
	 * Busca un libro por ID y lo elimina del registro maestro y de los 4 índices
	 */
	void quitarLibro(int IDArchivo);

	/*
	 * PRE: int parametro ('a'|'e'|'t'|'p')
	 * POS: Muestra la estructura del indice correspondiente segun el parametro recibido
	 * como texto plano
	 * */
	void verEstructura(int parametro);


	virtual ~HandlerComandos();


	/*
	void insertar(string path, ArbolBMas &arbol, Hash& hash);
	void borrarEnArbol(Clave* clave, ArbolBMas &arbol);
	void buscarEnArbol(Clave* clave, ArbolBMas &arbol);
	void borrarEnHash(Clave* clave, Hash &hash);
	void buscarEnHash(Clave* clave, Hash &hash);*/
};

#endif /* HANDLERARBOL_H_ */
