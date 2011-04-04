/*
 * HandlerArchivoBloques.h
 *
 *  Created on: 04/04/2011
 *      Author: angeles
 */

#ifndef HANDLERARCHIVOBLOQUES_H_
#define HANDLERARCHIVOBLOQUES_H_

/* CONSULTA N° 1: recupero el registro N° 10 que corresponde a la palabra "nublado", y le quiero agregar
 * un offset que referencia al nuevo libro agregado "Buen dia". Ahora bien, ese libro agregado ocupa la
 * 3ra posicion de los 10 registros que hay cargados en ese bloque, y ocupa 40 bytes. Que pasa si, luego de
 * agregar el nuevo offset, el registro pasa a medir 44 bytes, y no entra en el lugar que antes ocupaba?
 * Se lo elimina de esa posición y se lo apendea al final?
 *
 * CONSULTA N° 2: como sera el manejo de espacios libres en el archivo de bloques? supongamos que ocurre
 * un overflow de un bloque y se debe incorporar un nuevo bloque al sistema de referencias de la tabla,
 *
 * convención 1: se reutiliza un bloque que haya sido liberado previamente. En este caso, alguna sugerencia
 * para el manejo de espacios libres del archivo?
 *
 * convencion 2: no se reutiliza nada, se apendea siempre al final un nuevo bloque.
 */

class HandlerArchivoBloques {
private:

	int cant_bloques; /* incluye aquellos bloques activos y aquellos liberados */

public:

	HandlerArchivoBloques();
	virtual ~HandlerArchivoBloques() {};

	void guardar_bloque(int pos_arch);
	void recuperar_bloque(int pos_arch);

	void guardar_registro(int pos_arch, int clave);
	void recuperar_registro(int pos_arch, int clave);
};

#endif /* HANDLERARCHIVOBLOQUES_H_ */
