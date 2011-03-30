#include "ActualizadorArchivoRegLongVariable.h"

ActualizadorArchivoRegLongVariable::ActualizadorArchivoRegLongVariable() {
	// TODO Auto-generated constructor stub

}
ActualizadorArchivoRegLongVariable::ActualizadorArchivoRegLongVariable(string pathLibro) {
	this->pathLibro = pathLibro;

}
ActualizadorArchivoRegLongVariable::~ActualizadorArchivoRegLongVariable() {
	// TODO Auto-generated destructor stub
}
int ActualizadorArchivoRegLongVariable::actualizarLibro(){
	// Archivo que contiene el libro que quiero guardar
	FILE* fin;
	// Archivo de registrso de longitud variable
	FILE* fout;

	if (((fin = fopen(this->pathLibro.c_str(),"rt")) == NULL) && ((fout = fopen(PATH_REG_LONG_VARIABLE,"a+")) == NULL)){
		cout << "Error al abrir un archivo";
		return ERROR;
	}

	fseek(fin, 0, SEEK_END);
	// buffer donde tendré mi libro
	char* libro;
	// Obtengo el tamaño del libro (offset)
	int tamanio = ftell(fin);
	fseek(fin, 0, SEEK_SET);
	fread(libro,tamanio,1,fin);
	fclose(fin);

	// Genero el estado como procesado
	int flag_estado = 1;

	// TODO generar el ID de archivo e ir llevando el control de esto en algun lado
	int id_Archivo;

	// Grabo en mi archivo de registros de longitud variable en modo append mi libro y sus datos de control.
	fwrite(libro,tamanio,1,fout);

	return OK;
	fclose(fout);
	fclose(fin);

}
