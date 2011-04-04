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


void HandlerArchivoRLV::recuperarDatosAnteriores(){
	FILE* arch;
	if ((arch = fopen(PATH_CONFIG_RLV, "r")) == NULL) {
		cout << "Error al intentar abrir el archivo: " << PATH_CONFIG_RLV << endl;
		return;
	}

	char buffer[sizeof(int)];
	fread(buffer, 1, sizeof(int), arch);
	string cad = buffer;
	if (cad.length() > 0){
		this->ultimoID = atoi(buffer);
	}else{
		this->ultimoID = 0;
	}
	fclose(arch);

	std::ifstream archivoMaestro;
	char  cadena[100];
	archivoMaestro.open(PATH_CONFIG_RLV, std::ios_base::in);
	archivoMaestro.seekg(0);
	archivoMaestro.get(cadena,100);
	string cad2 = cadena;
	int longitudCadena = cad2.length();
	if (longitudCadena > 0){
		this->ultimoOffset = obtenerTamanioLibro(cadena);
	}else{
		this->ultimoOffset = 0;
	}
}

HandlerArchivoRLV::HandlerArchivoRLV() {
    recuperarDatosAnteriores();
}

int HandlerArchivoRLV::insertarRegistro(const string& path_nuevo_libro)
{
// Manejo sobre el archivo del libro a ingresar
	std::ifstream f_ent;
	f_ent.open(path_nuevo_libro.c_str(), std::ios_base::in);
	f_ent.seekg(0,std::ios_base::end);
	// Obtengo tamanio de libro
	int size = f_ent.tellg();
	f_ent.seekg(0);
	char* buffer = (char*) calloc (size-1 , sizeof(char));
    f_ent.read(buffer, size);
	f_ent.close();


// Obtengo ID del ultimo libro ingresado y seteo todos sus datos
	int id_Archivo = this->ultimoID + 1;
    this->ultimoID = id_Archivo;
    this->ultimoOffset = obtenerTamanioMaestro();

    grabarDatosActuales();

    int indexado = 0;
	int procesado = 1;

// Manejo sobre el archivo de RLV
	std::ofstream f_dst;
	f_dst.open(PATH_REG_LONG_VARIABLE, std::ios_base::app);
	stringstream ss;
// Armo las cabecera para el libro
	ss << id_Archivo << "|" << size << "|" << procesado << "|" << indexado << "|" << "\n" << buffer << "\n" ;
	string str = ss.str();
	// Escribo libro en el archivo de RLV
	f_dst.write(str.c_str(), str.length());
	f_dst.close();
	free(buffer);

// Retorno el offset que se guardara en el arbol.
	return this->ultimoOffset;
}

void HandlerArchivoRLV::grabarDatosActuales(){

	std::ofstream f_dst;
	f_dst.open(PATH_CONFIG_RLV, std::ios_base::out);
	stringstream ss;
	ss << this->ultimoID << "|" << this->ultimoOffset;
	string str = ss.str();

	// Escribo libro en el archivo de control el ultimo offset y ID.
	f_dst.write(str.c_str(), str.length());
	f_dst.flush();
	f_dst.close();
}

char* HandlerArchivoRLV::buscarRegistro(int offset)
{
	std::ifstream archivoMaestro;
	char  cadenaDeDatos[100];
	archivoMaestro.open(PATH_REG_LONG_VARIABLE, std::ios_base::in);
	// Me posiciono en el archivo de RLV
	archivoMaestro.seekg(offset);

	archivoMaestro.get(cadenaDeDatos,100);
	string cad = cadenaDeDatos;
	int longitudCadena = cad.length();
	longitudCadena += offset;
	//Obtengo el tamanio del libro a leer
	int espacioOcupado = obtenerTamanioLibro(cadenaDeDatos);

	/*Le sumo a la longitud de la cadena de datos el offset para posicionarme nuevamente
	 en el archivo*/
	archivoMaestro.seekg(longitudCadena);
	// obtengo el libro
	char * libroLeido = (char*)calloc (espacioOcupado, sizeof(char));
	archivoMaestro.read(libroLeido, espacioOcupado);
	archivoMaestro.close();

	return libroLeido;
}

int HandlerArchivoRLV::obtenerTamanioMaestro(){
	FILE* fin;
	if ((fin = fopen(PATH_REG_LONG_VARIABLE, "r")) == NULL){
		cout << "Error al abrir el archivo de registro de longitud variable" << endl;
		return -1;
	}
	fseek(fin, 0 , SEEK_END);
	int retorno = ftell(fin);
	rewind(fin);
	fclose(fin);
	return retorno;
}

void HandlerArchivoRLV::quitarRegistro(int offset){
// Abro el archivo y me posiciono para obtener los datos
	std::fstream fh;
	char  cadenaDeDatos[100];
	fh.open(PATH_REG_LONG_VARIABLE, std::ios_base::in | std::ios_base::out);
	fh.seekg(offset);
	fh.get(cadenaDeDatos,100);
	string cad = cadenaDeDatos;
	int longitudCadena = cad.length();
	int espacioOcupado = obtenerTamanioLibro(cadenaDeDatos);
	espacioOcupado += longitudCadena;
	fh.seekg(offset);
	cout << "Estoy parado en : " << fh.tellg() << endl;
	cout << "Y debo leer una cadena de :" << espacioOcupado << endl;
	char * libroLeido = (char*)calloc (espacioOcupado, sizeof(char));
	free(libroLeido);
	fh.write(libroLeido, espacioOcupado);
	fh.flush();
	fh.close();
}
