/*
 * Hash.cpp
 *
 *  Created on: 08/04/2011
 *      Author: angeles
 */

#include "Hash.h"

Hash::Hash(const string& ruta_arch_bloques, const string& ruta_arch_esp_libre) {
	this->handler_bloques.set_ruta_arch_bloques(ruta_arch_bloques);
	HandlerEspLibre handler_esp_libre(ruta_arch_esp_libre);
	this->handler_bloques.set_handler_esp_libre(handler_esp_libre);
}

void Hash::crear_condiciones_iniciales() {
	if (this->handler_tabla.tabla_vacia() == true) {
		Bloque_Hash bloque;
		int num_bloque = this->handler_bloques.guardar_bloque(bloque);
		this->handler_tabla.crear_tabla_inicial(num_bloque);
	}
}

void Hash::insertar_reg(const Reg& reg) {
	int pos_tabla_bloque;
	Bloque_Hash bloque;
	int num_bloque = this->handler_tabla.get_num_bloque(reg.get_clave(), pos_tabla_bloque);
	this->handler_bloques.recuperar_bloque(bloque, num_bloque);

	if (bloque.get_esp_libre() >= reg.get_tam()) {
		bloque.agregar_nuevo_reg(reg);
		this->handler_bloques.guardar_bloque(bloque, num_bloque);
	}
	else {
		int num_nuevo_bloque;
		int tam_tabla = this->handler_tabla.get_tam_tabla();

		if (bloque.get_tam_dispersion() == tam_tabla) {
			bloque.duplicar_tam_dispersion();
			Bloque_Hash nuevo_bloque(bloque.get_tam_dispersion());

			this->handler_tabla.duplicar_tabla();
			num_nuevo_bloque = this->handler_bloques.guardar_bloque(nuevo_bloque);
			this->handler_tabla.reemplazar_referencia(num_bloque, num_nuevo_bloque);

			list < Reg > regs_desactualizados = this->handler_tabla.actualizar_regs(num_bloque, bloque);
			nuevo_bloque.incorporar_regs(regs_desactualizados);

			this->handler_bloques.guardar_bloque(bloque, num_bloque);
			this->handler_bloques.guardar_bloque(nuevo_bloque, num_nuevo_bloque);
		}
		else {
			bloque.duplicar_tam_dispersion();
			Bloque_Hash nuevo_bloque(bloque.get_tam_dispersion());

			num_nuevo_bloque = this->handler_bloques.guardar_bloque(nuevo_bloque);
			this->handler_tabla.reemplazar_referencias(pos_tabla_bloque, num_nuevo_bloque, nuevo_bloque);

			list < Reg > regs_desactualizados = this->handler_tabla.actualizar_regs(num_bloque, bloque);
			nuevo_bloque.incorporar_regs(regs_desactualizados);

			this->handler_bloques.guardar_bloque(bloque, num_bloque);
			this->handler_bloques.guardar_bloque(nuevo_bloque, num_nuevo_bloque);
		}
	}
}

bool Hash::eliminar_reg(int clave) {
	int pos_tabla_bloque;
	Bloque_Hash bloque;
	int num_bloque = this->handler_tabla.get_num_bloque(clave, pos_tabla_bloque);
	this->handler_bloques.recuperar_bloque(bloque, num_bloque);

	if (bloque.eliminar_reg(clave) == false)
		return false;

	if (bloque.esta_vacio() == true) {
		int num_otro_bloque = this->handler_tabla.puedo_liberar_bloque(bloque, pos_tabla_bloque);
		if (num_otro_bloque != NULL) {
			Bloque_Hash otro_bloque;
			this->handler_bloques.recuperar_bloque(otro_bloque, num_otro_bloque);
			this->handler_tabla.liberar_referencias(pos_tabla_bloque, num_otro_bloque, otro_bloque);

			otro_bloque.truncar_tam_dispersion();
			this->handler_bloques.guardar_bloque(otro_bloque, num_otro_bloque);
			this->handler_bloques.eliminar_bloque(num_bloque);

			if (this->handler_tabla.mitades_iguales() == true)
				this->handler_tabla.truncar_tabla();
		}
	}
	return true;
}

