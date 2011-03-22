#include "RecuperadorNodos.h"


RecuperadorNodos::RecuperadorNodos() {

}

RecuperadorNodos::RecuperadorNodos (std::string path){
	this->path = path;
}

Nodo * RecuperadorNodos::obtenerNodo(int nroNodo, int tipoNodo){
	if (!iss.is_open()){
		iss.open(this->path.c_str());
	}
	iss.seekg(nroNodo*TAM_TOTAL_NODO);
	char readData[TAM_TOTAL_NODO];
	iss.read(readData, TAM_TOTAL_NODO);
	if (tipoNodo == 1){
		NodoHoja * nodoHoja = new NodoHoja();
		unsigned int offsetChar = 0;
		nodoHoja->hidratar(readData, offsetChar);
		return nodoHoja;
	}else{
		NodoInterior* nodoInterior = new NodoInterior();
		unsigned int offsetChar2 = 0;
		nodoInterior->hidratar(readData, offsetChar2);
		return nodoInterior;
	}
}

RecuperadorNodos::~RecuperadorNodos(){
	close();
}
