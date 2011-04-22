
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
						printf("-i      Tomar texto de un archivo\n");
						if (argv[2]) {
							printf("La ruta del archivo es %s \n", argv[2]);
							// handlerComandos.guardarLibroEnArchivoMaestro(argv[2]);
							printf("Bookerio: Libro guardado. \n");
						}else{
							printf("Bookerio: No se puede procesar la orden: falta ruta de archivo.\n");}
						break;}

            case 'e':   {
						printf("-e      Indexar por Editorial los libros agregados recientemente \n");
						// handlerComandos.indexarporEditoriales();
						break;}

            case 'a':   {
						printf("-a      Indexar por Autor los libros agregados recientemente \n");
						// handlerComandos.indexarPorAutores();
						break;}

            case 't':   {
						printf("-t      Indexar por Título los libros agregados recientemente \n");
						// handlerComandos.indexarPorTitulos();
						break;}

            case 'p':   {
						printf("-p      Indexar por Palabras los libros agregados recientemente \n");
						// handlerComandos.indexarPorPalabras();
						break;}

            case 'l':   {
						printf("-l      Listar todos los archivos tomados recientemente \n");
						// handlerComandos.listarLibrosIngresados();
						break;}

            case 'o':   {
						if (argv[2]) {
							printf("-o <ID> Obtener archivo por ID \n");
							// handlerComandos.obtenerLibro(argv[2]);
						}else{
							printf("Bookerio: No se puede procesar la orden: falta un parámetro.\n");}
						break;
						}

            case 'q':   {
						if (argv[2]) {
							printf("-q <ID> Quita un archivo por ID \n");
							//handlerComandos.quitarLibro(argv[2]);
						}else{
							printf("Bookerio: No se puede procesar la orden: falta un parámetro.\n");}
						break;
						}

            case 'v':   {
                        printf("-v -archivo         Ver archivos de índice\n");
                        if (argv[2]){
							opcion2 = getopt(argc,argv, "eatp?:");
							switch (opcion2){
								case 'e': {
									      printf("-e      Ver árbol de Editorial\n");
										  //handlerComandos.verArbolEditorial();
								          break;}

								case 'a': {
										  printf("-a      Ver árbol de Autor\n");
										  //handlerComandos.verArbolAutor();
										  break;}

								case 't': {
										  printf("-t      Ver hash de Título\n");
										  // handlerComandos.verHashTitulo();
										  break;}

								case 'p': {
									      printf("-p      Ver hash de Palabras\n");
									      //handlerComandos.verHashPalabras();
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
                        printf("-e      	Indexar por Editorial los libros agregados recientemente \n");
                        printf("-a      	Indexar por Autor los libros agregados recientemente \n");
                        printf("-t      	Indexar por Título los libros agregados recientemente \n");
                        printf("-p      	Indexar por Palabras los libros agregados recientemente \n");
                        printf("-l      	Listar todos los archivos tomados recientemente \n");
                        printf("-o <ID>   	Obtener archivo por ID \n");
                        printf("-q <ID>    	Quita un archivo por ID \n");
                        printf("-v -archivo         Ver archivos de índice, donde -archivo puede ser: \n");
                        printf("    -e  	Ver árbol de Editorial\n");
                        printf("    -a  	Ver árbol de Autor\n");
                        printf("    -t  	Ver hash de Título\n");
                        printf("    -p  	Ver hash de Palabras\n");
                        break;}

            case '?':   printf("Bookerio: Parámetro inválido. \nBookerio: Ingrese el parámetro -h(help) para ver la referencia de parámetros. \n"); break;
        }

    }
}


