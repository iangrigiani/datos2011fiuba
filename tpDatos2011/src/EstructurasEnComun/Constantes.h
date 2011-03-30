#ifndef CONSTANTES_H_
#define CONSTANTES_H_

#define ERROR -1
#define OK 0
#define TAMANIO_BUFFER 32768
#define STRING_BUFFER 32768
#define BLOQUE_LLENO 1
#define BLOQUE_NO_LLENO 0
#define TIPO_CLAVE_NUMERICA 1
#define TAM_TOTAL_NODO 512
#define TAM_CONTROL_NODO 12
#define TAM_EFECTIVO_NODO (TAM_TOTAL_NODO - TAM_CONTROL_NODO)
#define PORCENTAJE_NODO 50
#define PATH_CONFIGURACION "ArchivoConfiguracion.cnf"
#define PATH_NODOS "Archivo_Nodos.txt"
#define BUFFER_NODOS_LIBRES 128
#define TAM_CONTROL_REGISTRO 5
#define PATH_REG_LONG_VARIABLE "ArchivoRegistrosLongVariable.txt"
#endif /* CONSTANTES_H_ */
