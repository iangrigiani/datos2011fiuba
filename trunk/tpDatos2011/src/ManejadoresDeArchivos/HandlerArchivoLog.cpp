/*
 * HandlerArchivoLog.cpp
 *
 *  Created on: 22/04/2011
 *      Author: andrea
 */


#include "HandlerArchivoLog.h"
#include <sstream>
#include <fstream>
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../EstructurasEnComun/Constantes.h"


HandlerArchivoLog::HandlerArchivoLog() {
	// TODO Auto-generated constructor stub
}

HandlerArchivoLog::~HandlerArchivoLog() {
	// TODO Auto-generated destructor stub
}

void HandlerArchivoLog::insertarRegistro(int IDArchivo){
	string linea = crearStringAInsertar(IDArchivo, 0, 0, 0, 0);
	ofstream archivoLog;
	archivoLog.open(PATH_ARCHIVO_LOG,std::ios_base::app);
	archivoLog.write(linea.c_str(), linea.length());
	archivoLog.close();
}

int HandlerArchivoLog::buscarRegistro(int IDArchivo){

    bool registroEncontrado = false ;
	char* cadena = (char*)calloc(100, sizeof(char));
    string cad;
    int puntero = 0 , IDActual= 0 ;

    fstream archivoLog;
	archivoLog.open(PATH_ARCHIVO_LOG, std::ios_base::in | std::ios_base::out);
    archivoLog.seekg(0);

	while (!registroEncontrado && !archivoLog.eof() ){
        puntero = archivoLog.tellg();
		archivoLog.getline (cadena, 100);
        cad = cadena;
        if (cad.length() > 0 ) {
            IDActual= atoi(strtok(cadena,"|"));
            if (IDActual == IDArchivo){
                registroEncontrado = true;
            }
	    }
    }
	archivoLog.close();
	if(!registroEncontrado){
		puntero = -1;
	}
    return puntero;
}


void HandlerArchivoLog::setearIndexado(int IDArchivo, int parametro){
    int puntero = buscarRegistro(IDArchivo);
    int ID= 0, ind1=0 , ind2=0, ind3=0, ind4=0;
    char* cadena = (char*)calloc(100, sizeof(char));
    string linea;

    fstream archivoLog;
	archivoLog.open(PATH_ARCHIVO_LOG, std::ios_base::in | std::ios_base::out);
    archivoLog.seekg(puntero);
    archivoLog.getline(cadena,100);

    ID = atoi(strtok(cadena,"|"));
    ind1 = atoi ( strtok(NULL,"|") );
    ind2 = atoi ( strtok(NULL,"|") );
    ind3 = atoi ( strtok(NULL,"|") );
    ind4 = atoi ( strtok(NULL,"\n") );

    switch (parametro){
        case 'a':{ ind1 = 1; break;}

        case 'e':{ ind2 = 1; break;}

        case 't':{ ind3 = 1; break;}

        case 'p':{ ind4 = 1; break;}

    }
    linea = crearStringAInsertar(IDArchivo, ind1, ind2, ind3, ind4);
    archivoLog.seekp(puntero);
	archivoLog.write(linea.c_str(), linea.length());
    archivoLog.close();

}


string HandlerArchivoLog::crearStringAInsertar(int numero, int ind1, int ind2, int ind3, int ind4){
   stringstream ss;
   ss << numero  << "|" << ind1 << "|" << ind2 << "|" << ind3 << "|" << ind4 << "\n"  ;
   return ss.str();
}
