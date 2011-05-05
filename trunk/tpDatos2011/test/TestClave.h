#ifndef TESTCLAVE_H
#define TESTCLAVE_H

#include <cppunit/extensions/HelperMacros.h>

class TestClave : public CppUnit::TestFixture{
    CPPUNIT_TEST_SUITE(TestClave);

    CPPUNIT_TEST(testIgualConClavesIguales);
    CPPUNIT_TEST(testIgualConClavesDistintas);
    
    CPPUNIT_TEST(testEsMenorConClaveMenor);
    CPPUNIT_TEST(testEsMenorConClaveMayor);
    CPPUNIT_TEST(testEsMenorConClavesIguales);

    CPPUNIT_TEST_SUITE_END();

public:
    void setUp();
    void tearDown();

    void testIgualConClavesIguales();
    void testIgualConClavesDistintas();

    void testEsMenorConClaveMenor();  
    void testEsMenorConClavesIguales();  
    void testEsMenorConClaveMayor();  

};

#endif  // TESTCLAVE_H

