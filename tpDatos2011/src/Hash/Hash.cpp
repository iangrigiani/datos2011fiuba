/*
 * Hash.cpp
 *
 *  Created on: 23/04/2011
 *      Author: catu
 */

#include "Hash.h"

Hash::Hash(int tam_bloque, const string& ruta_arch_bloques,
			const string& ruta_arch_esp_libre, const string& ruta_arch_tabla,
			const string& ruta_arch_temporal) {

	this->handler_bloques.set_tam_bloque(tam_bloque);
	this->handler_bloques.set_ruta_arch_bloques(ruta_arch_bloques);
	HandlerEspLibre handler_esp_libre(ruta_arch_esp_libre);
	this->handler_bloques.set_handler_esp_libre(handler_esp_libre);
	this->handler_tabla.set_ruta_arch_tabla(ruta_arch_tabla);
	this->handler_tabla.set_ruta_arch_temporal(ruta_arch_temporal);
}
