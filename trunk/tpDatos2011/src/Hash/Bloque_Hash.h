/*
 * Bloque_Hash.h
 *
 *  Created on: 31/03/2011
 *      Author: angeles
 */

#ifndef BLOQUE_HASH_H_
#define BLOQUE_HASH_H_

#include "Registro_Hash.h"

#define TAM_BLOQUE 4096

class Bloque_Hash {

private:

	int pos_arch;
	int tam_dispersion;
	int espacio_libre;
	list < int > pos_tabla;
	list < Registro_Hash > regs;

public:

	Bloque_Hash(int pos_arch, int tam_dispersion = 1);
	virtual ~Bloque_Hash() {};

	void duplicar_tam_dispersion();
	void truncar_tam_dispersion();
	int get_tam_dispersion() const { return this->tam_dispersion; }

	int get_pos_arch() const { return this->pos_arch; }

	bool esta_vacio() const;
	bool entra_en_bloque(const Registro_Hash& reg) const;

	void agregar_nueva_pos(int pos);
	bool eliminar_pos(int pos);

	void agregar_nuevo_reg(const Registro_Hash& reg);
	bool eliminar_reg(int clave);

	bool agregar_nuevo_offset_a_reg(int clave, int offset);
	int eliminar_offset_de_reg(int clave, int offset);

	list < Registro_Hash > actualizar_regs(int tam_tabla);
	void incorporar_regs(list < Registro_Hash > regs);

	void vaciar();

	void serializar(char* buffer, unsigned int& offset);
	void hidratar(char* buffer, unsigned int& offset);
	void toString();
};

#endif /* BLOQUE_HASH_H_ */
