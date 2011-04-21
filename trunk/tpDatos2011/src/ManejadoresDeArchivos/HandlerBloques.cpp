#include "HandlerBloques.h"

HandlerBloques::HandlerBloques(const string& ruta_arch_bloques, const HandlerEspLibre& handler_esp_libre) :
	ruta_arch_bloques(ruta_arch_bloques), handler_esp_libre(handler_esp_libre) {}

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
void HandlerBloques::recuperar_bloque(Cubo& bloque, int pos_arch_bloques) {
	fstream arch;
	unsigned int offset = 0;
	char buffer[TAM_BUFFER];

	arch.open(this->ruta_arch_bloques.c_str(), fstream::in);
	arch.seekg(pos_arch_bloques * TAM_BLOQUE);
	arch.read(buffer, TAM_BUFFER);
	arch.close();

	bloque.hidratar(buffer, offset);
}

int HandlerBloques::guardar_bloque(Cubo& bloque) {
	fstream arch;
	int pos_insercion;
	unsigned int offset = 0;
	char buffer[TAM_BUFFER];

	bloque.serializar(buffer, offset);

	arch.open(this->ruta_arch_bloques.c_str(), fstream::out | fstream::in);
	if (this->handler_esp_libre.hay_bloque_libre() == true) {
		pos_insercion = this->handler_esp_libre.get_pos_bloque_libre();
		arch.seekg(pos_insercion * TAM_BLOQUE);
		this->handler_esp_libre.actualizar_baja_bloque_libre();
	}
	else {
		arch.seekg(0, fstream::end);
		pos_insercion = arch.tellg() / TAM_BLOQUE;
	}

	arch.write(buffer, TAM_BUFFER);
	arch.close();

	return pos_insercion;
}

void HandlerBloques::guardar_bloque(Cubo& bloque, int pos_arch_bloques) {
	fstream arch;
	unsigned int offset = 0;
	char buffer[TAM_BUFFER];

	bloque.serializar(buffer, offset);

	arch.open(this->ruta_arch_bloques.c_str(), fstream::out | fstream::in);
	arch.seekg(pos_arch_bloques * TAM_BLOQUE);
	arch.write(buffer, TAM_BUFFER);
	arch.close();
}

bool HandlerBloques::eliminar_bloque(int pos_arch_bloques) {
	if (this->get_tam_arch_bloques() / TAM_BLOQUE > pos_arch_bloques) {
		this->handler_esp_libre.actualizar_alta_bloque_libre(pos_arch_bloques);
		return true;
	}
	return false;
}
