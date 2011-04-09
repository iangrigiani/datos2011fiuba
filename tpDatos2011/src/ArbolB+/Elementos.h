#ifndef ELEMENTOS_H_
#define ELEMENTOS_H_

#include "../ModuloDePersistencia/Serializable.h"
#include "../EstructurasEnComun/Clave.h"
#include <string>
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
using namespace std;

/*
 * ESTOS ELEMENTOS SON LOS QUE ALMACENARA EL NODO
 */
class Elementos : public Serializable {
private:
	Clave* clave;
	unsigned int offset;
public:
	Elementos();
	Elementos(Clave* clave, unsigned int offset);
	virtual ~Elementos();
	int getTamanio() const{
		return (sizeof(int) + this->clave->getTamanio());
	}
	void toString();
	void serializar(char * buffer, unsigned int &offset);
	void hidratar(char * buffer, unsigned int &offset);
    Clave *getClave() const{
        return clave;
    }
    unsigned int getOffset() const{
        return offset;
    }
};

#endif /* ELEMENTOS_H_ */
