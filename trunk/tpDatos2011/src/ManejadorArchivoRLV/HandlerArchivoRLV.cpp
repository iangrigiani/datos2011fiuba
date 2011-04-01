#include "HandlerArchivoRLV.h"

HandlerArchivoRLV::HandlerArchivoRLV() {
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

// Otengo ID del ultimo libro ingresado
	obtenerDatosDeEntrada();

// Manejo sobre el archivo de RLV
	f_ent.read(buffer, size);
	int indexado = 0;
	int procesado = 1;
	int id_Archivo = this->ultimo_ID + 1;
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

char* HandlerArchivoRLV::buscarLibro(int offset)
{
	std::ifstream archivoRegistros;
	char  cadenaDeDatos[100];
	archivoRegistros.open(PATH_REG_LONG_VARIABLE, std::ios_base::in);
	archivoRegistros.seekg(offset);

	//Obtengo la linea correspondiente al libro en la que se tiene la información de tamanio
	archivoRegistros.get(cadenaDeDatos,100);
	string cad = cadenaDeDatos;
	int longitudCadena = cad.length();

	//Obtengo el tamanio del libro a leer
	int espacioOcupado = obtenerTamanioLibro(cadenaDeDatos);
	/*Le sumo a la longitud de la cadena de datos el offset para posicionarme nuevamente
	 en el archivo*/
	longitudCadena += offset;
	archivoRegistros.seekg(longitudCadena);
	char * libroLeido = (char*)calloc (espacioOcupado, sizeof(char));
	archivoRegistros.read(libroLeido, espacioOcupado);
	archivoRegistros.close();
	return libroLeido;
}

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

void HandlerArchivoRLV::obtenerDatosDeEntrada(){

	/*
	 *  TODO ESTE METODO SE DEBE VERIFICAR QUE VALLA ASIGNANDO
	 *  UN NUMERO CONSECUTIVO A CADA ARCHIVO INGRESADO.
	 */
	std::ifstream archivoRegistros;
	char  cadenaDeDatos[100];
	// Abro el archivo y obtengo la primer linea
	archivoRegistros.open(PATH_REG_LONG_VARIABLE, std::ios_base::in);
	archivoRegistros.get(cadenaDeDatos,100);
	string cad = cadenaDeDatos;
	int cont = 0;
	int offset = 0;
	int tamanioLibro = 0;
	int longitudCadena = cad.length();
	// si tiene datos busco el tamanio y salto al proximo libro
	if (longitudCadena > 0 ){
		++cont;
		tamanioLibro = obtenerTamanioLibro(cadenaDeDatos);
		offset = longitudCadena + tamanioLibro;
	}
	cad.clear();
	free(cadenaDeDatos);
	archivoRegistros.seekg(offset);
	archivoRegistros.get(cadenaDeDatos,100);
	cad = cadenaDeDatos;
	longitudCadena = cad.length();
	tamanioLibro = 0;

	/*
	 * Mientras vaya encontrando datos salto hasta el siguiente
	 * asi hasta no encontrar datos y segun la cantidad de veces
	 * que hice seek tengo la cantidad de libros que hay adentro del
	 * archivo por ende tengo el "ultimo_ID". El Id del libro a incertar
	 * sera este que consegui aca + 1.
	 */

	while(longitudCadena > 0){
		tamanioLibro = obtenerTamanioLibro(cadenaDeDatos);
		offset = longitudCadena + tamanioLibro;
		archivoRegistros.seekg(offset);
		cad.clear();
		free(cadenaDeDatos);
		archivoRegistros.get(cadenaDeDatos,100);
		cad = cadenaDeDatos;
		longitudCadena = cad.length();
		tamanioLibro = 0;
	}
	this->ultimo_ID = cont;
	this->size = offset;
	archivoRegistros.close();
}
