#ifndef CUBO_H_
#define CUBO_H_

#include "Reg.h"
#include "../EstructurasEnComun/Constantes.h"

class Cubo : public Serializable {

private:

	int esp_libre;
	int tam_disp;
	list < Reg > regs;

public:

	Cubo(int tam_disp = 1);
	virtual ~Cubo() {};

	bool esta_vacio() const;
	bool entra_en_bloque(int tam) const;

	void duplicar_tam_disp();
	void truncar_tam_disp();
	void aumentar_esp_libre(int diferencial);
	void disminuir_esp_libre(int diferencial);

	void agregar_nuevo_reg(const Reg& reg);
	bool eliminar_reg(int clave);
	bool buscar_reg(int clave, Reg& reg);

	int get_tam_disp() const { return this->tam_disp; }
	list < Reg >& get_regs() { return this->regs; }

	void incorporar_regs(list < Reg > regs);

	void vaciar();

	void serializar(char* buffer, unsigned int& offset);
	void hidratar(char* buffer, unsigned int& offset);

	void toString();

};

#endif /* CUBO_H_ */
