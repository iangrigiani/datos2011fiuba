/*
 * HashTitulo.h
 *
 *  Created on: 22/04/2011
 *      Author: angeles
 */

#ifndef HASHTITULO_H_
#define HASHTITULO_H_

#define NOM_ARCH_REGS_FIJOS "RegsFijosHash"

#include "Hash.h"
#include "../EstructurasHash/Ranura.h"

class HashTitulo : public virtual Hash {

public:

	HashTitulo() : Hash(TAM_RANURA, PATH_BLOQUES_TITULO, PATH_ESP_LIBRE_TITULO,
								PATH_TABLA_TITULO, PATH_TMP_TITULO) {}

	virtual ~HashTitulo() {};

	void crear_condiciones_iniciales();

	bool insertar_reg(const RegTitulo& reg);

	bool eliminar_reg(int clave);

	void mostrar();

};

#endif /* HASHTITULO_H_ */
