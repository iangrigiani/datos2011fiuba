#include "HandlerDeBloques.h"

HandlerDeBloques::HandlerDeBloques() {
}

HandlerDeBloques::HandlerDeBloques(string path){
	fstream ff ;
	this->path = path;
}

void HandlerDeBloques::guardar_bloque(char* buffer, int nro_bloque){
	fstream ff;
	ff.open(this->path.c_str(), fstream::in | fstream::out);
	if (ff.is_open()){
		int offset_bloque = nro_bloque * TAMANIO_BUFFER;
		// Manejo sobre el archivo de bloques
		stringstream ss;
		ss << buffer << "\n";
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

char* HandlerDeBloques::recuperar_bloque(int nro_bloque){
	fstream ff;
	ff.open(this->path.c_str(), fstream::in);
	if (ff.is_open()){
		char * bloqueARetornoar = (char*)calloc(TAMANIO_BUFFER, sizeof(char));
		int offset_bloque = nro_bloque * TAMANIO_BUFFER;
		// Me posiciono en el archivo de RLV
		ff.seekg(offset_bloque);
		ff.read(bloqueARetornoar, TAMANIO_BUFFER);
		ff.close();
		string cad = bloqueARetornoar;
		return ((char*)cad.c_str());
	}else{
		cout << "No se pudo abrir el archivo para recuperar bloque" << endl;
		return NULL;
	}
}

int HandlerDeBloques::get_tam_arch_bloques(){
	fstream ff;
	ff.open(this->path.c_str(), fstream::in);
	if (ff.is_open()){
		ff.seekg(0, ios_base::beg);
		ff.seekg(0, ios_base::end);
		int tamanio = ff.tellg();
		ff.seekg(0, ios_base::beg);
		ff.close();
		return tamanio;

	}else{
		cout << "No se pudo abrir el archivo para obtener su tamaño" << endl;
		return ERROR;
	}
}

void HandlerDeBloques::eliminar_bloque(int nro_Bloque){
	fstream ff;
	// Abro el archivo y me posiciono para obtener los datos
	ff.open(this->path.c_str(), fstream::in | fstream::out);
	if (ff.is_open()){
		int offset_bloque = nro_Bloque * TAMANIO_BUFFER;
		char * bloqueABorrar = (char*)calloc(TAMANIO_BUFFER, sizeof(char));
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
