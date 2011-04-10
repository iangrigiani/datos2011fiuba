/*
 * HandlerArchivoEspLibres.cpp
 *
 *  Created on: 09/04/2011
 *      Author: angeles
 */

#include "HandlerArchivoEspLibre.h"

HandlerArchivoEspLibre::HandlerArchivoEspLibre(const string& ruta_arch_esp_libre) :
		ruta_arch_esp_libre(ruta_arch_esp_libre) {}

void HandlerArchivoEspLibre::set_ruta_arch_esp_libre(const string& ruta_arch_esp_libre) {
	this->ruta_arch_esp_libre = ruta_arch_esp_libre;
}

int HandlerArchivoEspLibre::get_pos_bloque_libre() const {
	ifstream arch;
	int pos_bloque_libre;

	arch.open(this->ruta_arch_esp_libre.c_str());
	arch >> pos_bloque_libre;
	arch.close();

	return pos_bloque_libre;
}

bool HandlerArchivoEspLibre::hay_bloque_libre() const {
	if (this->get_pos_bloque_libre() != -1)
		return true;
	return false;
}

bool HandlerArchivoEspLibre::ya_existe(int pos_bloque_libre) const {
	ifstream arch;
	int pos_bloque_libre_aux;

	arch.open(this->ruta_arch_esp_libre.c_str());

	arch >> pos_bloque_libre_aux;
	while (pos_bloque_libre_aux != -1 && pos_bloque_libre_aux != pos_bloque_libre)
		arch >> pos_bloque_libre_aux;

	arch.close();

	if (pos_bloque_libre_aux == pos_bloque_libre)
		return true;
	return false;
}

void HandlerArchivoEspLibre::actualizar_baja_bloque_libre() {
	ifstream arch;
	ofstream arch_aux;
	int pos_bloque_libre;

	arch.open(this->ruta_arch_esp_libre.c_str());
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

	remove(this->ruta_arch_esp_libre.c_str());
	rename(NOM_ARCH_TEMP, this->ruta_arch_esp_libre.c_str());
}

void HandlerArchivoEspLibre::actualizar_alta_bloque_libre(int pos_nuevo_bloque_libre) {
	fstream arch;
	long pos;
	int pos_bloque_libre;

	arch.open(this->ruta_arch_esp_libre.c_str(), fstream::in | fstream::out);

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
