
#include "Resultado.h"

Resultado::Resultado() {
	flags = RESULTADO_OK;
}

Resultado::Resultado(eFlagsResultado flag) {
	flags = flag;
}

Resultado::Resultado(eFlagsResultado flag, Clave clave) {
	flags = flag;
	ultimaClave = clave;
}

bool Resultado::contiene(eFlagsResultado flag) const {
	return (flags & flag) != 0;
}

Resultado& Resultado::operator|=(const Resultado &unResultado) {

	flags = eFlagsResultado(flags | unResultado.flags);

	if (unResultado.contiene(ACTUALIZAR_ULTIMA_CLAVE))
		ultimaClave = unResultado.ultimaClave;

	return *this;
}
