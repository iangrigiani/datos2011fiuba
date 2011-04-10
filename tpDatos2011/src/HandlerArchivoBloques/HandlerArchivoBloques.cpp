/*
 * HandlerArchivoBloques.cpp
 *
 *  Created on: 04/04/2011
 *      Author: angeles
 */

#include "HandlerArchivoBloques.h"

HandlerArchivoBloques::HandlerArchivoBloques(const string& ruta_arch_bloques, const string& ruta_arch_esp_libre) :
	ruta_arch_bloques(ruta_arch_bloques), handler_esp_libre(ruta_arch_esp_libre) {}

void HandlerArchivoBloques::set_ruta_arch_bloques(const string& ruta_arch_bloques) {
	this->ruta_arch_bloques = ruta_arch_bloques;
}

void HandlerArchivoBloques::set_ruta_arch_esp_libre(const string& ruta_arch_esp_libre) {
	this->handler_esp_libre.set_ruta_arch_esp_libre(ruta_arch_esp_libre);
}

int HandlerArchivoBloques::get_tam_arch_bloques() const {
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
void HandlerArchivoBloques::recuperar_bloque(Bloq& bloque, int pos_arch_bloques) {
	fstream arch;
	unsigned int offset = 0;
	char buffer[TAM_BUFFER];

	arch.open(this->ruta_arch_bloques.c_str(), fstream::in);
	arch.seekp(pos_arch_bloques * TAM_BLOQUE);
	arch.read(buffer, TAM_BUFFER);
	arch.close();

	bloque.hidratar(buffer, offset);
}

int HandlerArchivoBloques::guardar_bloque(Bloq& bloque) {
	fstream arch;
	int pos_insercion;
	unsigned int offset = 0;
	char buffer[TAM_BUFFER];

	bloque.serializar(buffer, offset);

	arch.open(this->ruta_arch_bloques.c_str(), fstream::out | fstream::in);
	if (handler_esp_libre.hay_bloque_libre() == true) {
		pos_insercion = handler_esp_libre.get_pos_bloque_libre();
		arch.seekp(pos_insercion * TAM_BLOQUE);
		handler_esp_libre.actualizar_baja_bloque_libre();
	}
	else {
		arch.seekg(0, fstream::end);
		pos_insercion = arch.tellg() / TAM_BLOQUE;
	}

	arch.write(buffer, TAM_BUFFER);
	arch.close();

	return pos_insercion;
}

void HandlerArchivoBloques::guardar_bloque(Bloq& bloque, int pos_arch_bloques) {
	fstream arch;
	unsigned int offset = 0;
	char buffer[TAM_BUFFER];

	bloque.serializar(buffer, offset);

	arch.open(this->ruta_arch_bloques.c_str(), fstream::out);
	arch.seekp(pos_arch_bloques * TAM_BLOQUE);
	arch.write(buffer, TAM_BUFFER);
	arch.close();

	if (handler_esp_libre.ya_existe(pos_arch_bloques))
		handler_esp_libre.actualizar_baja_bloque_libre();
}

bool HandlerArchivoBloques::eliminar_bloque(int pos_arch_bloques) {
	if (this->get_tam_arch_bloques() / TAM_BLOQUE > pos_arch_bloques) {
		if (handler_esp_libre.ya_existe(pos_arch_bloques) == false)
			handler_esp_libre.actualizar_alta_bloque_libre(pos_arch_bloques);
		return true;
	}
	return false;
}
