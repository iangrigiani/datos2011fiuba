#include "HandlerComandos.h"


HandlerComandos::HandlerComandos() {
	this-> handler = new HandlerArchivoRLV();
	this-> parser = new ParserDeLibros();
//	this-> log = new HandlerArchivoLog(); TODO
}

HandlerComandos::~HandlerComandos() {
	delete this-> parser;
	delete this-> handler;
//	delete this-> log;
}

void HandlerComandos::guardarLibroEnArchivoMaestro(const string& path_nuevo_libro){
	int ID_Archivo =  0;
	ID_Archivo = this->handler->insertarRegistro(path_nuevo_libro);
//	this->loguearNuevoLibro(ID_Archivo); TODO
}

void HandlerComandos::indexarPorEditoriales(){
	//TODO Obtener del log cada libro guardado
	//TODO Indexar cada libro por editorial
	//TODO Escribir el flag de "indexado por editorial" de cada libro

}
void HandlerComandos::indexarPorAutores(){
	// TODO Idem, anterior

}

void HandlerComandos::indexarPorTitulos(){
	// TODO Idem, anterior
}

void HandlerComandos::indexarPorPalabras(){
	// TODO Idem, anterior
}

void HandlerComandos::listarLibrosIngresados(){
	//this->mostrarLog();TODO
}

void HandlerComandos::obtenerLibro(int IDArchivo){

}

void HandlerComandos::quitarLibro(int IDArchivo){
}

void HandlerComandos::verArbolEditorial(){

}

void HandlerComandos::verArbolAutor(){

}

void HandlerComandos::verHashTitulo(){

}

void HandlerComandos::verHashPalabras(){

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
