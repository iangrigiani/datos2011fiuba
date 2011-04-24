#include "HandlerBloques.h"

HandlerBloques::HandlerBloques() : tam_bloque(-1) {}

HandlerBloques::HandlerBloques(int tam_bloque, const string& ruta_arch_bloques,
		const HandlerEspLibre& handler_esp_libre) :
	tam_bloque(tam_bloque), ruta_arch_bloques(ruta_arch_bloques), handler_esp_libre(handler_esp_libre) {}

void HandlerBloques::set_tam_bloque(int tam_bloque) {
	this->tam_bloque = tam_bloque;
}

void HandlerBloques::set_ruta_arch_bloques(const string& ruta_arch_bloques) {
	this->ruta_arch_bloques = ruta_arch_bloques;
}

void HandlerBloques::set_handler_esp_libre(const HandlerEspLibre& handler_esp_libre) {
	this->handler_esp_libre = handler_esp_libre;
}

int HandlerBloques::get_tam_arch_bloques() const {
	fstream arch;
	int tam;

	arch.open(this->ruta_arch_bloques.c_str(), fstream::in);
	arch.seekg(0, fstream::end);
	tam = arch.tellg();
	arch.close();

	return tam;
}
/*
int HandlerArchivoBloques::get_pos_insercion() const {
	if (this->hay_bloque_libre() == true)
		return this->get_pos_bloque_libre();
	else return (this->get_tam_arch_bloques() / TAM_BLOQUE);
}
*/
void HandlerBloques::recuperar_bloque(char* buffer, int pos_arch_bloques) {
	fstream arch;

	arch.open(this->ruta_arch_bloques.c_str(), fstream::in);
	arch.seekg(pos_arch_bloques * this->tam_bloque);
	arch.read(buffer, this->tam_bloque);
	arch.close();
}

int HandlerBloques::guardar_bloque(char* buffer) {
	fstream arch;
	int pos_insercion;

	arch.open(this->ruta_arch_bloques.c_str(), fstream::out | fstream::in);
	if (this->handler_esp_libre.hay_bloque_libre() == true) {
		pos_insercion = this->handler_esp_libre.get_pos_bloque_libre();
		arch.seekg(pos_insercion * this->tam_bloque);
		this->handler_esp_libre.actualizar_baja_bloque_libre();
	}
	else {
		arch.seekg(0, fstream::end);
		pos_insercion = arch.tellg() / this->tam_bloque;
	}

	arch.write(buffer, this->tam_bloque);
	arch.close();

	return pos_insercion;
}

void HandlerBloques::guardar_bloque(char* buffer, int pos_arch_bloques) {
	fstream arch;

	arch.open(this->ruta_arch_bloques.c_str(), fstream::out | fstream::in);
	arch.seekg(pos_arch_bloques * this->tam_bloque);
	arch.write(buffer, this->tam_bloque);
	arch.close();
}

bool HandlerBloques::eliminar_bloque(int pos_arch_bloques) {
	if (this->get_tam_arch_bloques() / this->tam_bloque > pos_arch_bloques) {
		this->handler_esp_libre.actualizar_alta_bloque_libre(pos_arch_bloques);
		return true;
	}
	return false;
}
