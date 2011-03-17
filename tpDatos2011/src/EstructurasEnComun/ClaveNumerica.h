#ifndef CLAVENUMERICA_H_
#define CLAVENUMERICA_H_
#include "../ModuloDePersistencia/Persistencia.h"
class ClaveNumerica{
private:
	int clave;
public:
	ClaveNumerica();

	ClaveNumerica(int clave);

	ClaveNumerica(const ClaveNumerica &a){
		this->clave = a.clave;
	}
	int getValorClave();
	int getTipo();

	void serialize(char * buffer, unsigned int &offset);

	void unserialize(char * buffer, unsigned int &offset);

	bool igual (ClaveNumerica *a);

	bool esMenor(ClaveNumerica *a);

	void toString();
	int getTamanio()const{
		return sizeof(this->clave);
	}
	ClaveNumerica * getClaveNula(){
		return new ClaveNumerica(0);
	}
	ClaveNumerica * getClaveError(){
		return new ClaveNumerica(-1);
	}
	bool esMenorIgual(ClaveNumerica *a);
	virtual ~ClaveNumerica();
};

#endif /* CLAVENUMERICA_H_ */
