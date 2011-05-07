/*
 * Elemento.h
 *
 *  Created on: 03/05/2011
 *      Author: angeles
 */

#ifndef ELEMENTO_H_
#define ELEMENTO_H_

#include <list>
#include <string>
#include <sstream>
#include "../ModuloDePersistencia/Serializable.h"
#include "../ModuloDePersistencia/Persistencia.h"

using namespace std;

class Elemento : public Serializable {

private:

	string cadena;
	list < int > offsets;

public:

	Elemento() {};
	Elemento(const string& cadena, const list < int > & offsets);
	virtual ~Elemento() {};

	void set_cadena(const string& cadena);
	void set_offsets(const list < int > & offsets);

	const string& get_cadena() const { return this->cadena; }
	const list < int > & get_offsets() const { return this->offsets; }

	int get_tam();

	void agregar_nuevos_offsets(list < int > & offsets);
	bool eliminar_offset(int offset);

	void serializar(char* buffer, unsigned int& offset);
	void hidratar(char* buffer, unsigned int& offset);

	void toString();

};

#endif /* ELEMENTO_H_ */
