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
}

void HandlerComandos::guardarLibroEnArchivoMaestro(const string& path_nuevo_libro){
	int ID_Archivo =  0;
	ID_Archivo = this->handler->insertarRegistro(path_nuevo_libro);
	this-> log->insertarRegistro(ID_Archivo);
}

void HandlerComandos::indexar(int parametro){
	//Obtener del log una Lista de quintuplas (o como se diga) que contega los 5 campos
	//guardados en el log (ID_Archivo, ind1, ind2, ind3, ind4).

	// En esta lista obtengo los offset de todos los archivos que debo indexar.
	list<int> listaDeIds;
	// Obtengo todos los offsets
	this->log->obtenerListaIDsAIndexar(parametro,listaDeIds);
	list<int>::iterator it = listaDeIds.begin();

	// Para cada offset segun que parametro recibi inserto.
	while ( it != listaDeIds.end()){
	    switch (parametro){
	        case 'a':{
	        	fstream ff ;
	        	ff.open(PATH_CONFIGURACION_AUTORES, ios_base::out);
	        	ff.close();
	        	ff.open(PATH_NODOS, ios_base::out);
	        	ff.close();
	        	ff.open(PATH_FRONT_CODING, ios_base::out);
	        	ff.close();
	        	ff.open(PATH_ARBOL, ios_base::out);
	        	ff.close();
	        	ff.open(PATH_ESPACIO_LIBRE_RLV, ios_base::out);
	        	ff.close();
	        	ff.open(PATH_REG_LONG_VARIABLE, ios_base::out);
	        	ff.close();
	        	ff.open(PATH_STOPWORDS, ios_base::out);
	        	ff.close();
	        	insertarEnArbol (1, (*it));
	        	this->log->setearIndexado(*it,'a');break;}

	        case 'e':{
	        	fstream ff ;
	        	ff.open(PATH_CONFIGURACION_EDITORIAL, ios_base::out);
	        	ff.close();
	        	ff.open(PATH_NODOS, ios_base::out);
	        	ff.close();
	        	ff.open(PATH_FRONT_CODING, ios_base::out);
	        	ff.close();
	        	ff.open(PATH_ARBOL, ios_base::out);
	        	ff.close();
	        	ff.open(PATH_ESPACIO_LIBRE_RLV, ios_base::out);
	        	ff.close();
	        	ff.open(PATH_REG_LONG_VARIABLE, ios_base::out);
	        	ff.close();
	        	ff.open(PATH_STOPWORDS, ios_base::out);
	        	ff.close();
	        	insertarEnArbol (2, (*it));
	        	this->log->setearIndexado(*it,'e'); break;}

	        case 't': {
	        	if (this->insertar_en_hash_titulo(*it) == false)
	        			cout << "Coincidencia de claves" << endl;
	        	else this->log->setearIndexado(*it,'t');
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

void HandlerComandos::insertarEnArbol (int tipoArbol, int offset){
	ArbolBMas* arbol = new ArbolBMas(tipoArbol, PATH_NODOS, 20);
	Registro* reg = this->parser->obtenerRegistroDeLibro(this->handler->buscarRegistro(offset));

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
	delete arbol;
}

void HandlerComandos::listarLibrosIngresados(){
	list<int> listaDeIds;
	this->log->obtenerListaIDs(listaDeIds);
	list<int>::iterator it = listaDeIds.begin();
	while ( it != listaDeIds.end()){
		printf("%d", *it);
	}

}

void HandlerComandos::obtenerLibro(int IDArchivo){
	char* libro = this->handler->buscarRegistro(IDArchivo);
	printf("Bookerio: Libro %d \n", IDArchivo);
	printf("%s", libro);

}

void HandlerComandos::quitarLibro(int IDArchivo) {
	if (this->eliminar_de_hash_titulo(IDArchivo) == false)
		cout << "Error: no existe un archivo con ese ID" << endl;
	this->eliminar_de_hash_palabra(IDArchivo);
	//TODO Borrar de todos los índices
	//TODO Borrar del log?
}

void HandlerComandos::verEstructura(int parametro){
	//TODO enlazar con los métodos que tiene cada índice para mostrarse
	switch (parametro) {
	case 'a': {
			printf("Viendo estructura del árbol de autores. \n");
			//this->arbol_autores->MostrarArbol();
			break; }
	case 'e': {
			printf("Viendo estructura del árbol de editoriales. \n");
			//this->arbol_editoriales->MostrarArbol();
			break; }
	case 't': {
			printf("Viendo estructura del hash de títulos. \n");
			HashTitulo hash;
			hash.crear_condiciones_iniciales();
			hash.mostrar();
			break; }
	case 'p': {
			printf("Viendo estructura del hash de palabras. \n");
			HashPalabra hash;
			hash.crear_condiciones_iniciales();
			hash.mostrar();
			break; }
	}
}

int HandlerComandos::funcion_hash_titulo(const string& str) {
	int size = str.size();
	char* cadena = (char*) malloc (sizeof(char) * (size + 1));
	str.copy(cadena, size);
	cadena[size] = '\0';

	list < string >::iterator it;

	list < string > palabras = this->parser->obtenerDatos(cadena);
	int clave = 0;
	for (it = palabras.begin(); it != palabras.end(); ++ it)
		for (unsigned int i = 0; i < (*it).size(); ++ i)
			clave += ((int)(*it)[i]) * i;

	free(cadena);
	return clave;
}

bool HandlerComandos::insertar_en_hash_titulo(int offset) {
	Registro* reg = this->parser->obtenerRegistroDeLibro(this->handler->buscarRegistro(offset));

	HashTitulo hash;
	hash.crear_condiciones_iniciales();

	int clave = this->funcion_hash_palabra(reg->getTitulo());

	RegTitulo reg_indice(clave, offset);
	bool r = hash.insertar_reg(reg_indice);
	hash.mostrar();
	return r;
}

bool HandlerComandos::eliminar_de_hash_titulo(int offset) {
	Registro* reg = this->parser->obtenerRegistroDeLibro(this->handler->buscarRegistro(offset));

	HashTitulo hash;
	hash.crear_condiciones_iniciales();

	int clave = this->funcion_hash_titulo(reg->getTitulo());

	bool r = hash.eliminar_reg(clave);
	//hash.mostrar();
	return r;
}

int HandlerComandos::funcion_hash_palabra(const string& str) {
	int clave = 0;
	for (unsigned int i = 0; i < str.size(); ++ i)
		clave += ((int)str[i]) * i;

	//cout << str << " = " << clave;
	return clave;
}

void HandlerComandos::insertar_en_hash_palabra(int offset) {
	Registro* reg = this->parser->obtenerRegistroDeLibro(this->handler->buscarRegistro(offset));

	HashPalabra hash;
	hash.crear_condiciones_iniciales();

	int clave;
	list < int > offsets;
	list < string > palabras = reg->getPalabras();
	list < string > ::iterator it;
	for (it = palabras.begin(); it != palabras.end(); ++ it) {
		clave = this->funcion_hash_palabra(*it);
		offsets.push_back(offset);
		hash.insercion(clave, offsets);
		offsets.clear();
	}
	//hash.mostrar();
}

void HandlerComandos::eliminar_de_hash_palabra(int offset) {
	Registro* reg = this->parser->obtenerRegistroDeLibro(this->handler->buscarRegistro(offset));

	HashPalabra hash;
	hash.crear_condiciones_iniciales();

	int clave;
	list < string > palabras = reg->getPalabras();
	list < string > ::iterator it;
	for (it = palabras.begin(); it != palabras.end(); ++ it) {
		clave = this->funcion_hash_palabra(*it);
		hash.eliminacion(clave, offset);
	}
	//hash.mostrar();
}