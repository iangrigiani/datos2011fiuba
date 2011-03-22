#ifndef ELEMENTOS_H_
#define ELEMENTOS_H_

#include "../ModuloDePersistencia/Serializable.h"
/*
 * ESTOS ELEMENTOS SON LOS QUE ALMACENARA EL NODO
 */
class Elementos : public Serializable {
public:
	Elementos();
	virtual ~Elementos();
	int getTamanio() const{
		return 0;
	}
	void serializar(char * buffer, unsigned int &offset);
	void hidratar(char * buffer, unsigned int &offset);

};

#endif /* ELEMENTOS_H_ */
