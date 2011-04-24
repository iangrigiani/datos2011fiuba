#ifndef HASHPALABRAS_H_
#define HASHPALABRAS_H_

#include "Hash.h"
#include "../EstructurasHash/Cubo.h"

class HashPalabras : public virtual Hash {

private :

	void obtener_registro(RegPalabras& reg,Cubo& bloque_sig ,list <int> & bloques_sigs,int clave);
	void insertar_bloque(Cubo& nuevo_bloque,int& num_nuevo_bloque);


public:

	HashPalabras() : Hash(TAM_BLOQUE,PATH_BLOQUES_PALABRAS,PATH_ESPACIO_LIBRE_PALABRAS,
							PATH_TABLA_PALABRAS,PATH_TMP_PALABRAS){}
	virtual ~HashPalabras() {};

	void crear_condiciones_iniciales();

	void agregar_nuevos_offsets(Cubo& bloque, int num_bloque, RegPalabras& reg, list < int > & offsets);

	void insercion(int clave, list < int > & offsets);


	void eliminar_offset(Cubo& bloque, int num_bloque, int clave, int offset);

	void eliminacion(int clave, int offset);

	void insertar_reg(const RegPalabras& reg);

	bool eliminar_reg(int clave);

};

#endif /* HASHPALABRAS_H_ */
