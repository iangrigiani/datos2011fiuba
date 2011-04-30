#include "HandlerBloques.h"

HandlerBloques::HandlerBloques() : tam_bloque(-1) {}



HandlerBloques::HandlerBloques(int tam_bloque, const string& ruta_arch_bloques,
		const HandlerEspLibre& handler_esp_libre) :
	tam_bloque(tam_bloque), ruta_arch_bloques(ruta_arch_bloques), handler_esp_libre(handler_esp_libre) {}


HandlerBloques::HandlerBloques(int tam_bloque, const string& ruta_arch_bloques){
	this->tam_bloque = tam_bloque;
	this->ruta_arch_bloques = ruta_arch_bloques;
}

HandlerBloques::HandlerBloques(int tam_bloque){
	this->tam_bloque = tam_bloque;
}

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

char* HandlerBloques::recuperar_bloque_arbol(int nro_bloque){
	fstream ff;
	ff.open(this->ruta_arch_bloques.c_str(), fstream::in);
	if (ff.is_open()){
		char * bloqueARetornoar = (char*)calloc(this->tam_bloque, sizeof(char));
		int offset_bloque = nro_bloque * this->tam_bloque;
		// Me posiciono en el archivo de bloques
		ff.seekg(offset_bloque);
		ff.read(bloqueARetornoar, this->tam_bloque);
		ff.close();
		return bloqueARetornoar;
	}else{
		cout << "No se pudo abrir el archivo para recuperar bloque" << endl;
		return NULL;
	}
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

void HandlerBloques::guardar_bloque_arbol(char* buffer, int nro_bloque){
	fstream ff;
	ff.open(this->ruta_arch_bloques.c_str(), fstream::in | fstream::out);
	if (ff.is_open()){
		int offset_bloque = nro_bloque * this->tam_bloque;
		// Manejo sobre el archivo de bloques
		stringstream ss;
		ss << buffer;
		string str = ss.str();
		// Escribo libro en el archivo de bloques
		ff.seekg(offset_bloque);
		ff.write(str.c_str(), str.length());
		ff.flush();
		ff.close();
	}else{
		cout << "No se pudo abrir el archivo para guardar bloque" << endl;
	}
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

void HandlerBloques::eliminar_bloque_arbol(int nro_Bloque){
	fstream ff;
	// Abro el archivo y me posiciono para obtener los datos
	ff.open(this->ruta_arch_bloques.c_str(), fstream::in | fstream::out);
	if (ff.is_open()){
		int offset_bloque = nro_Bloque * this->tam_bloque;
		char * bloqueABorrar = (char*)calloc(this->tam_bloque, sizeof(char));
		ff.seekg(offset_bloque);
		ostringstream oss;
		free(bloqueABorrar);
		oss << bloqueABorrar << "\n" ;
		string borrar = oss.str();
		ff.write(borrar.c_str(), borrar.length());
		ff.flush();
		ff.close();
	}else{
		cout << "No se pudo abrir el archivo para eliminar bloque" << endl;
	}
}
