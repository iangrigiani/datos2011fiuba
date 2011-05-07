
#include "Cubo.h"

Cubo::Cubo(int tam_disp) : tam_disp(tam_disp) {
	this->esp_libre = TAM_CUBO - 6;

//	stringstream ss1;
//	ss1 << this->tam_disp << ' ';
//	string s(ss1.str());
//	this->esp_libre -= s.size();
//	s.clear();
//
//	stringstream ss2;
//	ss2 << this->regs.size() << ' ';
//	s = ss2.str();
//	this->esp_libre -= s.size();
//	s.clear();
}

bool Cubo::esta_vacio() const {
	if (this->esp_libre == (TAM_CUBO - sizeof(this->tam_disp)))
		return true;
	return false;
}

bool Cubo::entra_en_bloque(RegIndice& reg) const {
	if (this->esp_libre > reg.get_tam())
		return true;
	return false;
}

bool Cubo::entra_en_bloque(const string& cadena, const list < int > & offsets) const {
	int tam = strlen(cadena.c_str()) * sizeof(char) + sizeof(char) + offsets.size() * (sizeof(int) + sizeof(' '));
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

void Cubo::agregar_nuevo_reg(RegIndice& reg) {
	this->regs.push_back(reg);
	this->esp_libre -= reg.get_tam();
}

bool Cubo::eliminar_reg(int clave) {
	list < RegIndice > ::iterator it;

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
	list < RegIndice > ::iterator it;

	it = this->regs.begin();
	while (it != this->regs.end() && (*it).get_clave() != clave)
		++ it;

	if (it != this->regs.end())
		if ((*it).get_clave() == clave)
			return true;
	return false;
}
/*
RegIndice& Cubo::buscar_reg(int clave) {
	list < RegIndice > ::iterator it;

	it = this->regs.begin();
	while ((*it).get_clave() != clave)
		++ it;

	return (*it);
}
*/
RegIndice& Cubo::buscar_reg(int clave) {
	list < RegIndice > ::iterator it;

	it = this->regs.begin();
	while ((*it).get_clave() != clave)
		++ it;

	if (it == this->regs.end())
		return (*this->regs.begin());

	return (*it);
}

void Cubo::vaciar() {
	this->tam_disp = 1;
	this->esp_libre = TAM_CUBO - sizeof(int);
	this->regs.clear();
}

void Cubo::incorporar_regs(list < RegIndice > & regs) {
	list < RegIndice > ::iterator it;
	for (it = regs.begin(); it != regs.end(); ++ it)
		this->agregar_nuevo_reg(*it);
}

list < RegIndice > Cubo::actualizar_regs(int num_bloque, HandlerTabla& handler) {
	list < RegIndice > ::iterator it;
	list < RegIndice > list_aux;
	RegIndice reg_desact;
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
	Persistencia::PonerEnteroEnChar(buffer, offset, this->tam_disp);

	Persistencia::PonerEnteroEnChar(buffer, offset, this->regs.size());
	list < RegIndice > ::iterator it;
	for (it = this->regs.begin(); it != this->regs.end(); ++ it)
		(*it).serializar(buffer, offset);
}

void Cubo::hidratar(char* buffer, unsigned int& offset) {
	this->vaciar();

	this->tam_disp = Persistencia::getEnteroDesdeBuffer(buffer, offset);

	int tam_regs = Persistencia::getEnteroDesdeBuffer(buffer, offset);
	for (int i = 0; i < tam_regs; ++ i) {
		RegIndice reg;
		reg.hidratar(buffer, offset);
		this->agregar_nuevo_reg(reg);
	}
}

void Cubo::toString() {
	cout << " Bloque --> " << endl;
	cout << " Tamaño de dispersión:   " << this->tam_disp << endl;
	cout << " Cantidad de espacio libre:   " << this->esp_libre << endl;

	list < RegIndice > ::iterator it;
	for (it = this->regs.begin(); it != this->regs.end(); ++ it)
		(*it).toString();
}
