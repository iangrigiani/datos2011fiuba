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
		/*
		 * Metodo que verifica si el registro a insertar entra o no en alguno
		 * de los espacios libres del archivo de espacios libres y offsets
		 * Pre: Pasarle el tamanio del registro a insertar
		 * Post: Retorna ERROR en caso de que no se encuentro un lugar o
		 * 		 retorna el offset en donde se va a insertar el registro.
		 */
		int buscarOffsetArchivoEspaciosLibres(int tamanioRegistro);

		/*
		 * Retorna el tamanio del libro
		 * Pre: Se le pasa en un char* la cabecera del Libro separada por pipes
		 * Post: Retorna el tamanio (segundo par�metro)
		 */
		int obtenerTamanioLibro(char * cadenaDeDatos);
		/*
		 * Obtiene el tamanio actual del archivo de registros de longitud
		 * variable.
		 * Pre: -
		 * Post: Retorna el tamanio del archivo.
		 */
		int obtenerTamanioMaestro();
		/*
		 * Metodo que agrega en el archivo de espacio libre
		 * la cantidad de espacio libre para el offset correspondiente
		 * Pre: -
		 * Post: Datos almacenados.
		 */
		void actualizarEspaciosLibres(int offset, int tamanioLibre);
		/*
		 * Metodo que borra el offset y espacio libre que acabo de completar.
		 * Pre: offsetLineaABorrar es el offset en el Archivo de Espacio Libre
		 *      de la linea a borrar
		 * Post: Borra del archivo de espacios libres los datos del registro
		 * 		 del archivo de RLV que acaba de completar
		 */
		void borrarOffsetArchivoDeEspaciosLibres(int offsetLineaABorrar);
public:

		HandlerArchivoRLV();
		virtual ~HandlerArchivoRLV() {};
		/*
		 * M�todo que inserta un registro (libro ) en el
		 * archivo de registros de longitud variable.
		 * Pre: ingresar path del registro a insertar
		 * Post: devuelve el offset donde inserto el registro
		 */
		int insertarRegistro(const string& path_nuevo_libro);
		/*
		 * M�todo que busca un registro (libro ) en el
		 * archivo de registros d elongitud variable
		 * Pre: Pasa el offset donde est� el registro en el archivo
		 * Post: Devuelve en una variable char* el libro completo sin la cabecera
		 */
		char* buscarRegistro(int offset);
		/*
		 * M�todo que elimina un registro (libro ) del
		 * archivo de registros d elongitud variable
		 * Pre: Pasa el offset donde est� el registro en el archivo
		 * Post: Queda un espacio del tamanio del registro en blanco en el archivo.
		 */
		void quitarRegistro(int offset);
};

#endif /* HANDLERARCHIVORLV_H_ */
