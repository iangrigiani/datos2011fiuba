/*
 * Bloque_Hash.h
 *
 *  Created on: 31/03/2011
 *      Author: angeles
 */

#ifndef BLOQUE_HASH_H_
#define BLOQUE_HASH_H_

#include "Bloq.h"

class Bloque_Hash : public Bloq {

private:

	int tam_dispersion;

public:

	Bloque_Hash(int tam_dispersion = 1);
	virtual ~Bloque_Hash() {};

	void duplicar_tam_dispersion();
	void truncar_tam_dispersion();

	int get_tam_dispersion() const { return this->tam_dispersion; }

	bool agregar_nuevo_offset_a_reg(int clave, int offset);
	int eliminar_offset_de_reg(int clave, int offset);

	void incorporar_regs(list < Reg > regs);

	void serializar(char* buffer, unsigned int& offset);
	void hidratar(char* buffer, unsigned int& offset);

	void toString();
};

#endif /* BLOQUE_HASH_H_ */
