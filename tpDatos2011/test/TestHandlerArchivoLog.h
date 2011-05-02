#ifndef TEST_TestHandlerArchivoLog
#define TEST_TestHandlerArchivoLog

#ifdef ECUT_MAIN

#include "cppunit/extensions/HelperMacros.h"
#include "../HandlerArchivoLog.h"


class TestRoad : public CPPUNIT_NS::TestFixture {
public:
	void testInsertarRegistro();
	void testBuscarRegistro();
	void testSetearIndexado();
	void testObtenerListaIDs();
	void testObtenerListaIDsAIndexar();
	CPPUNIT_TEST_SUITE(TestHandlerArchivoLog);
	CPPUNIT_TEST(testInsertarRegistro);
	CPPUNIT_TEST(testBuscarRegistro);
	CPPUNIT_TEST(testSetearIndexado);
	CPPUNIT_TEST(testObtenerListaIDs);
	CPPUNIT_TEST(testObtenerListaIDsAIndexar);
	CPPUNIT_TEST_SUITE_END();*/
private:

};

#endif /* ECUT_MAIN */

#endif /*TestHandlerArchivoLog*/
