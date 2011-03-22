#include "Bloque.h"

Bloque::Bloque() {
	this->espacioLibre = TAMANIO_BUFFER;
}

bool Bloque::agregarRegistro(Registro * reg){
	bool retorno = false;
	if (tieneEspacio(reg->getTamanio())){
		retorno = true;
		this->registros.push_back(reg);
		espacioLibre -= reg->getTamanio();
	}	
	return retorno;
}

bool Bloque::tieneEspacio(int size){
	if (espacioLibre > size){
		return true;
	}
	return false;
}

Registro * Bloque::getRegistro(ClaveNumerica * clave){
	std::list<Registro*>::iterator it = this->registros.begin();
	bool encontrado = false;
	Registro * regRetornado = NULL;
	while (it != this->registros.end() && !encontrado){
		if ((*it)->getClave()->igual(clave)){
			encontrado = true;
			regRetornado = (*it);
		}
		it++;
	}
	return regRetornado;
}

Registro* Bloque::getSiguienteRegistro(ClaveNumerica * clave, ClaveNumerica * claveNumerica){
	std::list<Registro*>::iterator it = this->registros.begin();
	bool encontrado = false;
	Registro * regRetornado = NULL;
	while (it != this->registros.end() && !encontrado){
		if ((*it)->getClave()->igual(clave) && claveNumerica->esMenor((*it)->getClave())){
			encontrado = true;
			regRetornado = (*it);
		}
		it++;
	}
	return regRetornado;
}



void Bloque::limpiar(){
	this->espacioLibre = TAMANIO_BUFFER;
	this->registros.clear();
}

void Bloque::serializar(char * buffer, unsigned int &offset){
	Persistencia::PonerEnteroEnChar(buffer, offset, this->registros.size());
	std::list<Registro*>::iterator it = this->registros.begin();
	while (it != this->registros.end()){
		(*it)->serializar(buffer, offset);
		it++;
	}
}

void Bloque::hidratar(char * buffer, unsigned int &offset){
	int cantidadRegistros = Persistencia::getEnteroDesdeBuffer(buffer, offset);
	int contador = 0;
	while (contador < cantidadRegistros){
		Registro * reg = new Registro();
		reg->hidratar(buffer, offset);
		this->agregarRegistro(reg);
		contador++;
	}
}
void Bloque::toString(){
	std::list<Registro*>::iterator it = this->registros.begin();
	while (it != this->registros.end()){
		(*it)->toString();
		++it;
	}
}
Bloque::~Bloque() {
	std::list<Registro*>::iterator it = this->registros.begin();
	while (it != this->registros.end()){
		delete (*it);
		it++;
	}
}
