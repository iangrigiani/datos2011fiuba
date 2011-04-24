/*
 * HandlerTabla.h
 *
 *  Created on: 31/03/2011
 *      Author: angeles
 */

#ifndef HANDLERTABLA_H_
#define HANDLERTABLA_H_


#include <cstdio>
#include <string>
#include <fstream>
#include <sstream>
#include "../EstructurasHash/Bloque.h"
#include "../EstructurasHash/Cubo.h"
#include "../EstructurasHash/Ranura.h"

class HandlerTabla {

private:

	int tam_tabla;

	string ruta_arch_tabla;

	string ruta_arch_temporal;

public:

	HandlerTabla();
	virtual ~HandlerTabla() {};

	bool tabla_vacia();
	void crear_tabla_inicial(int num_bloque);

	void duplicar_tabla();
	void truncar_tabla();
	int get_tam_tabla() const { return this->tam_tabla; }

	void set_ruta_arch_tabla(const string& ruta_arch_tabla);

	const string& get_ruta_arch_tablas() const { return this->ruta_arch_tabla; }

	void set_ruta_arch_temporal(const string& ruta_arch_temporal);

	const string& get_ruta_arch_temporal() const { return this->ruta_arch_temporal; }

	bool mitades_iguales() const;

	int get_num_bloque(int clave, int& pos_tabla) const;

	void reemplazar_referencia(int num_bloque_a_reemplazar, int num_nuevo_bloque);
	void reemplazar_referencias(int pos_inicial, int num_nuevo_bloque, const Bloque& nuevo_bloque);

	int puedo_liberar_bloque(const Bloque& bloque_a_liberar, int pos_actual) const;
	void liberar_referencias(int pos_inicial, int num_bloque_por_reemplazar,
			const Bloque& bloque_por_reemplazar);

};

#endif /* HANDLERTABLA_H_ */
