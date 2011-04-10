/*
 * Hash.h
 *
 *  Created on: 08/04/2011
 *      Author: angeles
 */

#ifndef HASH_H_
#define HASH_H_

#include "HandlerTabla.h"
#include "../HandlerArchivoBloques/HandlerArchivoBloques.h"

class Hash {

private:

	HandlerTabla handler_tabla;
	HandlerArchivoBloques handler_bloques;

public:

	Hash(const string& ruta_arch_bloques, const string& ruta_arch_esp_libre);
	virtual ~Hash() {};

	const HandlerTabla& get_handler_tabla() const { return this->handler_tabla; }

	HandlerArchivoBloques& get_handler_bloques() { return this->handler_bloques; }

	void crear_condiciones_iniciales();

	void insertar_reg(const Reg& reg);

	bool eliminar_reg(int clave);

};

#endif /* HASH_H_ */
