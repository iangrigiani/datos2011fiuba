
#include "Cubo.h"

Cubo::Cubo(int tam_disp) : esp_libre(TAM_BLOQUE), tam_disp(tam_disp) {}

bool Cubo::esta_vacio() const {
	if (this->esp_libre == TAM_BLOQUE)
		return true;
	return false;
}

bool Cubo::entra_en_bloque(int tam) const {
	if (this->esp_libre > tam)
		return true;
	return false;
}

void Cubo::duplicar_tam_disp() {
	this->tam_disp *= 2;
}

void Cubo::truncar_tam_disp() {
	this->tam_disp /= 2;
}

void Cubo::aumentar_esp_libre(int diferencial) {
	this->esp_libre += diferencial;
}

void Cubo::disminuir_esp_libre(int diferencial) {
	this->esp_libre -= diferencial;
}

void Cubo::agregar_nuevo_reg(const Reg& reg) {
	this->regs.push_back(reg);
	this->esp_libre -= reg.get_tam();
}

bool Cubo::eliminar_reg(int clave) {
	list < Reg > ::iterator it;

	it = this->regs.begin();
	while (it != this->regs.end() && (*it).get_clave() != clave)
		++ it;

	if ((*it).get_clave() == clave) {
		this->esp_libre += (*it).get_tam();
		this->regs.erase(it);
		return true;
	}
	return false;
}

bool Cubo::buscar_reg(int clave, Reg& reg) {
	list < Reg > ::iterator it;

	it = this->regs.begin();
	while (it != this->regs.end() && (*it).get_clave() != clave)
		++ it;

	if ((*it).get_clave() == clave) {
		reg = *it;
		return true;
	}
	return false;
}

void Cubo::vaciar() {
	this->tam_disp = 1;
	this->esp_libre = TAM_BLOQUE;
	this->regs.clear();
}

void Cubo::incorporar_regs(list < Reg > regs) {
	list < Reg > ::iterator it;
	for (it = regs.begin(); it != regs.end(); ++ it)
		this->agregar_nuevo_reg(*it);
}

void Cubo::serializar(char* buffer, unsigned int& offset) {
	Persistencia::PonerEnteroEnChar(buffer, offset, this->tam_disp);

	Persistencia::PonerEnteroEnChar(buffer, offset, this->regs.size());
	list < Reg > ::iterator it;
	for (it = this->regs.begin(); it != this->regs.end(); ++ it)
		(*it).serializar(buffer, offset);
}

void Cubo::hidratar(char* buffer, unsigned int& offset) {
	this->vaciar();

	this->tam_disp = Persistencia::getEnteroDesdeBuffer(buffer, offset);

	int tam_regs = Persistencia::getEnteroDesdeBuffer(buffer, offset);
	for (int i = 0; i < tam_regs; ++ i) {
		Reg reg;
		reg.hidratar(buffer, offset);
		this->agregar_nuevo_reg(reg);
	}
}

void Cubo::toString() {
	cout << " Bloque --> " << endl;
	cout << " Tamaño de dispersión:   " << this->tam_disp << endl;
	cout << " Cantidad de espacio libre:   " << this->esp_libre << endl;

	list < Reg > ::iterator it;
	for (it = this->regs.begin(); it != this->regs.end(); ++ it)
		(*it).toString();

}
