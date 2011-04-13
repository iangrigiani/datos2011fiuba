#ifndef HANDLERARCHIVOBLOQUES_H_
#define HANDLERARCHIVOBLOQUES_H_

#define TAM_BUFFER 4096

#include "../EstructurasEnComun/Bloque.h"
#include "HandlerEspLibre.h"

class HandlerBloquesOtraVersion {

private:

	string ruta_arch_bloques;

	HandlerEspLibre handler_esp_libre;


public:

	/*
	 * Obtiene el tamanio del archivo de bloques.
	 * Pre: -
	 * Pos: devuelve dicho tamanio.
	 */
	int get_tam_arch_bloques() const;

	HandlerBloquesOtraVersion() {};

	HandlerBloquesOtraVersion(const string& ruta_arch_bloques, const string& ruta_arch_esp_Libre);

	virtual ~HandlerBloquesOtraVersion() {};

	void set_ruta_arch_bloques(const string& ruta_arch_bloques);

	void set_ruta_arch_esp_libre(const string& ruta_arch_esp_libre);

	const string& get_ruta_arch_bloques() const { return this->ruta_arch_bloques; }

	const HandlerEspLibre& get_handler_esp_libre() const { return this->handler_esp_libre; }

	/*
	 * Obtiene la posicion en la que sera insertado el bloque en caso de que la operacion a llevar
	 * a cabo se trate de una insercion.
	 * Pre: -
	 * Pos: o bien devuelve la posicion de un espacio libre en el archivo de bloques o la posicion
	 * siguiente a la ultima posicion del ultimo bloque del archivo de bloques.
	 */
	//int get_pos_insercion() const;

	/*
	 * Carga el bloque que se encuentra en la posicion pasada por parametro desde el archivo de
	 * bloques a memoria principal para su posterior lectura o modificacion.
	 * Pre: -
	 * Pos: devuelve por parametro un puntero a una instancia de la clase Bloq con todos sus
	 * atributos inicializados segun la información cargada desde el archivo de bloques(que
	 * permanece intacto).
	 */
		char* recuperar_bloque(int pos_arch_bloques);

	/*
	 * Guarda el bloque pasado por referencia en el archivo de bloques. Si hay algun espacio libre,
	 * el bloque se almacena alli, de lo contrario, se almacena al final del archivo. En caso de que
	 * se almacene en un espacio libre, este metodo tambien involucra la correspondiente actualizacion
	 * del archivo de espacios libres. Tanto el archivo de bloques como el de espacios libres se ven
	 * modificados.
	 * Pre: -
	 * Pos: devuelve la posicion del archivo de bloques en donde se realizo la insercion del bloque
	 * en cuestion.
	 */
	int guardar_bloque(char* bloque);

	/*
	 * Guarda el bloque pasado por referencia en la posicion pasada por parametro en el archivo de
	 * bloques. En caso de que se almacene en una posicion que esta incluida en el archivo de espacios libres,
	 * este metodo tambien involucra la correspondiente actualizacion del archivo de espacios libres. El
	 * archivo de bloques se ve modificado y el de espacios libres varia segun el caso.
	 * Pre: -
	 * Pos: -
	 */
	void guardar_bloque(char* bloque, int pos_arch_bloques);

	/*
	 * Elimina el bloque que se encuentra almacenado en la posicion pasada por parametro del archivo de
	 * bloques, con lo cual involucra la correspondiente actualizacion del archivo de espacios libres.
	 * Pre: -
	 * Pos: devuelve FALSO si se solicita la eliminacion de un bloque que ya esta incluido en el archivo
	 * de espacios libres o si la posicion solicitada se encuentra fuera del rango de tamanio del archivo de
	 * bloques. Devuelve VERDADERO en caso contrario.
	 */
	bool eliminar_bloque(int pos_arch_bloques);

};

#endif /* HANDLERARCHIVOBLOQUES_H_ */