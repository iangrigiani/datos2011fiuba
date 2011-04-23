#include "HandlerComandos.h"


HandlerComandos::HandlerComandos() {
	this-> handler 			= new HandlerArchivoRLV();
	this-> parser 			= new ParserDeLibros();
	this-> log 				= new HandlerArchivoLog();

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
	//TODO Obtener del log una Lista de quintuplas (o como se diga) que contega los 5 campos
	//	   guardados en el log (ID_Archivo, ind1, ind2, ind3, ind4).
	//TODO Indexar cada libro de acuerdo al parámetro si es que ya no fue indexado,
	//     modificando el índice correspondiente
	//TODO Escribir el flag indX de cada libro y actualizar el log

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




/*
void HandlerComandos::insertar(string path, ArbolBMas &arbol, Hash& hash){

	unsigned int offset = this->handler->insertarRegistro(path);

	Registro* reg = this->parser->obtenerRegistroDeLibro(this->handler->buscarRegistro(offset));

	if ( arbol.getTipo() == 1){
		// El dato es un Autor.
		Elementos* elemento = new Elementos(new Clave(reg->getAutor()), offset);
		if(elemento->getTamanio() > (TAM_EFECTIVO_NODO * PORC_TAMANIO_NODO / 100) ){
			cout<<"Elemento demasiado grande"<<endl;
		}else{
			if(arbol.insertar(elemento))
				cout<<"Elemento Insertado"<<endl;
		}
	}else{
		Elementos* elemento = new Elementos(new Clave(reg->getEditorial()), offset);
		if(elemento->getTamanio() > (TAM_EFECTIVO_NODO * PORC_TAMANIO_NODO / 100) ){
			cout<<"Elemento demasiado grande"<<endl;
		}else{
			if(arbol.insertar(elemento))
				cout<<"Elemento Insertado"<<endl;
		}
	}


	/*
	 *  TODO aca agregar lo que sea del hash para ese elemento usando "hash"
	 *  en Registor tenes la lista de palabras y el titulo y en offset
	 *  tenes el offset donde se inserto en el archivo de RLV
	 */

/*
void HandlerComandos::borrarEnArbol(Clave* clave, ArbolBMas &arbol){
}*/

/*
void HandlerComandos::buscarEnArbol(Clave* clave, ArbolBMas &arbol){
//	std::list<Elementos*> elementos = arbol.buscar(*(clave));
//	if (elementos.size() > 0){
//
//		cout<<"Elementos encontrados: ";
//		std::list<Elementos*>::iterator it = elementos.begin();
//		while ( it != elementos.end()){
//			Registro* reg = this->parser->obtenerRegistroDeLibro(handler->buscarRegistro((*it)->getOffset()));
//			reg->toString();
//			++it;
//			delete reg;
//		}
//	}else{
//		cout<<"elemento no encontrado"<<endl;
//	}
}*/
/*
void HandlerComandos::borrarEnHash(Clave* clave, Hash &hash){

}*/
/*
void HandlerComandos::buscarEnHash(Clave* clave, Hash &hash){

}
*/
