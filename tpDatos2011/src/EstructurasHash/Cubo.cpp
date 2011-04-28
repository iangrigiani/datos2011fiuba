
#include "Cubo.h"

Cubo::Cubo(int tam_disp) : Bloque(tam_disp), esp_libre(TAM_BLOQUE) {}

bool Cubo::esta_vacio() const {
	if (this->esp_libre == TAM_BLOQUE)
		return true;
	return false;
}

bool Cubo::entra_en_bloque(const RegPalabra& reg) const {
	if (this->esp_libre > reg.get_tam())
		return true;
	return false;
}

bool Cubo::entra_en_bloque(list < int > & offsets) const {
	int tam = offsets.size() * sizeof(int);
	if (this->esp_libre > tam)
		return true;
	return false;
}

void Cubo::aumentar_esp_libre(int diferencial) {
	this->esp_libre += diferencial;
}

void Cubo::disminuir_esp_libre(int diferencial) {
	this->esp_libre -= diferencial;
}

void Cubo::agregar_nuevo_reg(const RegPalabra& reg) {
	this->regs.push_back(reg);
	this->esp_libre -= reg.get_tam();
}

bool Cubo::eliminar_reg(int clave) {
	list < RegPalabra > ::iterator it;

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

bool Cubo::existe_reg(int clave) {
	list < RegPalabra > ::iterator it;

	it = this->regs.begin();
	while (it != this->regs.end() && (*it).get_clave() != clave)
		++ it;

	if ((*it).get_clave() == clave) {
		return true;
	}
	return false;
}

RegPalabra& Cubo::buscar_reg(int clave) {
	list < RegPalabra > ::iterator it;

	it = this->regs.begin();
	while ((*it).get_clave() != clave)
		++ it;

	return (*it);
}

void Cubo::vaciar() {
	this->set_tam_disp(1);
	this->esp_libre = TAM_BLOQUE;
	this->regs.clear();
}

void Cubo::incorporar_regs(list < RegPalabra > & regs) {
	list < RegPalabra > ::iterator it;
	for (it = regs.begin(); it != regs.end(); ++ it)
		this->agregar_nuevo_reg(*it);
}

list < RegPalabra > Cubo::actualizar_regs(int num_bloque, HandlerTabla& handler) {
	list < RegPalabra > ::iterator it;
	list < RegPalabra > list_aux;
	RegPalabra reg_desact;
	unsigned int tam_regs;
	unsigned int contador = 0;

	tam_regs = this->regs.size();
	it = this->regs.begin();

	while (contador != tam_regs) {
		if (num_bloque != handler.get_num_bloque((*it).get_clave())) {
			reg_desact = *it;
			it = this->regs.erase(it);
			this->esp_libre += reg_desact.get_tam();
			list_aux.push_back(reg_desact);
		}
		else ++ it;
		++ contador;
	}

	return list_aux;
}

void Cubo::serializar(char* buffer, unsigned int& offset) {
	Persistencia::PonerEnteroEnChar(buffer, offset, this->get_tam_disp());

	Persistencia::PonerEnteroEnChar(buffer, offset, this->regs.size());
	list < RegPalabra > ::iterator it;
	for (it = this->regs.begin(); it != this->regs.end(); ++ it)
		(*it).serializar(buffer, offset);
}

void Cubo::hidratar(char* buffer, unsigned int& offset) {
	this->vaciar();

	this->set_tam_disp(Persistencia::getEnteroDesdeBuffer(buffer, offset));

	int tam_regs = Persistencia::getEnteroDesdeBuffer(buffer, offset);
	for (int i = 0; i < tam_regs; ++ i) {
		RegPalabra reg;
		reg.hidratar(buffer, offset);
		this->agregar_nuevo_reg(reg);
	}
}

void Cubo::toString() {
	cout << " Bloque --> " << endl;
	cout << " Tamaño de dispersión:   " << this->get_tam_disp() << endl;
	cout << " Cantidad de espacio libre:   " << this->esp_libre << endl;

	list < RegPalabra > ::iterator it;
	for (it = this->regs.begin(); it != this->regs.end(); ++ it)
		(*it).toString();

}
