#ifndef CUBO_H_
#define CUBO_H_

class HandlerTabla;

#include "Bloque.h"
#include "RegPalabras.h"
#include "../EstructurasEnComun/Constantes.h"
#include "../Hash/HandlerTabla.h"

class Cubo : public Bloque {

private:

	int esp_libre;
	list < RegPalabras > regs;

public:

	Cubo(int tam_disp = 1);
	virtual ~Cubo() {};

	bool esta_vacio() const;
	bool entra_en_bloque(const RegPalabras& reg) const;
	bool entra_en_bloque(list < int > & offsets) const;

	void aumentar_esp_libre(int diferencial);
	void disminuir_esp_libre(int diferencial);

	void agregar_nuevo_reg(const RegPalabras& reg);
	bool eliminar_reg(int clave);
	bool existe_reg(int clave);
	RegPalabras& buscar_reg(int clave);
	list < RegPalabras > & get_regs() { return this->regs; }

	void incorporar_regs(list < RegPalabras > & regs);
	list < RegPalabras > actualizar_regs(int num_bloque, HandlerTabla& handler);

	void vaciar();

	void serializar(char* buffer, unsigned int& offset);
	void hidratar(char* buffer, unsigned int& offset);

	void toString();

};

#endif /* CUBO_H_ */
