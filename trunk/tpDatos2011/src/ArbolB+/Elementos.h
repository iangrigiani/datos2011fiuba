#ifndef ELEMENTOS_H_
#define ELEMENTOS_H_

#include "../ModuloDePersistencia/Serializable.h"
#include "../EstructurasEnComun/ClaveNumerica.h"
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
	ClaveNumerica* clave;
	string dato;
	unsigned int offset;
public:
	Elementos();
	Elementos(ClaveNumerica* clave, string dato, unsigned int offset);
	virtual ~Elementos();
	int getTamanio() const{
		return (sizeof(int) + this->clave->getTamanio() + this->dato.length());
	}
	void toString();
	void serializar(char * buffer, unsigned int &offset);
	void hidratar(char * buffer, unsigned int &offset);
    ClaveNumerica *getClave() const{
        return clave;
    }

    string getDato() const{
        return dato;
    }

    unsigned int getOffset() const{
        return offset;
    }

    void setClave(ClaveNumerica *clave){
        this->clave = clave;
    }

    void setDato(string dato){
        this->dato = dato;
    }

    void setOffset(unsigned int offset){
        this->offset = offset;
    }

};

#endif /* ELEMENTOS_H_ */
