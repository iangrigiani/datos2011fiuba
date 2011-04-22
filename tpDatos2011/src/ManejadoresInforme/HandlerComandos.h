#ifndef HANDLERARBOL_H_
#define HANDLERARBOL_H_
#include "../ArbolB+/ArbolBMas.h"
#include "../Hash/Hash.h"
#include "../ParserLibros/ParserDeLibros.h"
#include "../ManejadoresDeArchivos/HandlerArchivoRLV.h"


class HandlerComandos {

private:
	ParserDeLibros* parser;
	HandlerArchivoRLV* handlerArchivoRLV;
public:

	HandlerComandos();

	/*
	 * Toma un path donde se encuentra el libro original guardado y lo agrega al Archivo Maestro de libros
	 * */
	void guardarLibroEnArchivoMaestro();

	/*
	 * Agrega en el árbol de editoriales todos los libros agregados recientemente al Archivo Maestro
	 * */
	void indexarporEditoriales();

	/*
	 * Agrega en el árbol de autores todos los libros agregados recientemente al Archivo Maestro
	 * */
	void indexarPorAutores();

	/*
	 * Agrega en el hash de títulos todos los libros agregados recientemente al Archivo Maestro
	 * */
	void indexarPorTitulos();

	/*
	 * Agrega en el hash de palabras todos los libros agregados recientemente al Archivo Maestro
	 * */
	void indexarPorPalabras();

	/*
	 * Muestra el log de todos los archivos ingresados recientemente
	 * */
	void listarLibrosIngresados();

	/*
	 * Busca y muestra un libro por ID
	 */
	void obtenerLibro();

	/*
	 * Busca un libro por ID y lo elimina del registro maestro y de los 4 índices
	 */
	void quitarLibro();

	/*
	 * Muestra la estructura del árbol de editoriales como texto plano
	 * */
	void verArbolEditorial();

	/*
	 * Muestra la estructura del árbol de autores como texto plano
	 * */
	void verArbolAutor();

	/*
	 * Muestra la estructura del hash de títulos como texto plano
	 * */
	void verHashTitulo();

	/*
	 * Muestra la estructura del hash de palabras como texto plano
	 * */
	void verHashPalabras();

	virtual ~HandlerComandos();


	/*
	void insertar(string path, ArbolBMas &arbol, Hash& hash);
	void borrarEnArbol(Clave* clave, ArbolBMas &arbol);
	void buscarEnArbol(Clave* clave, ArbolBMas &arbol);
	void borrarEnHash(Clave* clave, Hash &hash);
	void buscarEnHash(Clave* clave, Hash &hash);*/
};

#endif /* HANDLERARBOL_H_ */
