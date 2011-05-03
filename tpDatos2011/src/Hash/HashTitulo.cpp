/*
 * HashTitulo.cpp
 *
 *  Created on: 22/04/2011
 *      Author: angeles
 */

#include "HashTitulo.h"

void HashTitulo::crear_condiciones_iniciales() {
	if (this->handler_tabla.tabla_vacia() == true) {
		Ranura bloque;
		unsigned int offset = 0;
		char buffer[TAM_RANURA];

		bloque.serializar(buffer, offset);
		int num_bloque = this->handler_bloques.guardar_bloque(buffer);
		this->handler_tabla.crear_tabla_inicial(num_bloque);
	}
}

bool HashTitulo::insertar_reg(const RegTitulo& reg) {
	Ranura bloque;
	unsigned int offset = 0;
	char buffer[TAM_RANURA];

	int pos_tabla_bloque = this->handler_tabla.get_pos_tabla(reg.get_clave());
	int num_bloque = this->handler_tabla.get_num_bloque(reg.get_clave());
	this->handler_bloques.recuperar_bloque(buffer, num_bloque);
	bloque.hidratar(buffer, offset);

	if (bloque.esta_ocupada() == false) {
		bloque.agregar_nuevo_reg(reg);
		offset = 0;
		bloque.serializar(buffer, offset);
		this->handler_bloques.guardar_bloque(buffer, num_bloque);
	}
	else {
		if (bloque.get_reg().get_clave() == reg.get_clave())
			return false;

		RegTitulo reg_aux;

		int tam_disp_inicial = bloque.get_tam_disp();
		bloque.duplicar_tam_disp();
		Ranura nuevo_bloque(bloque.get_tam_disp());

		offset = 0;
		nuevo_bloque.serializar(buffer, offset);
		int num_nuevo_bloque = this->handler_bloques.guardar_bloque(buffer);

		if (tam_disp_inicial == this->handler_tabla.get_tam_tabla()) {
			this->handler_tabla.duplicar_tabla();
			this->handler_tabla.reemplazar_referencia(num_bloque, num_nuevo_bloque);
		}
		else this->handler_tabla.reemplazar_referencias(pos_tabla_bloque, num_nuevo_bloque, nuevo_bloque);

		if (bloque.actualizar_reg(num_bloque, this->handler_tabla, reg_aux) == true) {
			nuevo_bloque.agregar_nuevo_reg(reg_aux);
			offset = 0;
			nuevo_bloque.serializar(buffer, offset);
			this->handler_bloques.guardar_bloque(buffer, num_nuevo_bloque);
		}

		offset = 0;
		bloque.serializar(buffer, offset);
		this->handler_bloques.guardar_bloque(buffer, num_bloque);

		this->insertar_reg(reg);
	}
	return true;
}

bool HashTitulo::eliminar_reg(int clave) {
	Ranura bloque;
	unsigned int offset = 0;
	char buffer[TAM_RANURA];

	int pos_tabla_bloque = this->handler_tabla.get_pos_tabla(clave);
	int num_bloque = this->handler_tabla.get_num_bloque(clave);
	this->handler_bloques.recuperar_bloque(buffer, num_bloque);
	bloque.hidratar(buffer, offset);

	if (bloque.eliminar_reg(clave) == false)
		return false;

	int num_otro_bloque = this->handler_tabla.puedo_liberar_bloque(bloque, pos_tabla_bloque);
	if (num_otro_bloque != -1) {
		Ranura otro_bloque;

		offset = 0;
		this->handler_bloques.recuperar_bloque(buffer, num_otro_bloque);
		otro_bloque.hidratar(buffer, offset);
		this->handler_tabla.liberar_referencias(pos_tabla_bloque, num_otro_bloque, otro_bloque);

		otro_bloque.truncar_tam_disp();
		offset = 0;
		otro_bloque.serializar(buffer, offset);
		this->handler_bloques.guardar_bloque(buffer, num_otro_bloque);
		this->handler_bloques.eliminar_bloque(num_bloque);

		if (this->handler_tabla.mitades_iguales() == true)
			this->handler_tabla.truncar_tabla();
	}
	else {
		offset = 0;
		bloque.serializar(buffer, offset);
		this->handler_bloques.guardar_bloque(buffer, num_bloque);
	}

	return true;
}

void HashTitulo::mostrar() {
	Ranura bloque;
	char buffer[TAM_RANURA];
	unsigned int offset;
	int cant_bloques = this->handler_bloques.get_tam_arch_bloques() / TAM_RANURA;

	cout << endl;
	for (int i = 0; i < cant_bloques; ++ i) {
		cout << "N° " << i << ":" << endl;
		offset = 0;
		this->handler_bloques.recuperar_bloque(buffer, i);
		bloque.hidratar(buffer, offset);
		bloque.toString();
		cout << endl;
	}
}
