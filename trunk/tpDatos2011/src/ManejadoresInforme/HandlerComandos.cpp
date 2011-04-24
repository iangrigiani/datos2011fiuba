#include "HandlerComandos.h"


HandlerComandos::HandlerComandos() {
	this-> handler 			= new HandlerArchivoRLV();
	this-> parser 			= new ParserDeLibros();
	this-> log 				= new HandlerArchivoLog();
	fstream ff ;
	ff.open(PATH_ARCHIVO_LOG, ios_base::out);
	ff.close();
/*	this-> arbol_autores     = new ArbolBMas();
	this-> arbol_editoriales = new ArbolBMas();
	this-> hash_titulos		 = new Hash();
	this-> hash_palabras	 = new Hash();*/

}

HandlerComandos::~HandlerComandos() {
	delete this-> parser;
	delete this-> handler;
	delete this-> log;

/*	delete this-> arbol_autores    	= new ArbolBMas();
	delete this-> arbol_editoriales	= new ArbolBMas();
	delete this-> hash_titulos		= new Hash();
	delete this-> hash_palabras		= new Hash();*/
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
	obtenerListaIDs(parametro, listaDeIds);
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
	        	insertarEnArbol (1, (*it));	break;}

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
	        	insertarEnArbol (2, (*it));	break;}

	        case 't':{ // TODO HASH
	        	break;}
	        case 'p':{ // TODO HASH
	        	break;}
	    }
		++it;
	}
}
void HandlerComandos::insertarEnArbol (int tipoArbol, int offset){
	ArbolBMas* arbol = new ArbolBMas(tipoArbol, PATH_NODOS, 20);
	Registro* reg = this->parser->obtenerRegistroDeLibro(this->handler->buscarRegistro(offset));

	if (tipoArbol == 1){
		Elementos* elemento = new Elementos(new Clave(reg->getAutor()), offset);
		if(elemento->getTamanio() > (TAM_EFECTIVO_NODO * PORC_TAMANIO_NODO / 100) ){
			cout<<"Elemento demasiado grande"<<endl;
		}else{
			if(arbol->insertar(elemento))
				cout<<"Elemento Insertado"<<endl;
		}
		delete elemento;
	}else{
		Elementos* elemento2 = new Elementos(new Clave(reg->getEditorial()), offset);
		if(elemento2->getTamanio() > (TAM_EFECTIVO_NODO * PORC_TAMANIO_NODO / 100) ){
			cout<<"Elemento demasiado grande"<<endl;
		}else{
			if(arbol->insertar(elemento2))
				cout<<"Elemento Insertado"<<endl;
		}
		delete elemento2;
	}
	delete reg;
	delete arbol;
}


void HandlerComandos::obtenerListaIDs (int parametro,list<int>& listaDeIds){
	fstream archivoLog;
    int IDActual = 0, ind1=0 , ind2=0, ind3=0, ind4=0;
    string cad;
    char* cadena = (char*)calloc(100, sizeof(char));
	bool indexado = false;
	archivoLog.open(PATH_ARCHIVO_LOG, std::ios_base::in | std::ios_base::out);
	archivoLog.seekg(0);
	while (!archivoLog.eof() ){
		archivoLog.getline (cadena, 100);
		cad = cadena;
		if (cad.length() > 0 ) {
			IDActual = atoi(strtok(cadena,"|"));
		    ind1 = atoi ( strtok(NULL,"|") );
		    ind2 = atoi ( strtok(NULL,"|") );
		    ind3 = atoi ( strtok(NULL,"|") );
		    ind4 = atoi ( strtok(NULL,"\n") );
		    switch (parametro){
		        case 'a':{
		        	if (ind1 == 1)
		        		indexado = true;
		        	break;}
		        case 'e':{
		        	if (ind2 == 1)
		        		indexado = true;
		        	break;}
		        case 't':{
		        	if (ind3 == 1)
		        		indexado = true;
		        	break;}
		        case 'p':{
		        	if (ind4 == 1)
		        		indexado = true;
		        	break;}
		    }
			if (!indexado){
				listaDeIds.push_back(IDActual);
			}

		}
		indexado = false;
	}
}
void HandlerComandos::listarLibrosIngresados(){
	//this->mostrarLog();TODO
}

void HandlerComandos::obtenerLibro(int IDArchivo){
	//TODO
}

void HandlerComandos::quitarLibro(int IDArchivo){
	//TODO Borrar del archivo maestro
	//TODO Borrar de todos los índices
	//¿TODO Borrar del log?
}

void HandlerComandos::verEstructura(int parametro){
	//TODO enlazar con los métodos que tiene cada índice para mostrarse
	switch (parametro){
	case 'a':{
			printf("Viendo estructura del árbol de autores. \n");
			//this.arbol_autores->MostrarArbol();
			break;
			}
	case 'e':{
			printf("Viendo estructura del árbol de editoriales. \n");
			//this.arbol_editoriales->MostrarArbol();
			break;
			}
	case 't':{
			printf("Viendo estructura del hash de titulos. \n");
			//this.hash_titulos->MostrarHash(); TODO
			break;
			}
	case 'p':{
			printf("Viendo estructura del hash de palabras. \n");
			//this.hash_palabras->MostrarHash(); TODO
			break;
			}

	}
}
