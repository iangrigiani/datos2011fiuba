#ifndef CUBO_H_
#define CUBO_H_

class HandlerTabla;

#include "Bloque.h"
#include "RegPalabra.h"
#include "../EstructurasEnComun/Constantes.h"
#include "../Hash/HandlerTabla.h"

class Cubo : public Bloque {

private:

	int esp_libre;
	list < RegPalabra > regs;

public:

	Cubo(int tam_disp = 1);
	virtual ~Cubo() {};

	bool esta_vacio() const;
	bool entra_en_bloque(const RegPalabra& reg) const;
	bool entra_en_bloque(list < int > & offsets) const;

	void aumentar_esp_libre(int diferencial);
	void disminuir_esp_libre(int diferencial);

	void agregar_nuevo_reg(const RegPalabra& reg);
	bool eliminar_reg(int clave);
	bool existe_reg(int clave);
	RegPalabra& buscar_reg(int clave);
	list < RegPalabra > & get_regs() { return this->regs; }

	void incorporar_regs(list < RegPalabra > & regs);
	list < RegPalabra > actualizar_regs(int num_bloque, HandlerTabla& handler);

	void vaciar();

	void serializar(char* buffer, unsigned int& offset);
	void hidratar(char* buffer, unsigned int& offset);

	void toString();

};

#endif /* CUBO_H_ */
