/*
 * Ranura.h
 *
 *  Created on: 21/04/2011
 *      Author: angeles
 */

#ifndef RANURA_H_
#define RANURA_H_

class HandlerTabla;

#include "Bloque.h"
#include "RegTitulo.h"
#include "../Hash/HandlerTabla.h"


class Ranura : public Bloque {

private:

	int estado;
	RegTitulo reg;

public:

	Ranura(int tam_disp = 1);
	virtual ~Ranura() {};

	void modificar_estado();
	bool esta_ocupada();

	RegTitulo get_reg() const { return this->reg; }
	void agregar_nuevo_reg(const RegTitulo& reg);
	bool eliminar_reg(int clave);

	bool actualizar_reg(int num_bloque, HandlerTabla& handler, RegTitulo& reg);

	void serializar(char* buffer, unsigned int& offset);
	void hidratar(char* buffer, unsigned int& offset);

	void toString();

};

#endif /* RANURA_H_ */
