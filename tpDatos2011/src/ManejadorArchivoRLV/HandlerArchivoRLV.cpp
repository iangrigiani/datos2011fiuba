#include "HandlerArchivoRLV.h"


int HandlerArchivoRLV::obtenerTamanioLibro(char * cadenaDeDatos)
{
	char * caracterProcesado;
	int tamanioLibro;
	strtok(cadenaDeDatos,"|");

	//Busco donde se que se encuentra el campo asociado al tamanio del libro
	caracterProcesado = strtok(NULL,"|");
	tamanioLibro = atoi(caracterProcesado);
	return tamanioLibro;
}


/*
 *  TODO LEE DESDE EL DISCO EL CAMPO QUE GUARDA EL ULTIMO ID GENERADO
 *	Debe usarse cuando se abre el archivo para insertar un nuevo registro
 */
void HandlerArchivoRLV::recuperarUltimoID(){

	std::ifstream archivoMaestro;
	char  cadenaDeDatos[100];
	int ultimoIDPersistido;

	// Abro el archivo y obtengo la primer linea
	archivoMaestro.open(PATH_REG_LONG_VARIABLE, std::ios_base::in);
	archivoMaestro.get(cadenaDeDatos,100);
	string cad = cadenaDeDatos;
	int longitudCadena = cad.length();

	// si tiene datos busco el ultimo ID persistido
	if (longitudCadena > 0 ){
		ultimoIDPersistido = obtenerUltimoIDPersistido(cadenaDeDatos);
	}
	else{
		ultimoIDPersistido = 0 ;
	}
	cad.clear();

	this->ultimoID = ultimoIDPersistido;
	archivoMaestro.close();
}


/*
 *Devuelve el ultimo ID persistido en el archivo maestro en formato int
 */
int HandlerArchivoRLV::obtenerUltimoIDPersistido(char * cadenaDeDatos){

	char * caracterProcesado;
	int UltimoIDPersistido;
	strtok(cadenaDeDatos,"|");
	//Obtengo el la cadena con el ultimo ID, lo transformo a int y los devuelvo
	caracterProcesado = strtok(NULL,"|");
	UltimoIDPersistido = atoi(caracterProcesado);
	return UltimoIDPersistido;
}


HandlerArchivoRLV::HandlerArchivoRLV() {
    recuperarUltimoID();

}

int HandlerArchivoRLV::insertarLibro(const string& path_nuevo_libro)
{
// Manejo sobre el archivo del libro a ingresar
	std::ifstream f_ent;
	f_ent.open(path_nuevo_libro.c_str(), std::ios_base::in);
	f_ent.seekg(0,std::ios_base::end);
	// Obtengo tamanio de libro
	int size = f_ent.tellg();
	f_ent.seekg(0);
	char* buffer = (char*) calloc (size-1 , sizeof(char));

// Obtengo ID del ultimo libro ingresado
	int id_Archivo = this->ultimoID + 1;
    this->ultimoID = id_Archivo;

// Manejo sobre el archivo de RLV
	f_ent.read(buffer, size);
	int indexado = 0;
	int procesado = 1;
	std::ofstream f_dst;
	f_dst.open(PATH_REG_LONG_VARIABLE, std::ios_base::app);
	stringstream ss;
	// Armo los datos de entrada para ese libro
	ss << id_Archivo << "|" << size << "|" << procesado << "|" << indexado << "|" << "\n" << buffer << "\n";
	string str = ss.str();
	// Escribo libro en el archivo de RLV
	f_dst.write(str.c_str(), str.length());
	f_dst.close();
	f_ent.close();
	free(buffer);


/*
 *  TODO ESTE RETURN ESTA MAL, ESTE METODO DEBERIA RETORNAR EL OFFSET EN DONDE
 *  SE GUARDO EL LIBRO, ASI PONGO ESE OFFSET EN EL ARBOL Y EN EL HASING Y LUEGO
 *  PUEDO BUSCAR ESTE LIBRO EN EL ARCHIVO DE RLV
 */
	return OK;
}


/*
 * Devuelve un puntero a una cadena de char que contiene todo el libro
 */
char* HandlerArchivoRLV::buscarLibro(int offset)
{
	std::ifstream archivoMaestro;
	char  cadenaDeDatos[100];
	archivoMaestro.open(PATH_REG_LONG_VARIABLE, std::ios_base::in);
	archivoMaestro.seekg(offset);

	//Obtengo la linea correspondiente al libro en la que se tiene la información de tamanio
	archivoMaestro.get(cadenaDeDatos,100);
	string cad = cadenaDeDatos;
	int longitudCadena = cad.length();

	//Obtengo el tamanio del libro a leer
	int espacioOcupado = obtenerTamanioLibro(cadenaDeDatos);
	/*Le sumo a la longitud de la cadena de datos el offset para posicionarme nuevamente
	 en el archivo*/
	longitudCadena += offset;
	archivoMaestro.seekg(longitudCadena);
	char * libroLeido = (char*)calloc (espacioOcupado, sizeof(char));
	archivoMaestro.read(libroLeido, espacioOcupado);
	archivoMaestro.close();
	return libroLeido;
}

int HandlerArchivoRLV::obtenerUltimoID(){
    return this->ultimoID;
}
