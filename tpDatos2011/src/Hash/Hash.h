/*
 * Hash.h
 *
 *  Created on: 23/04/2011
 *      Author: catu
 */

#ifndef HASH_H_
#define HASH_H_

#include "HandlerTabla.h"
#include "../ManejadoresDeArchivos/HandlerBloques.h"
#include "../EstructurasEnComun/Constantes.h"

class Hash {

protected:

		HandlerTabla handler_tabla;
		HandlerBloques handler_bloques;

public:

		Hash(int tam_bloque, const string& ruta_arch_bloques, const string& ruta_arch_esp_libre,
				const string& ruta_arch_tabla, const string& ruta_arch_temporal);
		virtual ~Hash() {};

		const HandlerTabla& get_handler_tabla() const { return this->handler_tabla; }

		HandlerBloques& get_handler_bloques() { return this->handler_bloques; }

		virtual void crear_condiciones_iniciales() = 0;

		virtual void mostrar() = 0;

};


#endif /* HASH_H_ */
