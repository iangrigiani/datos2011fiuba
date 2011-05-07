#ifndef TESTARBOL_H
#define TESTARBOL_H

#include <cppunit/extensions/HelperMacros.h>
#include "../src/ArbolB+/ArbolBMas.h"

class TestArbol : public CppUnit::TestFixture{
public:
  ArbolBMas* arbol;
  void setUp();
  void tearDown();
  void testInsertar();
  void testBuscar();
  void testBorrar();
  CPPUNIT_TEST_SUITE(TestArbol);
  CPPUNIT_TEST(testInsertar);
  CPPUNIT_TEST(testBuscar);
  CPPUNIT_TEST(testBorrar);
  CPPUNIT_TEST_SUITE_END();
private:
};

#endif  // TESTARBOL_H

