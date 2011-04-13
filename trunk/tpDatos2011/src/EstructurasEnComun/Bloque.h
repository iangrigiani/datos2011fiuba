#ifndef BLOQUE_H_
#define BLOQUE_H_

#include "Reg.h"
#include "Constantes.h"

class Bloque : public Serializable {

private:

	int pos_bloque_aux;
	int esp_libre;
	list < Reg > regs;

public:

	Bloque();
	virtual ~Bloque() {};

	bool esta_vacio() const;
	bool entra_en_bloque(const Reg& reg) const;

	void set_pos_bloque_aux(int pos_bloque_aux);

	void agregar_nuevo_reg(const Reg& reg);
	bool eliminar_reg(int clave);

	int get_pos_bloque_aux() const { return this->pos_bloque_aux; }
	int get_esp_libre() const { return this->esp_libre; }
	list < Reg >& get_regs() { return this->regs; }

	void vaciar();

	void serializar(char* buffer, unsigned int& offset);
	void hidratar(char* buffer, unsigned int& offset);

	void toString();

};

#endif /* BLOQUE */
