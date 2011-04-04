#ifndef HandlerArchivoRLV_H_
#define HandlerArchivoRLV_H_

#include <sstream>
#include <fstream>
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../EstructurasEnComun/Constantes.h"

using namespace std;

class HandlerArchivoRLV{

private:
		int ultimoID;
		int ultimoOffset;
		/*
		 * Retorna el tamanio del libro
		 * Pre: Se le pasa en un char* la cabecera del Libro separada por pipes
		 * Post: Retorna el tamanio (segundo parámetro)
		 */
		int obtenerTamanioLibro(char * cadenaDeDatos);
		/*
		 * Setea en el atributo UltimoId y UltimoOffset, obteniendo los datos del
		 * archivo de datos para control del archivo de RLV
		 * Pre: Debe existir el archivo
		 * Post: Se actualizan el ultimoID y Offset del objeto
		 */
		void recuperarDatosAnteriores();
		/*
		 * Graba los atributos UltimoId y UltimoOffset, en el archivo de datos del
		 * archivo para control del archivo de RLV
		 * Pre: -
		 * Post: Se actualizan el ultimoID y Offset del archivo de control
		 */
		void grabarDatosActuales();
		/*
		 * Obtiene el tamanio actual del archivo de registros de longitud
		 * variable.
		 * Pre: -
		 * Post: Retorna el tamanio del archivo.
		 */
		int obtenerTamanioMaestro();
public:

		HandlerArchivoRLV();
		virtual ~HandlerArchivoRLV() {};
		/*
		 * Método que inserta un registro (libro ) en el
		 * archivo de registros de longitud variable.
		 * Pre: ingresar path del registro a insertar
		 * Post: devuelve el offset donde inserto el registro
		 */
		int insertarRegistro(const string& path_nuevo_libro);
		/*
		 * Método que busca un registro (libro ) en el
		 * archivo de registros d elongitud variable
		 * Pre: Pasa el offset donde está el registro en el archivo
		 * Post: Devuelve en una variable char* el libro completo sin la cabecera
		 */
		char* buscarRegistro(int offset);
		/*
		 * Método que elimina un registro (libro ) del
		 * archivo de registros d elongitud variable
		 * Pre: Pasa el offset donde está el registro en el archivo
		 * Post: Queda un espacio del tamanio del registro en blanco en el archivo.
		 */
		void quitarRegistro(int offset);
};

#endif /* HANDLERARCHIVORLV_H_ */
