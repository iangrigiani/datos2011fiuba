/*
 * HandlerArchivoEspLibres.h
 *
 *  Created on: 09/04/2011
 *      Author: angeles
 */

#ifndef HANDLERESPLIBRE_H_
#define HANDLERESPLIBRE_H_

#define NOM_ARCH_TEMP "Temp"

#include <string>
#include <fstream>

using namespace std;

class HandlerEspLibre {

private:

	/*
	 * El archivo de espacios libres es una estructura FIFO (cola) que cumple con lo siguiente:
	 * - la insercion de la posicion de un nuevo bloque liberado se realiza antes del
	 * numero -1(dicho numero se encuentra al final del archivo).
	 * - la extraccion de la posicion de un bloque libre se realiza al inicio del archivo.
	 *
	 * El archivo siempre contendra el numero -1 antes de finalizar el archivo, de modo
	 * que un ejemplo de un archivo de espacios libres cumple con la siguiente secuencia:
	 * 3 60 45 50 303 4 -1
	 *
	 * Luego de la insercion de 15:
	 * 3 60 45 50 303 4 15 -1
	 *
	 * Luego de una extraccion:
	 * 60 45 50 303 4 15 -1
	 */
	string ruta_arch_esp_libre;

public:

	HandlerEspLibre() {};

	HandlerEspLibre(const string& ruta_arch_esp_libre);

	virtual ~HandlerEspLibre() {};

	void set_ruta_arch_esp_libre(const string& ruta_arch_esp_libre);

	const string& get_ruta_arch_esp_libre() const { return this->ruta_arch_esp_libre; }

	/*
	* Obtiene el primer elemento del archivo de espacios libres(o bien es el numero -1 o bien
	* es la posicion de un bloque libre).
	* Pre: -
	* Pos: devuelve dicho elemento. El archivo de espacios libres permanece intacto, no se modifica.
	*/
	int get_pos_bloque_libre() const;

	/*
	 * Determina si hay al menos un bloque libre en el archivo de bloques libres.
	 * Pre: -
	 * Pos: devuelve VERDADERO si hay al menos un bloque libre o FALSO si
	 * no hay ningun bloque libre. El archivo de espacios libres permanece intacto.
	 */
	bool hay_bloque_libre() const;

	/*
	 * Determina si la posicion del bloque libre pasada por parametro se encuentra incluida
	 * en el archivo de espacios libres.
	 * Pre: -
	 * Pos: devuelve VERDADERO si la posicion del bloque libre pasada por parametro esta
	 * incluida en el archivo o FALSO si dicha posicion no esta incluida en el archivo.
	 * El archivo de espacios libres permanece intacto.
	 */
	bool ya_existe(int pos_bloque_libre) const;

	/*
	 * Actualiza el archivo de espacios libres en caso de que se haya utilizado un espacio libre
	 * para almacenar un bloque.
	 * Pre: el archivo debe incluir al menos una posicion de un bloque libre, es decir,
	 * el archivo no puede constar unicamente del elemento -1.
	 * Pos: se elimina el primer elemento del archivo que indica la posicion de un bloque
	 * libre.
	 * Ej:
	 * Situación inicial del archivo de espacios libres:
	 * 3 6 9 12 15 -1
	 * Luego de la llamada al metodo(extraccion):
	 * 6 9 12 15 -1
	 */
	void actualizar_baja_bloque_libre();

	/*
	 * Actualiza el archivo de espacios libres en caso de que se haya liberado un bloque.
	 * Pre: -
	 * Pos: se inserta un nueva posicion de un bloque libre al archivo antes del elemento
	 * -1, que se encuentra al final del mismo.
	 * Ej:
	 * Situación inicial del archivo de espacios libres:
	 * 3 6 9 12 15 -1
	 * Luego de la llamada al metodo(insercion de 8):
	 * 3 6 9 12 15 8 -1
	 */
	void actualizar_alta_bloque_libre(int pos_nuevo_bloque_libre);

};

#endif /* HANDLERESPLIBRE_H_ */
