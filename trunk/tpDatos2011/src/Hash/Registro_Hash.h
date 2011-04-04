/*
 * Registro_Hash.h
 *
 *  Created on: 31/03/2011
 *      Author: angeles
 */

#ifndef REGISTRO_HASH_H_
#define REGISTRO_HASH_H_

#include <list>
#include "../ModuloDePersistencia/Serializable.h"
#include "../ModuloDePersistencia/Persistencia.h"

using namespace std;

class Registro_Hash: public Serializable {

private:

	int clave;
	list < int > offsets;

public:

	Registro_Hash(int clave);
	virtual ~Registro_Hash() {};

	int get_clave() const { return this->clave; }

	int obtener_tam() const;

	void agregar_nuevo_offset(int offset);
	bool eliminar_offset(int offset);

	void serializar(char* buffer, unsigned int& offset);
	void hidratar(char* buffer, unsigned int& offset);
	void toString();
};

#endif /* REGISTRO_HASH_H_ */
