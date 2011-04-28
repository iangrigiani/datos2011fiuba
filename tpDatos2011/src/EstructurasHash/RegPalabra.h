/*
 * Registro_Hash.h
 *
 *  Created on: 31/03/2011
 *      Author: angeles
 */

#ifndef REGPALABRA_H_
#define REGPALABRA_H_

#include <list>
#include "Reg.h"

using namespace std;

class RegPalabra: public Reg {

private:

	int bloque_sig;
	list < int > offsets;

public:

	RegPalabra() : Reg(), bloque_sig(-1) {}
	RegPalabra(int clave): Reg(clave), bloque_sig(-1) {}
	virtual ~RegPalabra() {};

	int get_tam() const;

	void set_bloque_sig(int bloque_sig);
	int get_bloque_sig() const { return this->bloque_sig; }

	void set_offsets(list < int > & offsets);
	list < int > get_offsets() const { return this->offsets; }

	void agregar_nuevos_offsets(list < int > & offsets);
	bool eliminar_offset(int offset);

	void serializar(char* buffer, unsigned int& offset);
	void hidratar(char* buffer, unsigned int& offset);

	void toString();

	void agregar_nuevo_offset(int offset);

};

#endif /* REGPALABRA_H_ */
