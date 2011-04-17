#ifndef HANDLERARBOL_H_
#define HANDLERARBOL_H_
#include "../ArbolB+/ArbolBMas.h"
#include "../Hash/Hash.h"
#include "../ParserLibros/ParserDeLibros.h"
#include "../ManejadoresDeArchivos/HandlerArchivoRLV.h"

class HandlerEstructuras {

private:
	ParserDeLibros* parser;
	HandlerArchivoRLV* handler;
public:

	HandlerEstructuras();
	void insertar(string path, ArbolBMas &arbol, Hash& hash);
	void borrarEnArbol(Clave* clave, ArbolBMas &arbol);
	void buscarEnArbol(Clave* clave, ArbolBMas &arbol);
	void borrarEnHash(Clave* clave, Hash &hash);
	void buscarEnHash(Clave* clave, Hash &hash);
	virtual ~HandlerEstructuras();
};

#endif /* HANDLERARBOL_H_ */
