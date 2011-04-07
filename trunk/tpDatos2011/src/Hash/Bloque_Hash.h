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

	int pos_arch;
	int tam_dispersion;
	list < int > pos_tabla;

public:

	Bloque_Hash(int tam_dispersion = 1);
	virtual ~Bloque_Hash() {};

	void duplicar_tam_dispersion();
	void truncar_tam_dispersion();
	int get_tam_dispersion() const { return this->tam_dispersion; }

	int get_pos_arch() const { return this->pos_arch; }

	void agregar_nueva_pos(int pos);
	bool eliminar_pos(int pos);

	list < Reg > actualizar_regs(int tam_tabla);
	void incorporar_regs(list < Reg > regs);

	void serializar(char* buffer, unsigned int& offset);
	void hidratar(char* buffer, unsigned int& offset);
	void toString();
};

#endif /* BLOQUE_HASH_H_ */
