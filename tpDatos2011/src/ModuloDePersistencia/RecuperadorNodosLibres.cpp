#include "RecuperadorNodosLibres.h"


RecuperadorNodosLibres::RecuperadorNodosLibres() {

}

RecuperadorNodosLibres::RecuperadorNodosLibres (std::string path){
	this->path = path;
}

void RecuperadorNodosLibres::obtenerDatos(int &primeraHoja, vector<int>& nodosLibres){
	if (!iss.is_open()){
		iss.open(this->path.c_str());
	}
	iss.seekg(0, std::ios_base::end);
	int tamanio = iss.tellg();
	if (tamanio > 0){
		unsigned int offset = 0;
		iss.seekg(offset);
		char readData[BUFFER_NODOS_LIBRES];
		iss.read(readData, BUFFER_NODOS_LIBRES);
		hidratarPrimeraHoja(readData,offset,primeraHoja);
		hidratarNodosLibres(readData,offset,nodosLibres);
	}
}

void RecuperadorNodosLibres::hidratarPrimeraHoja(char* readData, unsigned int &offset, int& primeraHoja){
	primeraHoja = Persistencia::getEnteroDesdeBuffer(readData,offset);
}
void RecuperadorNodosLibres::hidratarNodosLibres(char* readData, unsigned int &offset, vector<int>& nodosLibres){
   int nodos = Persistencia::getEnteroDesdeBuffer(readData,offset);
   for (int i = 0; i < nodos; i++){
	   nodosLibres[i] = Persistencia::getEnteroDesdeBuffer(readData,offset);
   }
}
RecuperadorNodosLibres::~RecuperadorNodosLibres(){
	close();
}
