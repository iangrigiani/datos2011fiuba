#include "TestParserDeLibros.h"
#include "../src/ParserLibros/ParserDeLibros.h"
#include "../src/EstructurasEnComun/Registro.h"
#include <sstream>

CPPUNIT_TEST_SUITE_REGISTRATION(TestParserDeLibros);

void TestParserDeLibros::setUp(){
	this->parser = new ParserDeLibros();
}

void TestParserDeLibros::tearDown(){
//	delete this->parser;
}

void TestParserDeLibros::testObtenerAutorEditorialTituloDeLibroConTodosLosDatos(){
	string strLibro = generarMockLibroCompleto();
	const char *auxlibro= strLibro.c_str();
	char* libro;
	libro = const_cast<char*>(auxlibro);
	Registro* regLibro = this->parser->obtenerRegistroDeLibro((libro) );

	string autor = regLibro->getAutor();
	CPPUNIT_ASSERT( (autor.compare("darrenzshan")) == 0 );

	string titulo = regLibro->getTitulo();
	CPPUNIT_ASSERT( (titulo.compare("lazmontazzazdezloszvampiros")) == 0 );

	string editorial = regLibro->getEditorial();
	CPPUNIT_ASSERT( (editorial.compare("littlezzbrownzandzcompany")) == 0 );

}

void TestParserDeLibros::testObtenerPalabrasConTodosLosDatos(){
	string strLibro = generarMockLibroCompleto();
	const char *auxlibro= strLibro.c_str();
	char* libro;
	libro = const_cast<char*>(auxlibro);
	Registro* regLibro = this->parser->obtenerRegistroDeLibro((libro) );

	list<string> palabrasPatron;
	generarListaPatron(palabrasPatron);
	list<string> palabras = regLibro->getPalabras();
	bool diferencia = false;

	list<string>::iterator it1 = palabrasPatron.begin();
	list<string>::iterator it2 = palabras.begin();
	string palabra, palabraPatron;
	while (( it1 != palabrasPatron.end()) && !(diferencia)){
		while (it2 != palabras.end()){
			palabraPatron = (*it1);
			palabra = (*it2);
			it1++; it2++;
			if (palabra.compare(palabraPatron)){
				diferencia = true;
			}
		}
	}
	CPPUNIT_ASSERT_MESSAGE("La lista de palabras no es correcta", diferencia == false );
}

void TestParserDeLibros::testObtenerEditorialEnLibroSinEditorial(){
	string strLibro = generarMockLibroSinEditorial();
	const char *auxlibro= strLibro.c_str();
	char* libro;
	libro = const_cast<char*>(auxlibro);
	Registro* regLibro = this->parser->obtenerRegistroDeLibro((libro) );

	string editorial = regLibro->getEditorial();
	CPPUNIT_ASSERT_MESSAGE( "No se creó la editorial por defecto en el registro",!(editorial.empty() ) );
}

string TestParserDeLibros::generarMockLibroCompleto(){
	stringstream ss;
	ss<< "Titulo:LA MONTAÑA DE LOS VAMPIROS" << endl << "por Autor:Darren Shan"<< endl ;
	ss<< "Editorial:Little, Brown and Company" << endl;
	ss<< "Boston New York London"<< endl;
	ss<< "Palabras: -Haz el equipaje -dijo Mr. Crepsley una noche, ya tarde, mientras iba hacia su ataud-."<< endl;
	ss<< "Ya estaba acostumbrado a las inesperadas decisiones del vampiro"<< endl;
	ss<< "|" << endl;
	return  ss.str();
}

string TestParserDeLibros::generarMockLibroSinEditorial(){
	stringstream ss;
	ss<< "Titulo:LA MONTAÑA DE LOS VAMPIROS" << endl << "por Autor:Darren Shan"<< endl ;
	ss<< "Boston New York London"<< endl;
	ss<< "Palabras: -Haz el equipaje -dijo Mr. Crepsley una noche, ya tarde, mientras iba hacia su ataud-."<< endl;
	ss<< "Ya estaba acostumbrado a las inesperadas decisiones del vampiro"<< endl;
	ss<< "|" << endl;
	return  ss.str();
}
void TestParserDeLibros::generarListaPatron(list<string>& palabrasPatron){
	palabrasPatron.push_back("haz");
	palabrasPatron.push_back("equipaje");
	palabrasPatron.push_back("dijo");
	palabrasPatron.push_back("mr");
	palabrasPatron.push_back("crepsley");
	palabrasPatron.push_back("noche");
	palabrasPatron.push_back("tarde");
	palabrasPatron.push_back("iba");
	palabrasPatron.push_back("ataud");
	palabrasPatron.push_back("ya");
	palabrasPatron.push_back("acostumbrado");
	palabrasPatron.push_back("inesperadas");
	palabrasPatron.push_back("decisiones");
	palabrasPatron.push_back("vampiro");
}

