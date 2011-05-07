
#include "Cubo.h"

Cubo::Cubo(int tam_disp) : Bloque(tam_disp) {

	this->calcular_esp_libre(tam_disp,this->regs.size(),this->esp_libre);

}

int Cubo::calcular_esp_libre(int tam_dip,int tam_regs,int& espLibre)
{
	int tam = 0;

	stringstream ss1;
	ss1 << tam_dip << ' ';
	string s = ss1.str();
	tam += s.size();
	s.clear();

	stringstream ss2;
	ss2 << tam_regs << ' ';
	s = ss2.str();
	tam += s.size();
	s.clear();

	espLibre= TAM_CUBO - tam;

	tam = 0;

	stringstream ss3;
	ss3 << espLibre << ' ';
	s = ss3.str();
	tam += s.size();
	s.clear();

	espLibre -= tam;

	return tam;
}

bool Cubo::esta_vacio(){

	int a = 0;
	int tam = this->calcular_esp_libre(this->get_tam_disp(),0,a);
	if (this->esp_libre == (TAM_CUBO - tam))
		return true;
	return false;
}

bool Cubo::entra_en_bloque(RegPalabra& reg) const {
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

void Cubo::aumentar_esp_libre(int offset) {

	int tam = 0;

	stringstream ss1;
	ss1 << offset << ' ';
	string s(ss1.str());
	tam += s.size();
	s.clear();

	this->esp_libre += tam;
}

void Cubo::disminuir_esp_libre(list<int> offsets) {

	int tam = 0;

	list < int > ::iterator it;
	for(it = offsets.begin(); it!=offsets.end();++it)
	{
		stringstream ss1;
		ss1 << *it << ' ';
		string s(ss1.str());
		tam += s.size();
		s.clear();
	}

	this->esp_libre -= tam;
}

void Cubo::agregar_nuevo_reg(RegPalabra& reg) {
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
	this->esp_libre = TAM_CUBO - sizeof(int);
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
	Persistencia::PonerEnteroEnChar(buffer, offset, this->esp_libre);

	Persistencia::PonerEnteroEnChar(buffer, offset, this->regs.size());
	list < RegPalabra > ::iterator it;
	for (it = this->regs.begin(); it != this->regs.end(); ++ it)
		(*it).serializar(buffer, offset);
}

void Cubo::hidratar(char* buffer, unsigned int& offset) {
	this->vaciar();

	this->set_tam_disp(Persistencia::getEnteroDesdeBuffer(buffer, offset));
	this->esp_libre = Persistencia::getEnteroDesdeBuffer(buffer,offset);

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
