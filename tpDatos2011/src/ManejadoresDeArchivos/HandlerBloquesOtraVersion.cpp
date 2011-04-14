#include "HandlerBloquesOtraVersion.h"

HandlerBloquesOtraVersion::HandlerBloquesOtraVersion(const string& ruta_arch_bloques, const string& ruta_arch_esp_libre) :
	ruta_arch_bloques(ruta_arch_bloques), handler_esp_libre(ruta_arch_esp_libre) {}

void HandlerBloquesOtraVersion::set_ruta_arch_bloques(const string& ruta_arch_bloques) {
	this->ruta_arch_bloques = ruta_arch_bloques;
}

void HandlerBloquesOtraVersion::set_ruta_arch_esp_libre(const string& ruta_arch_esp_libre) {
	this->handler_esp_libre.set_ruta_arch_esp_libre(ruta_arch_esp_libre);
}

int HandlerBloquesOtraVersion::get_tam_arch_bloques() const {
	ifstream arch;
	int tam;

	arch.open(this->ruta_arch_bloques.c_str());
	arch.seekg(0, ios_base::end);
	tam = arch.tellg();
	arch.seekg(0, ios_base::beg);
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
char* HandlerBloquesOtraVersion::recuperar_bloque(int pos_arch_bloques) {
	ifstream arch;
	char* buffer = (char*)calloc(TAM_BUFFER, sizeof(int));

	arch.open(this->ruta_arch_bloques.c_str());
	arch.seekg(pos_arch_bloques * TAM_BLOQUE);
	arch.read(buffer, TAM_BUFFER);
	arch.close();
	return buffer;
}

int HandlerBloquesOtraVersion::guardar_bloque(char* buffer) {
	fstream arch;
	int pos_insercion;

	arch.open(this->ruta_arch_bloques.c_str(), ios_base::in | ios_base::out | ios_base::app);
	if (handler_esp_libre.hay_bloque_libre() == true) {
		pos_insercion = handler_esp_libre.get_pos_bloque_libre();
		arch.seekg(pos_insercion * TAM_BLOQUE);
		handler_esp_libre.actualizar_baja_bloque_libre();
	}
	else {
		arch.seekg(0, fstream::end);
		pos_insercion = arch.tellg() / TAM_BLOQUE;
	}

	arch.write(buffer, TAM_BUFFER);
	arch.flush();
	arch.close();

	return pos_insercion;
}

void HandlerBloquesOtraVersion::guardar_bloque(char* buffer, int pos_arch_bloques) {
	fstream arch;
	arch.open(this->ruta_arch_bloques.c_str(), ios_base::out | ios_base::in);
	arch.seekg(pos_arch_bloques * TAM_BLOQUE);
	arch.write(buffer, TAM_BUFFER);
	arch.flush();
	arch.close();

//	if (handler_esp_libre.ya_existe(pos_arch_bloques))
//		handler_esp_libre.actualizar_baja_bloque_libre();
}

bool HandlerBloquesOtraVersion::eliminar_bloque(int pos_arch_bloques) {
	if (this->get_tam_arch_bloques() / TAM_BLOQUE > pos_arch_bloques) {
		if (handler_esp_libre.ya_existe(pos_arch_bloques) == false)
			handler_esp_libre.actualizar_alta_bloque_libre(pos_arch_bloques);
		return true;
	}
	return false;
}
