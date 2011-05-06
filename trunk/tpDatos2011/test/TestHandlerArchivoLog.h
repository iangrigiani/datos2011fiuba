#ifndef TESTHANDLERARCHIVOLOG_H
#define TESTHANDLERARCHIVOLOG_H
#include "../src/ManejadoresDeArchivos/HandlerArchivoLog.h"
#include <cppunit/extensions/HelperMacros.h>

class TestHandlerArchivoLog : public CppUnit::TestFixture{
public:
	HandlerArchivoLog* handler;
	void setUp();
	void testInsertarRegistro();
	void testBuscarRegistro();
	void testSetearIndexado();
	void testObtenerListaIDs();
	void testObtenerListaIDsAIndexar();
	void tearDown();
	CPPUNIT_TEST_SUITE(TestHandlerArchivoLog);
	CPPUNIT_TEST(testInsertarRegistro);
	CPPUNIT_TEST(testBuscarRegistro);
	CPPUNIT_TEST(testSetearIndexado);
	CPPUNIT_TEST(testObtenerListaIDs);
	CPPUNIT_TEST(testObtenerListaIDsAIndexar);
	CPPUNIT_TEST_SUITE_END();

};

#endif /*TESTHANDLERARCHIVOLOG_H*/
