/*
 * Registro_Hash.h
 *
 *  Created on: 31/03/2011
 *      Author: angeles
 */

#ifndef REGINDICE_H_
#define REGINDICE_H_

#include "Elemento.h"

class RegIndice : public Serializable {

private:

	int clave;
	int bloque_sig;
	list < Elemento > elementos;

public:

	RegIndice();
	RegIndice(int clave);
	virtual ~RegIndice() {};

	void set_clave(int clave);
	void set_bloque_sig(int bloque_sig);
	void set_elementos(const list < Elemento > & elementos);

	int get_clave() const { return this->clave; }
	int get_bloque_sig() const { return this->bloque_sig; }
	const list < Elemento > & get_elementos() const { return this->elementos; }

	bool esta_vacio();
	int get_tam();

	void agregar_nuevo_elemento(const Elemento& elemento);
	int eliminar_elemento(const string& cadena);

	bool existe_elemento(const string& cadena);
	Elemento& buscar_elemento(const string& cadena);

	void serializar(char* buffer, unsigned int& offset);
	void hidratar(char* buffer, unsigned int& offset);

	void toString();

};

#endif /* REGINDICE_H_ */
