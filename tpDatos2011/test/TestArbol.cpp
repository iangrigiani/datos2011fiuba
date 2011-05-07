#include "TestArbol.h"
#include "../src/ArbolB+/ArbolBMas.h"
#include "../src/EstructurasEnComun/Constantes.h"
#include <sstream>

CPPUNIT_TEST_SUITE_REGISTRATION(TestArbol);

void TestArbol::setUp(){
	this->arbol = new ArbolBMas(PATH_TEST_ARBOL);
}

void TestArbol::tearDown(){
	delete this->arbol;
}

void TestArbol::testInsertar(){
	Elementos* elemento1 = new Elementos (new Clave("1"), 263);
	Elementos* elemento2 = new Elementos (new Clave("2"), 300);
	Elementos* elemento3 = new Elementos (new Clave("3"), 403);
	Elementos* elemento4 = new Elementos (new Clave("4"), 471);
	Elementos* elemento5 = new Elementos (new Clave("5"), 490);
	Elementos* elemento6 = new Elementos (new Clave("6"), 520);
	bool insertado1, insertado2,insertado3, insertado4, insertado5, insertado6 = false;
	insertado1 = this->arbol->insertar(elemento1);
	insertado2 = this->arbol->insertar(elemento2);
	insertado3 = this->arbol->insertar(elemento3);
	insertado4 = this->arbol->insertar(elemento4);
	insertado5 = this->arbol->insertar(elemento5);
	insertado6 = this->arbol->insertar(elemento6);

	CPPUNIT_ASSERT(insertado1 == true);
	CPPUNIT_ASSERT(insertado2 == true);
	CPPUNIT_ASSERT(insertado3 == true);
	CPPUNIT_ASSERT(insertado4 == true);
	CPPUNIT_ASSERT(insertado5 == true);
	CPPUNIT_ASSERT(insertado6 == true);
}

/*Se usará cuando esté implementada la búsqueda en el arbol
void TestArbol::testBuscar(){
	list<Elementos*> resultado;
	Clave clave("3");
	resultado = buscar(clave);
	resultado
	CPPUNIT_ASSERT( "No implementado aún" );
}*/

void TestArbol::testBorrar(){
	Elementos elemento(new Clave("1"), 263);
	bool borrado = false;
	borrado = this->arbol->borrar(elemento);

	CPPUNIT_ASSERT(borrado == true );
}
