
#ifndef RESULTADO_H_
#define RESULTADO_H_

#include "../EstructurasEnComun/Clave.h"

class Resultado {

	friend class ArbolBMas;

private:

	enum eFlagsResultado {RESULTADO_OK = 0, NO_ENCONTRADO = 1, ACTUALIZAR_ULTIMA_CLAVE = 2, FUSION_NODOS = 4} flags;
	Clave ultimaClave;

public:
	Resultado();
	Resultado(eFlagsResultado flag);
	Resultado(eFlagsResultado flag, Clave clave);
	bool contiene(eFlagsResultado flag) const;
	Resultado& operator|=(const Resultado &unResultado);

};

#endif /* RESULTADO_H_ */
