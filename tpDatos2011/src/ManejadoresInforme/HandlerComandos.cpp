#include "HandlerComandos.h"

HandlerComandos::HandlerComandos() {
	this-> handler 			= new HandlerArchivoRLV();
	this-> parser 			= new ParserDeLibros();
	this-> log 				= new HandlerArchivoLog();
}

HandlerComandos::~HandlerComandos() {
	delete this-> parser;
	delete this-> handler;
	delete this-> log;
	//delete this-> arbol;
}

void HandlerComandos::guardarLibroEnArchivoMaestro(const string& path_nuevo_libro){
	int ID_Archivo =  0;
	ID_Archivo = this->handler->insertarRegistro(path_nuevo_libro);
	if ( ID_Archivo != ERROR){
		this-> log->insertarRegistro(ID_Archivo);
		printf("Bookerio: Libro guardado con éxito. \n");
		printf("		  ID Libro: %d \n", ID_Archivo);
	}else{
		printf("Bookerio: Libro no pudo ser guardado con éxito. \n");
	}
}

void HandlerComandos::indexar(int parametro){

	// Lista de IDs de libros a Indexar
	list<int> listaDeIds;
	this->log->obtenerListaIDsAIndexar(parametro,listaDeIds); // Obtengo todos los offsets
	list<int>::iterator it = listaDeIds.begin();
	// Para cada offset segun que parametro recibi inserto.
	while ( it != listaDeIds.end()){
	    switch (parametro){
	        case 'a':{
	        	this->arbol = new ArbolBMas(PATH_AUTOR);
	        	insertarEnArbol (1, (*it));
	        	this->log->setearIndexado(*it,'a');break;}

	        case 'e':{
	        	this->arbol = new ArbolBMas(PATH_EDITORIAL);
	        	insertarEnArbol (2, (*it));
	        	this->log->setearIndexado(*it,'e'); break;}

	        case 't': {
	        		this->insertar_en_hash_titulo(*it);
	        		this->log->setearIndexado(*it,'t');
	        		break;
	        }

	        case 'p': {
	        	this->insertar_en_hash_palabra(*it);
	        	this->log->setearIndexado(*it,'p');
	        	break;
	        }
	    }
		++ it;
	}
}

void HandlerComandos::listarLibrosIngresados(){
	list<int> listaDeIds;
	this->log->obtenerListaIDs(listaDeIds);
	list<int>::iterator it = listaDeIds.begin();
	printf("Bookerio: Total Libros Ingresados: %d \n" , listaDeIds.size());
	printf("Bookerio: Libros Ingresados:\n");
	while ( it != listaDeIds.end()){
		printf("%d \n", *it);
		it++;
	}
	printf("Bookerio: Fin de libros Ingresados:\n");
}

void HandlerComandos::obtenerLibro(int IDArchivo){
	char* libro = this->handler->buscarRegistro(IDArchivo);
	printf("Bookerio: Libro %d \n", IDArchivo);
	printf("%s", libro);
	printf("Bookerio: Fin de libro %d \n", IDArchivo);
}

void HandlerComandos::quitarLibro(int IDArchivo) {
	//Borrar libro de todos los índices
	int a = 0, e = 0, t= 0, p = 0;
	if (this->log->obtenerIDEstructuras(IDArchivo, a,e,t,p)){
		if (a == 1){
			if (!eliminarEnArbol(1, IDArchivo)){
				printf("Bookerio: Libro ID  %d : No pudo borrarse del indice por autor. \n", IDArchivo);;
			}
		}
		if (e == 1){
			if (!eliminarEnArbol(2, IDArchivo)){
				printf("Bookerio: Libro ID  %d : No pudo borrarse del indice por editorial. \n", IDArchivo);;
			}
		}
		if (t == 1){
			this->eliminar_de_hash_titulo(IDArchivo);
		}
		if (p == 1){
			this->eliminar_de_hash_palabra(IDArchivo);
		}
		//Borrar libro del archivo maestro
		this->handler->quitarRegistro(IDArchivo);
		printf("Bookerio: Libro ID  %d : Borrado procesado. \n", IDArchivo);
	}else{
		printf("Bookerio: Libro ID  %d : Error: No existe. \n", IDArchivo);
	}
}

void HandlerComandos::verEstructura(int parametro){

	switch (parametro) {
	case 'a': {
				printf("Viendo estructura del árbol de autores. \n");
				this->arbol = new ArbolBMas(PATH_AUTOR);
				arbol->MostrarArbol();
				/*TODO: ARREGLAR ESTO POR DIOS!!!!! */
				//delete arbol;
				break; }
	case 'e': {
				printf("Viendo estructura del árbol de editoriales. \n");
				this->arbol = new ArbolBMas(PATH_EDITORIAL);
				//ArbolBMas* arbol = new ArbolBMas(2, PATH_NODOS);
				arbol->MostrarArbol();
				delete arbol;
				break; }

	case 't': {
				printf("Viendo estructura del hash de títulos. \n");
				Hash hash(TAM_CUBO, PATH_BLOQUES_TITULO, PATH_ESP_LIBRE_TITULO, PATH_TABLA_TITULO, PATH_TMP_TITULO);
				hash.crear_condiciones_iniciales();
				hash.mostrar();
				break; }
		case 'p': {
				printf("Viendo estructura del hash de palabras. \n");
				Hash hash(TAM_CUBO, PATH_BLOQUES_PALABRA, PATH_ESP_LIBRE_PALABRA, PATH_TABLA_PALABRA, PATH_TMP_PALABRA);
				hash.crear_condiciones_iniciales();
				hash.mostrar();
				break; }

	}
}

int HandlerComandos::funcion_hash_titulo(string& str) {

	int size = str.size();
	char* cadena = (char*) malloc (sizeof(char) * (size + 1));
	str.copy(cadena, size);
	cadena[size] = '\0';

	list < string > ::iterator it;
	stringstream ss;

	list < string > palabras = this->parser->obtenerDatos(cadena);

	int clave = 0;
	for (it = palabras.begin(); it != palabras.end(); ++ it) {
		ss << *it << ' ';

		clave += this->funcion_hash_palabra(*it);
	}

	free(cadena);
	str = ss.str();

	return clave;

}

void HandlerComandos::insertar_en_hash_titulo(int offset) {
	Registro* reg = this->parser->obtenerRegistroDeLibro(this->handler->buscarRegistro(offset));

	Hash hash(TAM_CUBO, PATH_BLOQUES_TITULO, PATH_ESP_LIBRE_TITULO, PATH_TABLA_TITULO, PATH_TMP_TITULO);
	hash.crear_condiciones_iniciales();

	string titulo = reg->getTitulo();
	int clave = this->funcion_hash_titulo(titulo);

	list < int > offsets;
	offsets.push_back(offset);
	hash.alta(clave, titulo, offsets);
}

void HandlerComandos::eliminar_de_hash_titulo(int offset) {

	Registro* reg = this->parser->obtenerRegistroDeLibro(this->handler->buscarRegistro(offset));

	Hash hash(TAM_CUBO, PATH_BLOQUES_TITULO, PATH_ESP_LIBRE_TITULO, PATH_TABLA_TITULO, PATH_TMP_TITULO);
	hash.crear_condiciones_iniciales();

	string titulo = reg->getTitulo();
	int clave = this->funcion_hash_titulo(titulo);

	hash.baja(clave, titulo, offset);
}

list < string > HandlerComandos::eliminar_repeticion(list < string > & palabras) {
	list < string > filtrados;
	list < string > ::iterator it_1;
	list < string > ::iterator it_2;

	for (it_1 = palabras.begin(); it_1 != palabras.end(); ++ it_1) {
		it_2 = filtrados.begin();
		while ((*it_2).compare(*it_1) != 0 && it_2 != filtrados.end())
			++ it_2;
		if ((*it_2).compare(*it_1) != 0 && it_2 == filtrados.end())
			filtrados.push_back(*it_1);
	}

	return filtrados;
}



int HandlerComandos::funcion_hash_palabra(const string& str) {

	int clave = 0;
	for (unsigned int i = 0; i < str.size(); ++ i)
		clave += ((int)str[i]) * i;
		//clave += ((int)str[i]) * (2 ^ i);

	return clave;
}

void HandlerComandos::insertar_en_hash_palabra(int offset) {

	Registro* reg = this->parser->obtenerRegistroDeLibro(this->handler->buscarRegistro(offset));

	Hash hash(TAM_CUBO, PATH_BLOQUES_PALABRA, PATH_ESP_LIBRE_PALABRA, PATH_TABLA_PALABRA, PATH_TMP_PALABRA);
	hash.crear_condiciones_iniciales();

	int clave;
	list < int > offsets;
	list < string > ::iterator it;

	list < string > palabras = reg->getPalabras();
	list < string > filtradas = this->eliminar_repeticion(palabras);

	for (it = filtradas.begin(); it != filtradas.end(); ++ it) {
		clave = this->funcion_hash_palabra(*it);
		offsets.push_back(offset);
		hash.alta(clave, *it, offsets);
		offsets.clear();
	}

}

void HandlerComandos::eliminar_de_hash_palabra(int offset) {

	Registro* reg = this->parser->obtenerRegistroDeLibro(this->handler->buscarRegistro(offset));

	Hash hash(TAM_CUBO, PATH_BLOQUES_PALABRA, PATH_ESP_LIBRE_PALABRA, PATH_TABLA_PALABRA, PATH_TMP_PALABRA);
	hash.crear_condiciones_iniciales();

	int clave;
	list < string > ::iterator it;

	list < string > palabras = reg->getPalabras();
	list < string > filtradas = this->eliminar_repeticion(palabras);

	for (it = filtradas.begin(); it != filtradas.end(); ++ it) {
		clave = this->funcion_hash_palabra(*it);
		hash.baja(clave, *it, offset);
	}
}

void HandlerComandos::insertarEnArbol (int tipoArbol, int offset){
//	ArbolBMas* arbol = new ArbolBMas(tipoArbol, PATH_NODOS);
	char * puntero = this->handler->buscarRegistro(offset);
	Registro* reg = this->parser->obtenerRegistroDeLibro(puntero);

	if (tipoArbol == 1){
		Elementos* elemento = new Elementos(new Clave(reg->getAutor()), offset);
		if(elemento->getTamanio() > (TAM_EFECTIVO_NODO * PORC_TAMANIO_NODO / 100) ){
			cout<<"Elemento demasiado grande.\n"<<endl;
		}else{
			if(arbol->insertar(elemento))
				cout<<"ID:"<<offset<<".Libro indexado por autor.\n"<<endl;
		}
		delete elemento;
	}else{
		Elementos* elemento2 = new Elementos(new Clave(reg->getEditorial()), offset);
		if(elemento2->getTamanio() > (TAM_EFECTIVO_NODO * PORC_TAMANIO_NODO / 100) ){
			cout<<"Elemento demasiado grande.\n"<<endl;
		}else{
			if(arbol->insertar(elemento2))
				cout<<"ID:"<<offset<<".Libro indexado por editorial.\n"<<endl;
		delete elemento2;
		}
	}
	delete reg;
//	delete arbol;
}

bool HandlerComandos::eliminarEnArbol(int tipoArbol, int offset) {
	Registro* reg = this->parser->obtenerRegistroDeLibro(this->handler->buscarRegistro(offset));
	bool retorno = false;
	if (tipoArbol == 1){
		this->arbol = new ArbolBMas(PATH_AUTOR);
		Elementos* e = new Elementos(new Clave (reg->getAutor()),offset);
		retorno = arbol->borrar(*e);
		delete e;
		delete arbol;
	}else{
		this->arbol = new ArbolBMas(PATH_EDITORIAL);
		Elementos* e = new Elementos(new Clave (reg->getEditorial()),offset);
		retorno = arbol->borrar(*e);
		delete e;
		delete arbol;
	}
	delete reg;
	return retorno;
//	delete arbol;
}
