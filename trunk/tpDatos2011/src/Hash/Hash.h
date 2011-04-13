#ifndef HASH_H_
#define HASH_H_

#define NOM_ARCH_BLOQUES "BloquesHash"
#define NOM_ARCH_ESP_LIBRE "EspLibreHash"

#include "HandlerTabla.h"
#include "..//ManejadoresDeArchivos/HandlerBloques.h"

class Hash {

private:

	HandlerTabla handler_tabla;
	HandlerBloques handler_bloques;

public:

	Hash(const string& ruta_arch_bloques, const string& ruta_arch_esp_libre);
	virtual ~Hash() {};

	const HandlerTabla& get_handler_tabla() const { return this->handler_tabla; }

	HandlerBloques& get_handler_bloques() { return this->handler_bloques; }

	void crear_condiciones_iniciales();

	void insertar_reg(const Reg& reg);

	bool eliminar_reg(int clave);

};

#endif /* HASH_H_ */
