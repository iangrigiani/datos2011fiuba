#ifndef TESTPARSERDELIBROS_H
#define TESTPARSERDELIBROS_H

#include <cppunit/extensions/HelperMacros.h>
#include "../src/ParserLibros/ParserDeLibros.h"

class TestParserDeLibros : public CppUnit::TestFixture{
public:
  ParserDeLibros* parser;
  void setUp();
  void tearDown();
  void testObtenerAutorEditorialTituloDeLibroConTodosLosDatos();
  void testObtenerPalabrasConTodosLosDatos();
  void testObtenerEditorialEnLibroSinEditorial();
  CPPUNIT_TEST_SUITE(TestParserDeLibros);
  CPPUNIT_TEST(testObtenerAutorEditorialTituloDeLibroConTodosLosDatos);
  CPPUNIT_TEST(testObtenerPalabrasConTodosLosDatos);
  CPPUNIT_TEST(testObtenerEditorialEnLibroSinEditorial);
  CPPUNIT_TEST_SUITE_END();
private:
  string generarMockLibroCompleto();
  string generarMockLibroSinEditorial();
  void	 generarListaPatron(list<string>& listaDeIds);

};

#endif  // TESTPARSERDELIBROS_H

