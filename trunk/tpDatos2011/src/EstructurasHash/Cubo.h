#ifndef CUBO_H_
#define CUBO_H_

class HandlerTabla;

#include "RegIndice.h"
#include "../EstructurasEnComun/Constantes.h"
#include "../Hash/HandlerTabla.h"

class Cubo {

private:

	int tam_disp;
	int esp_libre;
	list < RegIndice > regs;

public:

	Cubo(int tam_disp = 1);
	virtual ~Cubo() {};

	bool esta_vacio() const;
	bool entra_en_bloque(RegIndice& reg) const;
	bool entra_en_bloque(const string& cadena, const list < int > & offsets) const;

	void duplicar_tam_disp();
	void truncar_tam_disp();
	int get_tam_disp() const { return this->tam_disp; }

	list < RegIndice > & get_regs() { return this->regs; }

	void agregar_nuevo_reg(RegIndice& reg);
	bool eliminar_reg(int clave);

	bool existe_reg(int clave);
	RegIndice& buscar_reg(int clave);

	void incorporar_regs(list < RegIndice > & regs);
	list < RegIndice > actualizar_regs(int num_bloque, HandlerTabla& handler);

	void vaciar();

	void serializar(char* buffer, unsigned int& offset);
	void hidratar(char* buffer, unsigned int& offset);

	void toString();

};

#endif /* CUBO_H_ */
