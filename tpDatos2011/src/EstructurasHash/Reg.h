/*
 * Reg.h
 *
 *  Created on: 23/04/2011
 *      Author: catu
 */

#ifndef REG_H_
#define REG_H_

#include "../ModuloDePersistencia/Serializable.h"
#include "../ModuloDePersistencia/Persistencia.h"

class Reg : public Serializable{

protected:

	int clave;

public:

	Reg() : clave(-1) {}

	Reg(int clave) : clave(clave) {}

	virtual ~Reg() {};

	void set_clave(int clave);

	int get_clave() const { return this->clave; }

};

#endif /* REG_H_ */
