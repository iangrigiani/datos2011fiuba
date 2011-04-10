/*
 * HandlerTabla.h
 *
 *  Created on: 31/03/2011
 *      Author: angeles
 */

#ifndef HANDLERTABLA_H_
#define HANDLERTABLA_H_

#define NOM_ARCH_TABLA "TablaHash"
#define NOM_ARCH_TEMP "Temp"

#include <cstdio>
#include <string>
#include <fstream>
#include <sstream>
#include "Bloque_Hash.h"

class HandlerTabla {

private:

	int tam_tabla;

public:

	HandlerTabla();
	virtual ~HandlerTabla() {};

	bool tabla_vacia();
	void crear_tabla_inicial(int num_bloque);

	void duplicar_tabla();
	void truncar_tabla();
	int get_tam_tabla() const { return this->tam_tabla; }

	bool mitades_iguales() const;

	int get_num_bloque(int clave, int& pos_tabla) const;
	list < Reg > actualizar_regs(int num_bloque, Bloque_Hash& bloque);

	void reemplazar_referencia(int num_bloque_a_reemplazar, int num_nuevo_bloque);
	void reemplazar_referencias(int pos_inicial, int num_nuevo_bloque, const Bloque_Hash& nuevo_bloque);

	int puedo_liberar_bloque(const Bloque_Hash& bloque_a_liberar, int pos_actual) const;
	void liberar_referencias(int pos_inicial, int num_bloque_por_reemplazar,
			const Bloque_Hash& bloque_por_reemplazar);

};

#endif /* HANDLERTABLA_H_ */
