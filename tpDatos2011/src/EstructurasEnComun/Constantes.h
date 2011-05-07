#ifndef CONSTANTES_H_
#define CONSTANTES_H_

#define ERROR -1
#define OKEY 0
#define BASURA_RLV 33
#define TAMANIO_BUFFER 4096
#define TAM_BLOQUE 4096
#define TAM_BUFFER 4096
#define STRING_BUFFER 4096
#define STRING_BUFFER_PALABRAS 2000000
#define CUALQUIERA 33000
#define BLOQUE_LLENO 1
#define EDITORIAL "Grupo17"
#define BLOQUE_NO_LLENO 0
#define TIPO_CLAVE_NUMERICA 1
#define PATH_REG_LONG_VARIABLE "ArchivoDeRLV.txt"
#define PATH_ESPACIO_LIBRE_RLV "controlEspaciosLibresRLV.txt"
#define PATH_STOPWORDS "stopWords.txt"
#define PATH_ARCHIVO_LOG "logBookerio.txt"

/**********************Arbol B+ ***********************/
#define PORC_TAMANIO_NODO 50
#define TAM_TOTAL_NODO 4096
#define TAM_CONTROL_NODO 13
#define TAM_EFECTIVO_NODO (TAM_TOTAL_NODO - TAM_CONTROL_NODO)
#define PORCENTAJE_NODO 50
#define BUFFER_NODOS_LIBRES 4096
#define TAM_CONTROL_REGISTRO 12
#define PATH_AUTOR "Autores"
#define PATH_EDITORIAL "Editoriales"

/************************ Hash ************************/

#define PATH_TABLA_PALABRA "TablaPalabra"
#define PATH_TABLA_TITULO "TablaTitulo"
#define PATH_TMP_PALABRA "TempPalabra"
#define PATH_TMP_TITULO "TempTitulo"
#define PATH_ESP_LIBRE_PALABRA "EspLibrePalabra"
#define PATH_ESP_LIBRE_TITULO "EspLibreTitulo"
#define PATH_BLOQUES_PALABRA "BloquesPalabra"
#define PATH_BLOQUES_TITULO "BloquesTitulo"
#define TAM_CONTROL_HASH_PALABRAS 14
#define TAM_CUBO 4096
#define TAM_RANURA 16

#define OCUPADA 1
#define VACIA 0

#endif /* CONSTANTES_H_ */
