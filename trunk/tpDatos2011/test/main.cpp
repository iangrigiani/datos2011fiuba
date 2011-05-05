#include <cppunit/CompilerOutputter.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/ui/text/TestRunner.h>

int main(int argc, char* argv[]){

    // Obtiene el test suite de nivel superior desde el registro
    CppUnit::Test *suite = CppUnit::TestFactoryRegistry::getRegistry().makeTest();
    
    // Agrega los tests a la lista de tests a ejecutar
    CppUnit::TextUi::TestRunner runner;
    runner.addTest( suite );
    
    // Cambiar el default outputter para que genere un error de compilacion
    runner.setOutputter( new CppUnit::CompilerOutputter(&runner.result(), std::cerr ) );

    // Ejecuta los tests
    bool wasSucessful = runner.run();
    
    // Devuelve codigo de error 1 si algun test falla
    return wasSucessful ? 0 : 1;
}

