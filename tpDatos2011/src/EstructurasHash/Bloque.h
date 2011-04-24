/*
 * Bloque.h
 *
 *  Created on: 22/04/2011
 *      Author: angeles
 */

#ifndef BLOQUE_H_
#define BLOQUE_H_

#include "../ModuloDePersistencia/Serializable.h"

class Bloque : public Serializable {

private:

	int tam_disp;

public:

	Bloque(int tam_disp = 1);
	virtual ~Bloque() {};

	void set_tam_disp(int tam_disp);
	int get_tam_disp() const { return this->tam_disp; }

	void duplicar_tam_disp();
	void truncar_tam_disp();

};

#endif /* BLOQUE_H_ */
