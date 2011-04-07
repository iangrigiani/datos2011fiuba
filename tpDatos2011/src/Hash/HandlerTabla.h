/*
 * HandlerTabla.h
 *
 *  Created on: 31/03/2011
 *      Author: angeles
 */

#ifndef HANDLERTABLA_H_
#define HANDLERTABLA_H_

#define NOM_ARCH_TABLA "Tabla_hash_extensible"
#define NOM_ARCH_TEMP "Temp"

#include <cstdio>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include "Bloque_Hash.h"

class HandlerTabla {

private:

	int tam_tabla;

public:

	HandlerTabla();
	virtual ~HandlerTabla() {};

	void set_tam_tabla(int tam_tabla);
	int get_tam_tabla() const { return this->tam_tabla; }

	void duplicar_tabla();
	void truncar_tabla();

	bool mitades_iguales() const;
	int get_num_bloque(int clave) const;

	void reemplazar_referencia(const Bloque_Hash& bloque_a_reemplazar, const Bloque_Hash& nuevo_bloque);
	void reemplazar_referencias(int pos_inicial, const Bloque_Hash& nuevo_bloque);

	bool puedo_liberar_bloque(const Bloque_Hash& bloque_a_liberar, int pos_actual,
			int* num_bloque_por_reemplazar) const;
	void liberar_referencias(int pos_inicial, const Bloque_Hash& bloque_por_reemplazar);

};

#endif /* HANDLERTABLA_H_ */
