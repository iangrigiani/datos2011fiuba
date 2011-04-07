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
	list < int > offsets;

public:

	Reg();
	Reg(int clave);
	virtual ~Reg() {};

	int get_clave() const { return this->clave; }

	int get_tam() const;

	void agregar_nuevo_offset(int offset);
	bool eliminar_offset(int offset);

	void serializar(char* buffer, unsigned int& offset);
	void hidratar(char* buffer, unsigned int& offset);

	void toString();
};

#endif /* REG_H_ */
