#ifndef TESTPARSERDELIBROS_H
#define TESTPARSERDELIBROS_H

#include <cppunit/extensions/HelperMacros.h>

class TestParserDeLibros : public CppUnit::TestFixture
{
  CPPUNIT_TEST_SUITE(TestParserDeLibros);
  CPPUNIT_TEST(testConstructor);
  CPPUNIT_TEST_SUITE_END();

public:
  void setUp();
  void tearDown();
  void testConstructor();
};

#endif  // TESTPARSERDELIBROS_H

