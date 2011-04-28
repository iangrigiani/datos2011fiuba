#ifndef HASHPALABRA_H_
#define HASHPALABRA_H_

#include "Hash.h"
#include "../EstructurasHash/Cubo.h"

class HashPalabra : public virtual Hash {

private :

	void obtener_reg(RegPalabra& reg, Cubo& bloque_sig ,list < int > & bloques_sigs, int clave);

	void agregar_nuevos_offsets(Cubo& bloque, int num_bloque, RegPalabra& reg, list < int > & offsets);

	void eliminar_offset(Cubo& bloque, int num_bloque, int clave, int offset);

	void insertar_reg(const RegPalabra& reg);

	bool eliminar_reg(int clave);

public:

	HashPalabra() : Hash(TAM_CUBO, PATH_BLOQUES_PALABRA, PATH_ESP_LIBRE_PALABRA,
							PATH_TABLA_PALABRA, PATH_TMP_PALABRA) {}

	virtual ~HashPalabra() {};

	void crear_condiciones_iniciales();

	void insercion(int clave, list < int > & offsets);

	void eliminacion(int clave, int offset);

	void mostrar();

};

#endif /* HASHPALABRAS_H_ */
