#include "ManejadoresInforme/HandlerComandos.h"
#include <iostream>
#include <stdio.h>
#include <cstring>
#include <string>
#include <unistd.h>

using namespace std;

int main (int argc , char *argv[]){

/* TODO cambiar printfs por métodos de HandlerComandos*/
        HandlerComandos* handlerComandos = new HandlerComandos();

    int opcion1, opcion2;
    if ((argc!= 2) && (argc!=3) ) {
        printf("Bookerio: Cantidad errónea de parámetros. Sólo puede pasar un parámetro o ");
        printf("dos en caso de -v(er) o de -i(ngresar). \n");
        printf("Bookerio: Ingrese el parámetro -h(elp) para ver la referencia de parámetros. \n");
    }else{
        (opcion1 = getopt(argc,argv, "ieatploqvh?:")) ;
        switch ( opcion1 ) {
            case 'i':   {
                                                if (argv[2]) {
                                                        handlerComandos->guardarLibroEnArchivoMaestro(argv[2]);
                                                        printf("Bookerio: Libro guardado. \n");
                                                }else{
                                                        printf("Bookerio: No se puede procesar la orden: falta ruta de archivo.\n");}
                                                break;}

            case 'e':   {
                                                printf("Bookerio: Indexando por Editorial los libros agregados recientemente \n");
                                                handlerComandos->indexar('e');
                                                printf("Bookerio: Fin de indexado por Editorial.\n");
                                                break;}

            case 'a':   {
                                                printf("Bookerio: Indexando por Autor los libros agregados recientemente \n");
                                                handlerComandos->indexar('a');
                                                printf("Bookerio: Fin de indexado por Autor.\n");
                                                break;}

            case 't':   {
                                                printf("Bookerio: Indexando por Título los libros agregados recientemente \n");
                                                handlerComandos->indexar('t');
                                                printf("Bookerio: Fin de indexado por Título.\n");
                                                break;}

            case 'p':   {
                                                printf("Bookerio: Indexando por Palabras los libros agregados recientemente \n");
                                                handlerComandos->indexar('p');
                                                printf("Bookerio: Fin de indexado por Palabras.\n");
                                                break;}

            case 'l':   {
                                                printf("Bookerio: Listando todos los archivos tomados recientemente \n");
                                                handlerComandos->listarLibrosIngresados();
                                                printf("Bookerio: Fin de listado de libros tomados recientemente.\n");
                                                break;}

            case 'o':   {
                                                if (argv[2]) {
                                                        printf("Bookerio: Obtener Libro %s \n", argv[2]);
                                                        handlerComandos->obtenerLibro(atoi(argv[2]));
                                                        printf("Bookerio: Obtener Libro %s \n", argv[2]);
                                                }else{
                                                        printf("Bookerio: No se puede procesar la orden: falta un parámetro.\n");}
                                                break;}

            case 'q':   {
                                                if (argv[2]) {
                                                        printf("-q <ID> Quita un archivo por ID \n");
                                                        handlerComandos->quitarLibro(atoi(argv[2]));
                                                }else{
                                                        printf("Bookerio: No se puede procesar la orden: falta un parámetro.\n");}
                                                break;}

            case 'v':   {
                        printf("-v -archivo         Ver archivos de índice\n");
                        if (argv[2]){
                                                        opcion2 = getopt(argc,argv, "eatp?:");
                                                        switch (opcion2){
                                                                case 'e': {
                                                                              printf("Bookerio: Viendo estructura de árbol de Editoriales.\n");
                                                                                  handlerComandos->verEstructura('e');
                                                                                  printf("Bookerio: Fin de estructura de árbol de Editoriales.\n");
                                                                          break;}

                                                                case 'a': {
                                                                                  printf("Bookerio: Viendo estructura de árbol de Autores.\n");
                                                                                  handlerComandos->verEstructura('a');
                                                                                  printf("Bookerio: Fin de estructura de árbol de Autores.\n");
                                                                                  break;}

                                                                case 't': {
                                                                                  printf("Bookerio: Viendo estructura de hash de Títulos.\n");
                                                                                  handlerComandos->verEstructura('t');
                                                                                  printf("Bookerio: Fin de estructura de hash de Títulos.\n");
                                                                                  break;}

                                                                case 'p': {
                                                                                  printf("Bookerio: Viendo estructura de hash de Palabras.\n");
                                                                              handlerComandos->verEstructura('p');
                                                                              printf("Bookerio: Fin de estructura de hash de Palabras.\n");
                                                                              break;}

                                                                case '?': {
                                                                                  printf("Bookerio: Parámetro inválido. \n");
                                                                                  printf(" Bookerio: Ingrese el parámetro -r para ver la referencia de parámetros.\n");
                                                                                  break;}
                                                                }
                        }else{
                                printf("Bookerio: No se puede procesar la orden: falta un parámetro.\n");}
                                                break;
                                                }

            case 'h': {
                        printf("Parámetros válidos: \n");
                        printf("-i <ruta>   Tomar texto de un archivo\n");
                        printf("-e              Indexar por Editorial los libros agregados recientemente \n");
                        printf("-a              Indexar por Autor los libros agregados recientemente \n");
                        printf("-t              Indexar por Título los libros agregados recientemente \n");
                        printf("-p              Indexar por Palabras los libros agregados recientemente \n");
                        printf("-l              Listar todos los archivos tomados recientemente \n");
                        printf("-o <ID>         Obtener archivo por ID \n");
                        printf("-q <ID>         Quita un archivo por ID \n");
                        printf("-v -archivo         Ver archivos de índice, donde -archivo puede ser: \n");
                        printf("    -e          Ver árbol de Editorial\n");
                        printf("    -a          Ver árbol de Autor\n");
                        printf("    -t          Ver hash de Título\n");
                        printf("    -p          Ver hash de Palabras\n");
                        break;}

            case '?':   printf("Bookerio: Parámetro inválido. \nBookerio: Ingrese el parámetro -h(help) para ver la referencia de parámetros. \n"); break;
        }

    }
    delete handlerComandos;
}

