#include "HandlerEstructuras.h"

HandlerEstructuras::HandlerEstructuras() {
	this-> handler = new HandlerArchivoRLV();
	this-> parser = new ParserDeLibros();
}

HandlerEstructuras::~HandlerEstructuras() {
	delete this-> parser;
	delete this-> handler;
}

void HandlerEstructuras::insertar(string path, ArbolBMas &arbol, Hash& hash){

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
}

void HandlerEstructuras::borrarEnArbol(Clave* clave, ArbolBMas &arbol){
}

void HandlerEstructuras::buscarEnArbol(Clave* clave, ArbolBMas &arbol){
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
}

void HandlerEstructuras::borrarEnHash(Clave* clave, Hash &hash){

}
void HandlerEstructuras::buscarEnHash(Clave* clave, Hash &hash){

}
