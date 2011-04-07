/*
 * Bloque_Hash.h
 *
 *  Created on: 31/03/2011
 *      Author: angeles
 */

#ifndef BLOQ_H_
#define BLOQ_H_

#include "Reg.h"

#define TAM_BLOQUE 4096

class Bloq : public Serializable {

private:

	int pos_bloque_aux;
	int espacio_libre;
	list < Reg > regs;

public:

	Bloq();
	virtual ~Bloq() {};

	void set_pos_bloque_aux(int pos_bloque_aux);
	int get_pos_bloque_aux() const { return this->pos_bloque_aux; }

	bool esta_vacio() const;
	bool entra_en_bloque(const Reg& reg) const;

	void agregar_nuevo_reg(const Reg& reg);
	bool eliminar_reg(int clave);

	bool agregar_nuevo_offset_a_reg(int clave, int offset);
	int eliminar_offset_de_reg(int clave, int offset);

	void vaciar();

	void serializar(char* buffer, unsigned int& offset);
	void hidratar(char* buffer, unsigned int& offset);

	void toString();
};

#endif /* BLOQUE_HASH_H_ */
