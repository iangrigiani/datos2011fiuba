#ifndef REGISTRO_H_
#define REGISTRO_H_

#include <string>
#include "ClaveNumerica.h"
#include <iostream>
#include "../ModuloDePersistencia/Serializable.h"
#include "../ModuloDePersistencia/Persistencia.h"
class Registro: public Serializable {
private:
	std::string apellido;
	ClaveNumerica * Clave;

public:
	Registro();
	Registro(std::string apellido, int uiKey);
	Registro (ClaveNumerica * uiKey);
	Registro (const Registro &a);
	std::string getApellido();
	ClaveNumerica * getClave(){
		return this->Clave;
	}

	void toString();

	int getTamanio(){
		int size = 0;
		size += this->apellido.length()+sizeof(int)+1;
		size += sizeof(int);
		return size;
	}

	void serializar(char * buffer, unsigned int &offset);

	void hidratar(char * buffer, unsigned int &offset);

	virtual ~Registro();
};

#endif /* REGISTRO_H_ */
