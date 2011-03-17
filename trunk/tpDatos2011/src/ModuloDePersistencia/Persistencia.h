#ifndef UTIL_H_
#define UTIL_H_
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <iostream>
#include "../EstructurasEnComun/Constantes.h"
#include <string>

class Persistencia {
private:
	Persistencia(){}
	virtual ~Persistencia(){}
public:

	static int getTamanioEntero(unsigned int dato){
		int resultado = dato / 10;
		int cant = 1;
		while (resultado > 0){
			resultado = resultado / 10;
			cant ++;
		}
		return cant;
	}
	static unsigned int getEnteroDesdeBuffer(char buffer[STRING_BUFFER], unsigned int &inicioOffset){
		unsigned int tamanioCargado;
		sscanf(&buffer[inicioOffset], "%u ", &tamanioCargado);
		inicioOffset += getTamanioEntero(tamanioCargado) + 1;
		return tamanioCargado;
	}

	static void PonerEnteroEnChar(char buffer[STRING_BUFFER], unsigned int &inicioOffset, unsigned int dato){
		sprintf(&buffer[inicioOffset], "%u ", dato);
		inicioOffset += getTamanioEntero(dato) + 1;
	}


	static void PonerStringEnChar(char buffer[STRING_BUFFER], unsigned int &offset, char * dato){
		unsigned int tamanio = strlen(dato);
	    PonerEnteroEnChar(buffer, offset, tamanio);
	    unsigned int  i;
	    for (i = offset; i< tamanio+offset; i++){
	        buffer[i] = dato[i-offset];
	    }
	    offset += tamanio;
	}

	static std::string getStringDesdeBuffer(char buffer[STRING_BUFFER], unsigned int &inicioOffset){

	    char * loadedCharDos=new char [sizeof(char)*STRING_BUFFER];
	    int tamanioCargado = getEnteroDesdeBuffer(buffer, inicioOffset);
	    unsigned int i;
	    for (i=inicioOffset ; i< inicioOffset + tamanioCargado; i++){
	        loadedCharDos[i- inicioOffset]=buffer[i];
	    }
	    loadedCharDos[i-inicioOffset]='\0';
	    inicioOffset += tamanioCargado;
	    std::string string = loadedCharDos;
	    delete[] loadedCharDos;
	    return string;
	}


};

#endif /* UTIL_H_ */
