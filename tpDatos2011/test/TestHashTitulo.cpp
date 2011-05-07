#include "TestHashTitulo.h"
#include "../src/Hash/Hash.h"
#include "../src/EstructurasEnComun/Registro.h"
#include "../src/EstructurasEnComun/Constantes.h"
#include <sstream>

CPPUNIT_TEST_SUITE_REGISTRATION(TestHashTitulo);

void TestHashTitulo::setUp(){
	this->hash = new Hash(TAM_BLOQUE, PATH_BLOQUES_TITULO_TEST, PATH_ESP_LIBRE_TITULO_TEST,
			PATH_TABLA_TITULO_TEST, PATH_TMP_TITULO_TEST);
}

void TestHashTitulo::tearDown(){
	delete this->hash;
}

void TestHashTitulo::testInsertar(){
	CPPUNIT_FAIL( "No implementado aún" );

}

void TestHashTitulo::testBuscar(){
	CPPUNIT_FAIL( "No implementado aún" );
	}

void TestHashTitulo::testBorrar(){
	CPPUNIT_FAIL( "No implementado aún" );
	}
