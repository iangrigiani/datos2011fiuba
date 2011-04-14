#include "HandlerDeBloques.h"

HandlerDeBloques::HandlerDeBloques() {
}

HandlerDeBloques::HandlerDeBloques(string path){
	this->path = path;
	if (!ff.is_open()){
		ff.open(this->path.c_str(), std::ios_base::in | std::ios_base::out);
	}else{
		ff.close();
		ff.open(this->path.c_str() , std::ios_base::in | std::ios_base::out);
	}
}

void HandlerDeBloques::guardar_bloque(char* buffer, int nro_bloque){
	int offset_bloque = nro_bloque * TAMANIO_BUFFER;
// Manejo sobre el archivo de bloques
	stringstream ss;
	ss << buffer << "\n";
	string str = ss.str();
	// Escribo libro en el archivo de bloques
	ff.seekg(offset_bloque);
	ff.write(str.c_str(), str.length());
}

char* HandlerDeBloques::recuperar_bloque(int nro_bloque)
{
	char * bloqueARetornoar = (char*)calloc(TAMANIO_BUFFER, sizeof(char));
	int offset_bloque = nro_bloque * TAMANIO_BUFFER;
	// Me posiciono en el archivo de RLV
	ff.seekg(offset_bloque);
	ff.read(bloqueARetornoar, TAMANIO_BUFFER);
	string cad = bloqueARetornoar;
	return ((char*)cad.c_str());
}

int HandlerDeBloques::get_tam_arch_bloques(){
	ff.seekg(0, ios_base::beg);
	ff.seekg(0, ios_base::end);
	int tamanio = ff.tellg();
	ff.seekg(0, ios_base::beg);
	return tamanio;
}

void HandlerDeBloques::eliminar_bloque(int nro_Bloque){
// Abro el archivo y me posiciono para obtener los datos
	int offset_bloque = nro_Bloque * TAMANIO_BUFFER;
	char * bloqueABorrar = (char*)calloc(TAMANIO_BUFFER, sizeof(char));
	ff.seekg(offset_bloque);
	ostringstream oss;
	free(bloqueABorrar);
	oss << bloqueABorrar << "\n" ;
	string borrar = oss.str();
	ff.write(borrar.c_str(), borrar.length());
	ff.flush();
}
