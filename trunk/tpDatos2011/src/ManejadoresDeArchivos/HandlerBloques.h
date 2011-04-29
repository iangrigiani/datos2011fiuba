#ifndef HANDLERBLOQUES_H_
#define HANDLERBLOQUES_H_

#include "HandlerEspLibre.h"

class HandlerBloques {

private:

	int tam_bloque;

	string ruta_arch_bloques;

	HandlerEspLibre handler_esp_libre;

public:

	HandlerBloques();

	HandlerBloques(int tam_bloque, const string& ruta_arch_bloques, const HandlerEspLibre& handler_esp_libre);

	virtual ~HandlerBloques() {};

	void set_tam_bloque(int tam_bloque);

	void set_ruta_arch_bloques(const string& ruta_arch_bloques);

	void set_handler_esp_libre(const HandlerEspLibre& handler_esp_libre);

	int get_tam_bloque() const { return this->tam_bloque; }

	const string& get_ruta_arch_bloques() const { return this->ruta_arch_bloques; }

	const HandlerEspLibre& get_handler_esp_libre() const { return this->handler_esp_libre; }

	/*
	 * Obtiene el tamanio del archivo de bloques.
	 * Pre: -
	 * Pos: devuelve dicho tamanio.
	 */
	int get_tam_arch_bloques() const;

	/*
	 * Carga el bloque que se encuentra en la posicion pasada por parametro desde el archivo de
	 * bloques a memoria principal para su posterior lectura o modificacion.
	 * Pre: -
	 * Pos: devuelve por parametro un puntero a una instancia de la clase Bloq con todos sus
	 * atributos inicializados segun la información cargada desde el archivo de bloques(que
	 * permanece intacto).
	 */
	void recuperar_bloque(char* buffer, int pos_arch_bloques);

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
	int guardar_bloque(char* buffer);

	/*
	 * Guarda el bloque pasado por referencia en la posicion pasada por parametro en el archivo de
	 * bloques. En caso de que se almacene en una posicion que esta incluida en el archivo de espacios libres,
	 * este metodo tambien involucra la correspondiente actualizacion del archivo de espacios libres. El
	 * archivo de bloques se ve modificado y el de espacios libres varia segun el caso.
	 * Pre: -
	 * Pos: -
	 */
	void guardar_bloque(char* buffer, int pos_arch_bloques);

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

#endif /* HANDLERBLOQUES_H_ */
