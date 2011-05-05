#include "TestClave.h"
#include "../src/EstructurasEnComun/Clave.h"

// Registers the fixture into the 'registry'
CPPUNIT_TEST_SUITE_REGISTRATION(TestClave);


void TestClave::setUp(){}

void TestClave::tearDown(){}

void TestClave::testIgualConClavesIguales(){
    Clave a("a");
    Clave b("a");

    CPPUNIT_ASSERT(a.igual(&b));
}

void TestClave::testIgualConClavesDistintas(){
    Clave a("a");
    Clave b("b");

    CPPUNIT_ASSERT(!(a.igual(&b)));
}

void TestClave::testEsMenorConClaveMenor(){
    Clave a("abc");
    Clave b("def");

    CPPUNIT_ASSERT(a.esMenor(&b));
}
void TestClave::testEsMenorConClaveMayor(){
    Clave a("abc");
    Clave b("def");

    CPPUNIT_ASSERT(!(b.esMenor(&a)));
}
void TestClave::testEsMenorConClavesIguales(){
    Clave a("abc");
    Clave b("abc");

    CPPUNIT_ASSERT(!(a.esMenor(&b)));
    CPPUNIT_ASSERT(!(b.esMenor(&a)));
}

