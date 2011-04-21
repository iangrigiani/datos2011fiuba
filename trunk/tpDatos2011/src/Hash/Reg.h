/*
 * Registro_Hash.h
 *
 *  Created on: 31/03/2011
 *      Author: angeles
 */

#ifndef REG_H_
#define REG_H_

#include <list>
#include "../ModuloDePersistencia/Serializable.h"
#include "../ModuloDePersistencia/Persistencia.h"

using namespace std;

class Reg: public Serializable {

private:

	int clave;
	int bloque_sig;
	list < int > offsets;

public:

	Reg();
	Reg(int clave);
	virtual ~Reg() {};

	void set_clave(int clave);
	int get_clave() const { return this->clave; }

	void set_bloque_sig(int bloque_sig);
	int get_bloque_sig() const { return this->bloque_sig; }

	int get_tam() const;

	list < int > get_offsets() const { return this->offsets; }

	void agregar_nuevo_offset(int offset);
	bool eliminar_offset(int offset);

	void incorporar_offsets(list < int > offsets);

	void serializar(char* buffer, unsigned int& offset);
	void hidratar(char* buffer, unsigned int& offset);

	void toString();

};

#endif /* REG_H_ */
