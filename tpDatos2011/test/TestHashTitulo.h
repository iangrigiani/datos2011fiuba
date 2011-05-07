#ifndef TESTHASH_H
#define TESTHASH_H

#include <cppunit/extensions/HelperMacros.h>
#include "../src/Hash/Hash.h"

class TestHashTitulo : public CppUnit::TestFixture{
public:
	Hash* hash;
	void setUp();
	void tearDown();
	void testInsertar();
	void testBuscar();
	void testBorrar();
	CPPUNIT_TEST_SUITE(TestHashTitulo);
	CPPUNIT_TEST(testInsertar);
	CPPUNIT_TEST(testBuscar);
	CPPUNIT_TEST(testBorrar);
	CPPUNIT_TEST_SUITE_END();
private:
};

#endif  // TESTHASHTITULO_H

