/*
 * Main.cpp
 *
 *  Created on: 22/04/2011
 *      Author: andrea
 */


#include "HandlerEstructuras.h"
#include <iostream>
#include <stdio.h>
#include <cstring>
#include <string>
#include <unistd.h>

using namespace std;


int main (int argc , char *argv[]){
	int i = 1 ;
    int opcion, opcion2;
    if ((argc!= 2) && (argc!=3) ) {
        printf("Bookerio: Cantidad errónea de parámetros. Sólo puede pasar un parámetro. \n");
        printf("Bookerio: Ingrese el parámetro -h(elp) para ver la referencia de parámetros. \n");
    }else{
        (opcion = getopt(argc,argv, "ieatploqvh?:")) ;
        switch ( opcion ) {
            case 'i':   printf("-i      Tomar texto de un archivo\n"); break;

            case 'e':   printf("-e      Indexar por Editorial los libros agregados recientemente \n"); break;

            case 'a':   printf("-a      Indexar por Autor los libros agregados recientemente \n"); break;

            case 't':   printf("-t      Indexar por Título los libros agregados recientemente \n"); break;

            case 'p':   printf("-p      Indexar por Palabras los libros agregados recientemente \n"); break;

            case 'l':   printf("-l      Listar todos los archivos tomados recientemente \n"); break;

            case 'o':   printf("-o      Obtener archivo por ID \n"); break;

            case 'q':   printf("-q      Quita un archivo por ID \n"); break;

            case 'v':   {
                        printf("-v -archivo         Ver archivos de índice\n");
                        opcion2 = getopt(argc,argv, "eatp?:");
                        switch (opcion2){
                            case 'e': printf("-e      Indexar por Editorial\n"); break;
                            case 'a': printf("-a      Indexar por Autor\n"); break;
                            case 't': printf("-t      Indexar por Título \n"); break;
                            case 'p': printf("-p      Indexar por Palabras\n"); break;
                            case '?': {
                                      printf("Bookerio: Parámetro inválido. \n");
                                      printf(" Bookerio: Ingrese el parámetro -r para ver la referencia de parámetros.\n");
                                      break;}
                            }
                        break;
                        }

            case 'h': {
                        printf("Parámetros válidos: \n");
                        printf("-i      Tomar texto de un archivo\n");
                        printf("-e      Indexar por Editorial los libros agregados recientemente \n");
                        printf("-a      Indexar por Autor los libros agregados recientemente \n");
                        printf("-t      Indexar por Título los libros agregados recientemente \n");
                        printf("-p      Indexar por Palabras los libros agregados recientemente \n");
                        printf("-l      Listar todos los archivos tomados recientemente \n");
                        printf("-o      Obtener archivo por ID \n");
                        printf("-q      Quita un archivo por ID \n");
                        printf("-v -archivo         Ver archivos de índice, donde -archivo puede ser: \n");
                        printf("    -e  Ver árbol de Editorial\n");
                        printf("    -a  Ver árbol de Autor\n");
                        printf("    -t  Ver hash de Título\n");
                        printf("    -p  Ver hash de Palabras\n");
                        break;}

            case '?':   printf("Bookerio: Parámetro inválido. \nBookerio: Ingrese el parámetro -h(help) para ver la referencia de parámetros. \n"); break;
        }

}
}


