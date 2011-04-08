#ifndef BLOQUE_H_
#define BLOQUE_H_

#include <list>
#include "Registro.h"
#include "Constantes.h"
#include "../ModuloDePersistencia/Serializable.h"
#include "../ModuloDePersistencia/Persistencia.h"
class Bloque: public Serializable {
private:
	int espacioLibre;
	std::list <Registro*> registros;
public:
	Bloque();
	bool agregarRegistro(Registro * reg);
	bool tieneEspacio(int size);

	Registro *getRegistro(Clave * clave);

	Registro *getSiguienteRegistro(Clave * clave, Clave * previousKey);

	int getCantidadRegistros(){
		return this->registros.size();
	}
	int getEspacioLibre(){
		return this->espacioLibre;
	}
	std::list<Registro*> getListaRegistros(){
		return this->registros;
	}

	void serializar(char * buffer, unsigned int &offset);

	void hidratar(char * buffer, unsigned int &offset);

	void limpiar();
	void toString();
	virtual ~Bloque();
};

#endif /* BLOQUE_H_ */
