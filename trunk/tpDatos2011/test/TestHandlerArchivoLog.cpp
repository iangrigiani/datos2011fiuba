
#ifdef ECUT_MAIN
#include "TestHandlerArchivoLog.h"
#include <stdlib.h>
#include <list>


CPPUNIT_TEST_SUITE_REGISTRATION(TestHandlerArchivoLog);


void TestRoad::testInsertarRegistro(){
	HandlerArchivoLog* handler = new HandlerArchivoLog();
	handler->insertarRegistro(300);
	handler->insertarRegistro(301);
	handler->insertarRegistro(302);
	list<int> listaInsertados;
	handler->obtenerListaIDs(listaInsertados);
	list<int>::iterator it = listaInsertados.begin();
	while ( it != listaDeIds.end()){
		i++;
		it++;
	}
	CPPUNIT_ASSERT(i == 3);
	delete handler;
}

void TestRoad::testBuscarRegistro() {
	HandlerArchivoLog* handler = new HandlerArchivoLog();
	int puntero = 0;
	puntero = handler->buscarRegistro(301);
	CPPUNIT_ASSERT(puntero == 13);
	delete handler;
}

void TestRoad::testSetearIndexado() {
	HandlerArchivoLog* handler = new HandlerArchivoLog();
	handler->setearIndexado(301, 'a');
	bool encontrado = false;
	list<int>::iterator it = listaInsertados.begin();
	while ( it != listaDeIds.end()){
		if (it== 301) {
			encontrado == true;
		}
	}
	CPPUNIT_ASSERT(encontrado == true);
	delete handler;
}

void TestRoad::testObtenerListaIDs() {
/*	Edge  edge1("1", oVertex, dVertex);
	Edge  edge2("2", oVertex, dVertex);
	aRoad->addEdge(&edge1, 100, 200, *oIntersection, *dIntersection);
	aRoad->addEdge(&edge2, 199, 300, *oIntersection, *dIntersection);*/
}

void TestRoad::testObtenerListaIDsAIndexar() {
/*	Edge  edge1("1", oVertex, dVertex);
	Edge  edge2("2", oVertex, dVertex);
	Edge  edge3("3", oVertex, dVertex);
	aRoad->addEdge(&edge1, 100, 200, *oIntersection, *dIntersection);
	aRoad->addEdge(&edge2, 100, 200, *oIntersection, *dIntersection);
	aRoad->addEdge(&edge3, 000, 100, *oIntersection, *dIntersection);
	util::LinkedList<RoadSegment*>* segments = aRoad->getSegments(150);
	CPPUNIT_ASSERT(segments->count() == 1);
	CPPUNIT_ASSERT(segments->get(0)->getIncreasingEdges()->count() == 2);
	CPPUNIT_ASSERT(segments->get(0)->getDecreasingEdges()->count() == 0);
	EqualMatcher<Edge*> matcher;
	util::LinkedList<Edge*>* edges = segments->get(0)->getIncreasingEdges();
	CPPUNIT_ASSERT(edges->contains(matcher.setCurrent(&edge1)));
	CPPUNIT_ASSERT(edges->contains(matcher.setCurrent(&edge2)));*/
}

#endif /* ECUT_MAIN */

