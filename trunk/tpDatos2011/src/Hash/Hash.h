#ifndef HASH_H_
#define HASH_H_

#include "../ManejadoresDeArchivos/HandlerBloques.h"
#include "../EstructurasHash/Cubo.h"

class Hash {

private :

	HandlerTabla handler_tabla;
	HandlerBloques handler_bloques;

	void obtener_reg(RegIndice& reg, Cubo& bloque_sig ,list < int > & bloques_sigs, int clave);

	void agregar_nuevos_offsets(Cubo& bloque, int num_bloque, RegIndice& reg, const string& cadena,
			list < int > & offsets);

	void eliminar_offset(Cubo& bloque, int num_bloque, int clave, const string& cadena, int offset);

	void insertar_reg(RegIndice& reg);

	bool eliminar_reg(int clave);

public:

	Hash(int tam_bloque, const string& ruta_arch_bloques, const string& ruta_arch_esp_libre,
			const string& ruta_arch_tabla, const string& ruta_arch_temporal);

	virtual ~Hash() {};

	const HandlerTabla& get_handler_tabla() const { return this->handler_tabla; }

	const HandlerBloques& get_handler_bloques() const { return this->handler_bloques; }

	void crear_condiciones_iniciales();

	void alta(int clave, const string& cadena, list < int > & offsets);

	void baja(int clave, const string& cadena, int offset);

	void mostrar();

};

#endif /* HASH_H_ */
