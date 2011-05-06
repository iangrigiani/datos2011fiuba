#include "TestHandlerArchivoLog.h"
#include "../src/ManejadoresDeArchivos/HandlerArchivoLog.h"
#include <stdlib.h>
#include <list>


CPPUNIT_TEST_SUITE_REGISTRATION(TestHandlerArchivoLog);
void TestHandlerArchivoLog::setUp(){
	this->handler = new HandlerArchivoLog();
}

void TestHandlerArchivoLog::tearDown(){
	delete this->handler;
}

void TestHandlerArchivoLog::testInsertarRegistro(){
	int i= 0;
	int a, e, t, p = 0;

	bool encontrado = false;
	this->handler->insertarRegistro(300);
	this->handler->insertarRegistro(301);
	this->handler->insertarRegistro(302);
	encontrado = this->handler->obtenerIDEstructuras(300, a, e, t, p);
	if (encontrado) { i++;}

	encontrado = this->handler->obtenerIDEstructuras(301, a, e, t, p);
	if (encontrado) { i++;}

	encontrado = this->handler->obtenerIDEstructuras(302, a, e, t, p);
	if (encontrado) { i++;}

	CPPUNIT_ASSERT(i == 3);
}

void TestHandlerArchivoLog::testBuscarRegistro() {
	int a, e, t, p = 0;
        bool encontrado = this->handler->obtenerIDEstructuras(301, a, e, t, p);
	CPPUNIT_ASSERT(encontrado == true ); 
}

void TestHandlerArchivoLog::testSetearIndexado() {
	int a, e, t, p = 0 ;
	this->handler->setearIndexado(301, 'a');
	this->handler->obtenerIDEstructuras(301, a, e, t, p);
	CPPUNIT_ASSERT(a == 1);
}

void TestHandlerArchivoLog::testObtenerListaIDs() {

}

void TestHandlerArchivoLog::testObtenerListaIDsAIndexar() {

}
