/*
 * HandlerArchivoBloques.cpp
 *
 *  Created on: 04/04/2011
 *      Author: angeles
 */

#include "HandlerArchivoBloques.h"

HandlerArchivoBloques::HandlerArchivoBloques(const string& ruta_arch_bloques, const string& ruta_arch_esp_libres) :
	ruta_arch_bloques(ruta_arch_bloques), ruta_arch_esp_libres(ruta_arch_esp_libres) {}

int HandlerArchivoBloques::get_pos_bloque_libre() const {
	ifstream arch;
	int pos_bloque_libre;

	arch.open(this->ruta_arch_esp_libres.c_str());
	arch >> pos_bloque_libre;
	arch.close();

	return pos_bloque_libre;
}

bool HandlerArchivoBloques::hay_bloque_libre() const {
	if (this->get_pos_bloque_libre() != -1)
		return true;
	return false;
}

bool HandlerArchivoBloques::ya_existe(int pos_bloque_libre) const {
	ifstream arch;
	int pos_bloque_libre_aux;

	arch.open(this->ruta_arch_esp_libres.c_str());

	arch >> pos_bloque_libre_aux;
	while (pos_bloque_libre_aux != -1 && pos_bloque_libre_aux != pos_bloque_libre)
		arch >> pos_bloque_libre_aux;

	arch.close();

	if (pos_bloque_libre_aux == pos_bloque_libre)
		return true;
	return false;
}

void HandlerArchivoBloques::actualizar_baja_bloque_libre() {
	ifstream arch;
	ofstream arch_aux;
	int pos_bloque_libre;

	arch.open(this->ruta_arch_esp_libres.c_str());
	arch_aux.open(NOM_ARCH_TEMP);

	for(int i = 0; i < 2; ++ i)
		arch >> pos_bloque_libre;
	while (pos_bloque_libre != -1) {
		arch_aux << pos_bloque_libre << ' ';
		arch >> pos_bloque_libre;
	}
	arch_aux << pos_bloque_libre << ' ';

	arch.close();
	arch_aux.close();

	remove(this->ruta_arch_esp_libres.c_str());
	rename(NOM_ARCH_TEMP, this->ruta_arch_esp_libres.c_str());
}

void HandlerArchivoBloques::actualizar_alta_bloque_libre(int pos_nuevo_bloque_libre) {
	fstream arch;
	long pos;
	int pos_bloque_libre;

	arch.open(this->ruta_arch_esp_libres.c_str(), fstream::in | fstream::out);

	pos = arch.tellp();
	arch >> pos_bloque_libre;

	while (pos_bloque_libre != -1) {
		pos = arch.tellp();
		arch >> pos_bloque_libre;
	}

	arch.seekp(pos);
	arch << ' ' << pos_nuevo_bloque_libre << ' ' << pos_bloque_libre << ' ';

	arch.close();
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

Bloq HandlerArchivoBloques::recuperar_bloque(int pos_arch_bloques) {
	fstream arch;
	unsigned int offset = 0;
	char buffer[TAM_BUFFER];

	arch.open(this->ruta_arch_bloques.c_str(), fstream::in);
	arch.seekp(pos_arch_bloques * TAM_BLOQUE);
	arch.read(buffer, TAM_BUFFER);
	arch.close();

	Bloq bloque;
	bloque.hidratar(buffer, offset);

	return bloque;
}

void HandlerArchivoBloques::guardar_bloque(Bloq& bloque) {
	fstream arch;
	unsigned int offset = 0;
	char buffer[TAM_BUFFER];

	bloque.serializar(buffer, offset);

	arch.open(this->ruta_arch_bloques.c_str(), fstream::out | fstream::in);
	if (this->hay_bloque_libre() == true) {
		arch.seekp(this->get_pos_bloque_libre() * TAM_BLOQUE);
		this->actualizar_baja_bloque_libre();
	}
	else arch.seekg(0, fstream::end);
	arch.write(buffer, TAM_BUFFER);
	arch.close();
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

	if (this->ya_existe(pos_arch_bloques))
		this->actualizar_baja_bloque_libre();
}

bool HandlerArchivoBloques::eliminar_bloque(int pos_arch_bloques) {
	if (this->get_tam_arch_bloques() / TAM_BLOQUE > pos_arch_bloques) {
		if (this->ya_existe(pos_arch_bloques) == false)
			this->actualizar_alta_bloque_libre(pos_arch_bloques);
		return true;
	}
	return false;
}
