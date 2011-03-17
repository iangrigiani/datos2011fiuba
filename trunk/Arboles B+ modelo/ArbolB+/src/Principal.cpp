#define FIN_LINEA 	'\n'
#define FIN_CADENA 	'\0'
#define ESP_BLANCO 	' '

#define TAMANIO_BLOQUE 		128

//ERRORES
#define EXITO				0
#define ERROR_ARGS_INSUF	1
#define ERROR_FORMATO		2
#define ERROR_ORD_INDEF		3
//
#include <iostream>
#include <string.h>
#include <stdlib.h>

#include "ArbolB.h"
#include "Prueba.h"
/******* DEFINICION DE FUNCIONES AUXILIARES DE INTERFAZ *******/
void mostrarError(int codigo);
void opcionHelp();
unsigned int opcionInsertar(char* cadena, ArbolB * arbol);
unsigned int opcionModificar(char* cadena, ArbolB * arbol);
unsigned int opcionQuitar(char* cadena, ArbolB * arbol);
unsigned int opcionBuscar(char* cadena, ArbolB * arbol);
void opcionInsertarAzar(int cantidad, ArbolB * arbol);
void opcionObtenerAnterior(ArbolB * arbol);
void opcionObtenerSiguiente(ArbolB * arbol);
void opcionOPruebasDefault(ArbolB * arbol);

void setPreferenciasVolcado(int argc, char** argv , bool * full,FILE ** salida);
char * numeroToString(unsigned int);
char* leerEntrada ();
char* obtenerArgumento (char* lista, unsigned int* posicion);
int obtenerDatos(char * cadena, unsigned int * clave, char ** valor);
/******* FIN DEFINICION DE FUNCIONES AUXILIARES DE INTERFAZ *******/


//FORMATO ENTRADA
//NOMBRE ARCHIVO -COMANDO ARG1 ARG2 ARGN < INPUT
//Argv[0] es el path donde se esta ejecutando

int main( int argc, char** argv )
{

	char * nombreArchivoMaestro = NULL; // Archio donde se encuentra la estructura principal
	char * opcion = NULL;	// Opcion seleccionada
	char * entrada = NULL;
	char * actual;

	unsigned int posicion = 0;
	bool full; // ¿Muestra estructura o estructura + elementos?
	FILE * salida;

	unsigned int codigoError=0;

	//No ingreso ningun parametro
	if (argc == 1) {
		mostrarError(ERROR_ARGS_INSUF);
		return 1;
	}

	//Esta consultando la ayuda?
	if (strcmp(argv[1],"-h")==0) {
		opcionHelp();
		return EXIT_SUCCESS;
	}

	//Sino quiere consultar la ayuda debe tener al menos 3 parametros.
	//No ingreso ningun parametro
	if (argc < 3) {
		mostrarError(ERROR_ARGS_INSUF);
		return 1;
	}

	nombreArchivoMaestro = argv[1];
	opcion = argv[2];

	ArbolB * arbol = new ArbolB(nombreArchivoMaestro,TAMANIO_BLOQUE);

	if (strcmp(opcion,"-I") == 0) {
		//Insertar
		entrada = leerEntrada();

		actual = obtenerArgumento(entrada, &posicion);

		while(actual != NULL && codigoError == 0) {
			codigoError = opcionInsertar(actual,arbol);
			free(actual);
			actual = obtenerArgumento(entrada, &posicion);
		}

		free(entrada);

	} else if (strcmp(opcion,"-M") == 0) {
		//Modificar
		entrada = leerEntrada();

		actual = obtenerArgumento(entrada, &posicion);

		while(actual != NULL && codigoError == 0) {
			codigoError = opcionModificar(actual,arbol);
			free(actual);
			actual = obtenerArgumento(entrada, &posicion);
		}

		free(entrada);

	} else if (strcmp(opcion,"-Q") == 0) {
		//Quitar
		entrada = leerEntrada();

		actual = obtenerArgumento(entrada, &posicion);

		while(actual != NULL && codigoError == 0) {
			codigoError = opcionQuitar(actual,arbol);
			free(actual);
			actual = obtenerArgumento(entrada, &posicion);
		}

		free(entrada);

	} else if (strcmp(opcion,"-B") == 0) {
		//Buscar
		entrada = leerEntrada();

		actual = obtenerArgumento(entrada, &posicion);

		while(actual != NULL && codigoError == 0) {
			codigoError = opcionBuscar(actual,arbol);
			free(actual);
			actual = obtenerArgumento(entrada, &posicion);
		}

		free(entrada);
	} else if (strcmp(opcion,"-S") == 0) {
		//Volcar
		setPreferenciasVolcado(argc, argv, &full,&salida);
		arbol->visualizar(full,salida);

		if (salida != stdout) fclose(salida);

	} else if (strcmp(opcion,"-T") == 0) {
		//Inicia el iterador
		arbol->iniciarRecorridoSecuencial();

	} else if (strcmp(opcion,"-N") == 0) {
		//Obtiene el siguiente elemento
		opcionObtenerSiguiente(arbol);

	} else if (strcmp(opcion,"-L") == 0) {
		//Obtiene el elemento anterior
		opcionObtenerAnterior(arbol);

	} else if (strcmp(opcion,"-R") == 0) {
		//Agrega elementos al azar
		if (argc < 4) {
			codigoError = ERROR_ARGS_INSUF;
		} else {
			opcionInsertarAzar(atoi(argv[3]),arbol);
		}
	} else if (strcmp(opcion,"-P") == 0) {
		//Ejecuta pruebas pre definidas
		ejecutarPrueba();
	} else {
		codigoError = ERROR_ORD_INDEF;

	}
	if(codigoError!=0) {
		mostrarError(codigoError);
	}

	delete(arbol);

	return EXIT_SUCCESS;
}

void opcionHelp(){
	printf ("Estas ordenes de consola se encuentran definidas internamente.\n\n");
	printf ("archivo -I                      Insertar un elemento. Formato: (clave;valor)\n");
	printf ("archivo -B                      Buscar un elemento a partir de su clave. Formato: (clave;)\n");
	printf ("archivo -M                      Modificar un elemento. Formato: (clave;valor)\n");
	printf ("archivo -Q                      Quitar un elemento. Formato: (clave;)\n");
	printf ("archivo -T                      Inicia el recorrido secuencial a partir del primer elemento del set.\n");
	printf ("archivo -N                      Obtiene el siguiente elemento en el set-secuencial.\n");
	printf ("archivo -L                      Obtiene el anterior elemento en el set-secuencial.\n");
	printf ("archivo -R cantidadAgregar      Agregar elementos al azar\n");

	printf ("archivo -S                      Vuelca la estructura en pantalla.\n");
	printf ("           archivoDestino       Vuelca la estructura en archivoDestino.\n");
	printf ("           -FULL                Vuelca la estructura mas los datos en pantalla.\n");
	printf ("           -FULL archivoDestino Vuelca la estructura mas los datos en archivoDestino.\n");

	printf ("archivo -P                      Ejecuta pruebas default mostrandolas por pantalla.\n");

	printf ("-h                              Imprime la ayuda.\n");
}

void mostrarError(int codigo)
{
	switch(codigo){
		case ERROR_ARGS_INSUF:
		printf ("ERROR: Cantidad de argumentos insuficientes.\n");
		break;
	case ERROR_FORMATO:
		printf ("ERROR: Formato no correspondiente.\n");
		break;
	case ERROR_ORD_INDEF:
		printf ("ERROR: orden no encontrada.\n");
		break;
	default:
		printf ("ERROR: La operacion no ha podido ser procesada.\n");
		break;
	}
	printf ("Puede consultar la ayuda a traves del comando -h.\n");
}

char* leerEntrada () //Levanta todo el contenido de stdin
{
    char * argumentos = (char*) malloc (sizeof(char));
    char c = fgetc(stdin); //lee desde entrada standard

	int i = 0;
	while (c != EOF)
	{
		argumentos[i] = c;
		argumentos = (char *) realloc (argumentos, strlen(argumentos) + 1);
		c = fgetc(stdin);
		i++;
	}
	argumentos[i] = FIN_CADENA;

    return argumentos;
}

char* obtenerArgumento(char* entrada, unsigned int* posicion) {

	char * inicioBusqueda;

	char * inicio = NULL;
	char * fin = NULL;
	char * retorno;

	unsigned int longitud = 0;

	if (*posicion > strlen(entrada)) return NULL;

	inicioBusqueda = *posicion * sizeof(char) + entrada;

    inicio = strchr(inicioBusqueda,'(');
    fin = strchr(inicioBusqueda,')');

    if (inicio == NULL || fin == NULL) return NULL;

    longitud = fin - inicio + 1;

    retorno = (char *) malloc(sizeof(char) * longitud);

    memcpy(retorno,inicio,longitud);

    (*posicion)+=longitud+1;

    return retorno;
}

unsigned int opcionInsertar(char* cadena, ArbolB * arbol) {
	unsigned int clave = 0;
	char* valor;

	if (obtenerDatos(cadena,&clave, &valor) && valor!=NULL) {
		ArbolB::Resultado resultado = arbol->Insertar(clave, valor, strlen(valor) + 1); //se tiene en cuenta el '\0'

		if(resultado == ArbolB::OPERACION_EXITOSA) {
			printf("Se inserto el elemento '%s' con clave %d\n", valor, clave);
		} else {
			printf("No se pudo insertar el elemento '%s' con clave %d\n", valor, clave);
		}

		free(valor);
		return EXITO;
	} else {
		return ERROR_FORMATO;

	}
}

unsigned int opcionModificar(char* cadena, ArbolB * arbol) {
	unsigned int clave = 0;
	char* valor;

	if (obtenerDatos(cadena,&clave, &valor) && valor !=NULL) {

		ArbolB::Resultado resultado = arbol->Modificar(clave, valor, strlen(valor) + 1); //se tiene en cuenta el '\0'

		if(resultado == ArbolB::OPERACION_EXITOSA) {
			printf("Se modifico el elemento '%s' con clave %d\n", valor, clave);
		} else {
			printf("No se pudo modificar el elemento '%s' con clave %d\n", valor, clave);
		}

		free(valor);

		return EXITO;
	} else {
		return ERROR_FORMATO;
	}
}

unsigned int opcionQuitar(char* cadena, ArbolB * arbol) {
	unsigned int clave = 0;
	char* valor;

	if (obtenerDatos(cadena,&clave, &valor)) {

		ArbolB::Resultado resultado = arbol->suprimir(clave);

		if(resultado == ArbolB::OPERACION_EXITOSA) {
			printf("Se quito el elemento con clave %d\n", clave);
		} else {
			printf("No se pudo quitar el elemento con clave %d\n", clave);
		}

		free(valor);
		return EXITO;
	} else {
		return ERROR_FORMATO;
	}
}

int obtenerDatos(char * cadena, unsigned int * clave, char ** valor) {
	char * inicio = NULL;
	char * fin = NULL;
	char * medio = NULL;

	char * aux;

	int longitudClave = 0;
	int longitudValor = 0;

	inicio = strchr(cadena,'(');
	medio = strchr(cadena,';');
	fin = strchr(cadena,')');

	if (inicio == NULL || medio == NULL || fin == NULL) return 0;

	longitudClave = medio - inicio;
	longitudValor = fin - medio;

	aux = (char *) malloc(sizeof(char) * longitudClave);
	aux[0] = '\0';
	strncat(aux, (inicio + sizeof(char)),longitudClave - 1);

	(*clave) = atoi(aux);

	if (longitudValor > 1) {
		(*valor) = (char *) malloc(sizeof(char) * longitudValor);
		(*valor)[0] = '\0';
		strncat(*valor, (medio + sizeof(char)), longitudValor - 1);
	} else {
		(*valor)=NULL;
	}

	return 1;
}

void setPreferenciasVolcado(int argc, char** argv , bool * full,FILE ** salida){
	//1) -S  < salida por pantalla, no todos los lementos
	//2) -S -FULL < salida por pantalla completa
	//3) -S nombreArchivo < salida por archivo no full
	//4a) -S -FULL nombreArchivo < salida completa al archivo
	//4b) -S nombreArchivo -FULL < salida completa al archivo

	if (argc == 3) {
		//1)
		(*full) = false;
		(*salida) = stdout;
	} else if (argc == 4) {
		//2) o 3)

		if (strcmp(argv[3],"-FULL")==0) {
			(*full) = true;
			(*salida) = stdout;
		} else {
			(*full) = false;
			(*salida) = fopen(argv[3],"a");
		}

	} else if (argc == 5) {
		//4
		(*full) = true;
		if (strcmp(argv[4],"-FULL")==0) {
			//4a)
			(*salida) = fopen(argv[3],"a");
		} else {
			//4b)
			(*salida) = fopen(argv[4],"a");
		}

	}
}

unsigned int opcionBuscar(char* cadena, ArbolB * arbol) {
	unsigned int clave = 0;
	char* valor;
	char * resultado;
	unsigned int claveDevuelta;

	if (obtenerDatos(cadena,&clave, &valor)) {

		resultado = (char*) arbol->Buscar(clave,&claveDevuelta);

		if(resultado == NULL) {
			printf("No se ha encontrado la clave (ni una superior) %d.\n",clave);
		} else if (clave == claveDevuelta){
			printf("Clave encontrada. Elemento %i: %s.\n",claveDevuelta, resultado);
		} else {
		printf("Clave no encontrada. Resultado aproximado con clave %i: %s.\n",claveDevuelta, resultado);
			free(resultado);
		}

		free(valor);

		return EXITO;
	} else {
		return ERROR_FORMATO;
	}
}

void opcionInsertarAzar(int cantidad, ArbolB * arbol) {

	unsigned int clave;
	char * valor;
	int agregados = 0;

	while (agregados < cantidad) {
			clave = rand() % 99999 + 1;

			valor = numeroToString(clave);

			//Por si se generan duplicados
			if (arbol->Insertar(clave, valor, strlen(valor)+1) == ArbolB::OPERACION_EXITOSA) {
				agregados++;
			}

			free(valor);
	}

	printf("Se han agregado %i elementos.\n",agregados);
}

void opcionObtenerSiguiente(ArbolB * arbol) {

	if (arbol->tieneSiguiente()) {
		char * resultado;
		unsigned int clave;
		resultado = (char*) arbol->getSiguiente(&clave);
		printf("Resultado: (%i,%s)\n",clave,resultado);
	} else {
		printf("No hay siguiente.\n");
	}

}

void opcionObtenerAnterior(ArbolB * arbol) {

	if (arbol->tieneAnterior()) {
		char * resultado;
		unsigned int clave;
		resultado = (char*) arbol->getAnterior(&clave);
		printf("Resultado: (%i,%s)\n",clave,resultado);
	} else {
		printf("No hay anterior.\n");
	}

}

char * numeroToString(unsigned int numero) {
	//Obtengo la cantidad de digitos que tiene el numero
	unsigned int temp;
	unsigned int cantidadDigitos = 0;
	char * numeroS = NULL;

	temp=numero;

	while (temp > 0) {
		temp/=10;
		cantidadDigitos++;
	}
	//Paso de int a chr
	numeroS = (char*) malloc (sizeof(char)* (cantidadDigitos+1));
	sprintf(numeroS,"%i",numero);
	numeroS[cantidadDigitos]='\0';

	return numeroS;
}
