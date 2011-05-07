#include "TestArbol.h"
#include "../src/ArbolB+/ArbolBMas.h"
#include "../src/EstructurasEnComun/Registro.h"
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
	CPPUNIT_FAIL( "No implementado aún" );

}

void TestArbol::testBuscar(){
	CPPUNIT_FAIL( "No implementado aún" );
	}

void TestArbol::testBorrar(){
	CPPUNIT_FAIL( "No implementado aún" );
	}
