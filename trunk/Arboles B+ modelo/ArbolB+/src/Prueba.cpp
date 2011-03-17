//============================================================================
// Name        : Prueba.cpp
// Author      : Grupo Klow
// Version     :
// Description : Modulo que prueba el funcionamiento del Arbol B+
//============================================================================

#include <iostream>
#include <string.h>
#include <stdlib.h>

#include "ArbolB.h"
#include "Prueba.h"

using namespace std;

//Funcion auxiliar para la prueba, agrega elementos int al arbol
void agregarElemetnosArbol(ArbolB* arbol){

	//inseerto elementos al arbol
	int dato = 20;
	arbol->Insertar(dato,&dato,sizeof(dato));
	dato = 33;
	arbol->Insertar(dato,&dato,sizeof(dato));
	dato = 49;
	arbol->Insertar(dato,&dato,sizeof(dato));
	dato = 57;
	arbol->Insertar(dato,&dato,sizeof(dato));
	dato = 90;
	arbol->Insertar(dato,&dato,sizeof(dato));
	dato = 47;
	arbol->Insertar(dato,&dato,sizeof(dato));
	dato = 30;
	arbol->Insertar(dato,&dato,sizeof(dato));
	dato = 17;
	arbol->Insertar(dato,&dato,sizeof(dato));
	dato = 35;
	arbol->Insertar(dato,&dato,sizeof(dato));
	dato = 10;
	arbol->Insertar(dato,&dato,sizeof(dato));
	dato = 21;
	arbol->Insertar(dato,&dato,sizeof(dato));
	dato = 40;
	arbol->Insertar(dato,&dato,sizeof(dato));
	dato = 80;
	arbol->Insertar(dato,&dato,sizeof(dato));
	dato = 56;
	arbol->Insertar(dato,&dato,sizeof(dato));
	dato = 8;
	arbol->Insertar(dato,&dato,sizeof(dato));
	dato = 39;
	arbol->Insertar(dato,&dato,sizeof(dato));
	dato = 43;
	arbol->Insertar(dato,&dato,sizeof(dato));
	dato = 60;
	arbol->Insertar(dato,&dato,sizeof(dato));
	dato = 4;
	arbol->Insertar(dato,&dato,sizeof(dato));
	dato = 31;
	arbol->Insertar(dato,&dato,sizeof(dato));
	dato = 99;
	arbol->Insertar(dato,&dato,sizeof(dato));
	dato = 1;
	arbol->Insertar(dato,&dato,sizeof(dato));
	dato = 2;
	arbol->Insertar(dato,&dato,sizeof(dato));
	dato = 11;
	arbol->Insertar(dato,&dato,sizeof(dato));

}

void ejecutarPrueba() {

	{
		/**
		 * PRUEBA 2: Modificacion de elementos
		 */

		cout <<endl<<"*****          PRUEBA 1          ******";
		cout <<endl<<"*****  Eliminacion de elementos  ******"<<endl;
		cout <<      "***************************************"<<endl;

		char nombreArchivo[20] = "pruebas.dat";
		int dato;
		//Creo el arbol con bloque de 64 bytes
		ArbolB  arbol(nombreArchivo,64);
		//agrego elementos
		agregarElemetnosArbol(&arbol);

		cout <<endl<<"* Arbol a Probar * "<<endl;
		cout <<endl<<"***********    Arbol b+    ***********"<<endl;
		arbol.visualizar();
		cout <<endl<<"**************************************"<<endl;


		cout <<endl<<"* Elimino el elemento de clave 2 : baja con rotacion a izq en hoja * "<<endl;
		arbol.suprimir(2);
		cout <<endl<<"***********    Arbol b+    ***********"<<endl;
		arbol.visualizar();
		cout <<endl<<"**************************************"<<endl;

		cout <<endl<<"* Elimino el elemento de clave 11 : baja normal * "<<endl;
		arbol.suprimir(11);
		cout <<endl<<"***********    Arbol b+    ***********"<<endl;
		arbol.visualizar();
		cout <<endl<<"**************************************"<<endl;

		cout <<endl<<"* Elimino el elemento de clave 4 : baja con concatenacion en hoja a izq * "<<endl;
		arbol.suprimir(4);
		cout <<endl<<"***********    Arbol b+    ***********"<<endl;
		arbol.visualizar();
		cout <<endl<<"**************************************"<<endl;



		cout <<endl<<"* Elimino el elemento de clave 40 : baja normal * "<<endl;
		arbol.suprimir(40);
		cout <<endl<<"***********    Arbol b+    ***********"<<endl;
		arbol.visualizar();
		cout <<endl<<"**************************************"<<endl;

		cout <<endl<<"* Intento eliminar nuevamente el 40 : no hay baja dado que no existe * "<<endl;
		arbol.suprimir(40);
		cout <<endl<<"***********    Arbol b+    ***********"<<endl;
		arbol.visualizar();
		cout <<endl<<"**************************************"<<endl;



		cout <<endl<<"* Elimino el elemento de clave 17 y 20: baja con redistribucion a derecha en hoja * "<<endl;
		arbol.suprimir(17);
		arbol.suprimir(20);
		cout <<endl<<"***********    Arbol b+    ***********"<<endl;
		arbol.visualizar();
		cout <<endl<<"**************************************"<<endl;


		cout <<endl<<"* Inserto 32 y 34 * "<<endl;
		dato = 32;
		arbol.Insertar(dato,&dato,sizeof(dato));
		dato = 34;
		arbol.Insertar(dato,&dato,sizeof(dato));
		cout <<endl<<"***********    Arbol b+    ***********"<<endl;
		arbol.visualizar();
		cout <<endl<<"**************************************"<<endl;

		cout <<endl<<"* Elimino el elemento de clave el 34: baja normal * "<<endl;
		arbol.suprimir(34);
		cout <<endl<<"***********    Arbol b+    ***********"<<endl;
		arbol.visualizar();
		cout <<endl<<"**************************************"<<endl;

		cout <<endl<<"* Elimino el elemento de clave el 35: baja con concatenacion en hoja a der * "<<endl;
		arbol.suprimir(35);
		cout <<endl<<"***********    Arbol b+    ***********"<<endl;
		arbol.visualizar();
		cout <<endl<<"**************************************"<<endl;


		cout <<endl<<"* Elimino el elemento de clave el 39: baja normal * "<<endl;
		arbol.suprimir(39);
		cout <<endl<<"***********    Arbol b+    ***********"<<endl;
		arbol.visualizar();
		cout <<endl<<"**************************************"<<endl;


		cout <<endl<<"* Inserto 100 y 110* "<<endl;
		dato = 100;
		arbol.Insertar(dato,&dato,sizeof(dato));
		dato = 110;
		arbol.Insertar(dato,&dato,sizeof(dato));
		cout <<endl<<"***********    Arbol b+    ***********"<<endl;
		arbol.visualizar();
		cout <<endl<<"**************************************"<<endl;

		cout <<endl<<"* Elimino el elemento de clave el 33: baja con concatenacion en hoja a izq y rotacion a izq interno * "<<endl;
		arbol.suprimir(33);
		cout <<endl<<"***********    Arbol b+    ***********"<<endl;
		arbol.visualizar();
		cout <<endl<<"**************************************"<<endl;


		cout <<endl<<"* Inserto 33 y 34* "<<endl;
		dato = 33;
		arbol.Insertar(dato,&dato,sizeof(dato));
		dato = 34;
		arbol.Insertar(dato,&dato,sizeof(dato));
		cout <<endl<<"***********    Arbol b+    ***********"<<endl;
		arbol.visualizar();
		cout <<endl<<"**************************************"<<endl;

		cout <<endl<<"* Elimino el elemento de clave el 49: baja con concatenacion en hoja y rotacion a der interno * "<<endl;
		arbol.suprimir(49);
		cout <<endl<<"***********    Arbol b+    ***********"<<endl;
		arbol.visualizar();
		cout <<endl<<"**************************************"<<endl;

		cout <<endl<<"* Inserto del 120 al 129 * "<<endl;
		for (int var = 0; var < 10; ++var) {
			dato = var +120;
			arbol.Insertar(dato,&dato,sizeof(dato));
		}
		cout <<endl<<"***********    Arbol b+    ***********"<<endl;
		arbol.visualizar();
		cout <<endl<<"**************************************"<<endl;


		cout <<endl<<"* Elimino el elemento de clave el 121: baja con concatenacion en hoja * "<<endl;
		arbol.suprimir(121);
		cout <<endl<<"***********    Arbol b+    ***********"<<endl;
		arbol.visualizar();
		cout <<endl<<"**************************************"<<endl;

		cout <<endl<<"* Elimino el elemento de clave el 110,120: baja normal y baja con concatenacion interno der * "<<endl;
		arbol.suprimir(110);
		arbol.suprimir(120);
		cout <<endl<<"***********    Arbol b+    ***********"<<endl;
		arbol.visualizar();
		cout <<endl<<"**************************************"<<endl;

		cout <<endl<<"* Inserto del 130 al 139 * "<<endl;
		for (int var = 0; var < 10; ++var) {
			dato = var +130;
			arbol.Insertar(dato,&dato,sizeof(dato));
		}
		cout <<endl<<"***********    Arbol b+    ***********"<<endl;
		arbol.visualizar();
		cout <<endl<<"**************************************"<<endl;

		cout <<endl<<"* Elimino el elemento de clave  8: baja con concatenacion interno * "<<endl;
		arbol.suprimir(8);
		cout <<endl<<"***********    Arbol b+    ***********"<<endl;
		arbol.visualizar();
		cout <<endl<<"**************************************"<<endl;

		cout <<endl<<"* Elimino el elemento de clave  1: baja normal * "<<endl;

		arbol.suprimir(1);
		cout <<endl<<"***********    Arbol b+    ***********"<<endl;
		arbol.visualizar();
		cout <<endl<<"**************************************"<<endl;

		cout <<endl<<"* Elimino el elemento de clave el 10: baja con concatenacion hoja * "<<endl;
		arbol.suprimir(10);
		cout <<endl<<"***********    Arbol b+    ***********"<<endl;
		arbol.visualizar();
		cout <<endl<<"**************************************"<<endl;


		cout <<endl<<"* Elimino  elementos * "<<endl;
		arbol.suprimir(21);
		arbol.suprimir(30);
		arbol.suprimir(31);
		arbol.suprimir(32);
		arbol.suprimir(33);
		arbol.suprimir(34);
		arbol.suprimir(56);
		arbol.suprimir(57);
		arbol.suprimir(70);
		arbol.suprimir(43);
		arbol.suprimir(47);
		arbol.suprimir(60);
		arbol.suprimir(80);
		arbol.suprimir(90);
		arbol.suprimir(99);
		arbol.suprimir(100);
		arbol.suprimir(122);
		cout <<endl<<"***********    Arbol b+    ***********"<<endl;
		arbol.visualizar();
		cout <<endl<<"**************************************"<<endl;

		cout <<endl<<"* Elimino  123: reduccion de nivel * "<<endl;
		arbol.suprimir(123);
		cout <<endl<<"***********    Arbol b+    ***********"<<endl;
		arbol.visualizar();
		cout <<endl<<"**************************************"<<endl;


		cout <<endl<<"* Muestro el arbol y los elementos que contiene * "<<endl;
		cout <<endl<<"***********    Arbol b+    ***********"<<endl;
		arbol.visualizar(true);
		cout <<endl<<"**************************************"<<endl;

		cout <<endl<<"* Se eliminan todos los elementos * "<<endl;
		arbol.suprimir(131);
		arbol.suprimir(133);
		arbol.suprimir(135);
		arbol.suprimir(137);
		arbol.suprimir(139);
		arbol.suprimir(132);
		arbol.suprimir(124);
		arbol.suprimir(125);
		arbol.suprimir(126);
		arbol.suprimir(129);
		arbol.suprimir(130);
		arbol.suprimir(134);
		arbol.suprimir(136);
		arbol.suprimir(127);
		arbol.suprimir(128);
		arbol.suprimir(138);
		cout <<endl<<"***********    Arbol b+    ***********"<<endl;
		arbol.visualizar(true);
		cout <<endl<<"**************************************"<<endl;


		/**
		 * PRUEBA 2: Modificacion de elementos
		 */

		cout <<endl<<"*****          PRUEBA 2          ******";
		cout <<endl<<"*****  Modificacion de elementos ******"<<endl;
		cout <<      "***************************************"<<endl;


		//estructura para la prueba
		typedef struct {
			int dato_1;
			int dato_2;

		} Prueba;

		cout<<endl<<" Inserto un elemento del tipo int con clave 1"<<endl;
		dato = 12;
		//ingreso un elemento del tipo int al arbol con clave 1
		arbol.Insertar(1,&dato,sizeof(int));
		cout <<endl<<"***********    Arbol b+    ***********"<<endl;
		arbol.visualizar();
		cout <<endl<<"**************************************"<<endl;

		cout<<endl<<" Modifico el elemento de clave 1 por una estructura de datos"<<endl;
		//modifico el elemento de clave uno por uno del tipo estructura Prueba
		Prueba d;
		d.dato_1 = 1;
		d.dato_2 = 2;
		arbol.Modificar(1,&d,sizeof(Prueba));
		cout <<endl<<"***********    Arbol b+    ***********"<<endl;
		arbol.visualizar();
		cout <<endl<<"**************************************"<<endl;

		Prueba* ptr_d;
		unsigned int claveDevuelta;
		ptr_d = (Prueba*)arbol.Buscar(1,&claveDevuelta);
		cout<<endl<<"* Recupero la estructura de datos ingresada en la modificacion"<<endl<<"- prueba.dato_1 = "<<ptr_d->dato_1 <<endl<< "- prueba.dato_2 = "<<ptr_d->dato_2<<endl;
		delete[] (ptr_d);
		//igreso datos del tipo in al arbol
		dato = 49;
		arbol.Insertar(dato,&dato,sizeof(dato));
		dato = 57;
		arbol.Insertar(dato,&dato,sizeof(dato));
		dato = 90;
		arbol.Insertar(dato,&dato,sizeof(dato));
		dato = 47;
		arbol.Insertar(dato,&dato,sizeof(dato));
		dato = 30;
		arbol.Insertar(dato,&dato,sizeof(dato));
		dato = 35;
		arbol.Insertar(dato,&dato,sizeof(dato));
		dato = 10;
		arbol.Insertar(dato,&dato,sizeof(dato));
		dato = 21;
		cout<<endl<<"* Agrego mas elementos al arbol, ahora del tipo int"<<endl;
		cout <<endl<<"***********    Arbol b+    ***********"<<endl;
		arbol.visualizar();
		cout <<endl<<"**************************************"<<endl;

		cout<<endl<<"* Elimino el elemento de clave 10: No produce undeflow"<<endl;
		arbol.suprimir(10);
		cout <<endl<<"***********    Arbol b+    ***********"<<endl;
		arbol.visualizar();
		cout <<endl<<"**************************************"<<endl;


		cout<<endl<<"* Modifico el elemento de clave 1 por uno del tipo int: produce underflow"<<endl;
		dato = 1;
		arbol.Modificar(dato,&dato,sizeof(int));
		cout <<endl<<"***********    Arbol b+    ***********"<<endl;
		arbol.visualizar();
		cout <<endl<<"**************************************"<<endl;

		cout<<endl<<"* Agrego un elemento del tipo estructura Prueba con clave 100 : no produce overflow"<<endl;
		arbol.Insertar(100,&d,sizeof(Prueba));
		cout <<endl<<"***********    Arbol b+    ***********"<<endl;
		arbol.visualizar();
		cout <<endl<<"**************************************"<<endl;


		cout<<endl<<"* Modifico el elemento de clave 90 por uno del tipo estructura Prueba: produce overflow"<<endl;
		arbol.Modificar(90,&d,sizeof(Prueba));
		cout <<endl<<"***********    Arbol b+    ***********"<<endl;
		arbol.visualizar();
		cout <<endl<<"**************************************"<<endl;

	}


	cout <<endl<<endl<<"*****          PRUEBA 3          ******";
	cout <<endl<<"*****    Recorrido Secuencial    ******"<<endl;
	cout <<      "***************************************"<<endl;

	char nombreArchivo[20] = "pruebasRec.dat";

	//Creo el arbol con bloque de 64 bytes
	ArbolB  arbol(nombreArchivo,64);
	//agrego elementos
	agregarElemetnosArbol(&arbol);

	cout <<endl<<"***********    Arbol b+    ***********"<<endl;
	arbol.visualizar();
	cout <<endl<<"**************************************"<<endl;


	int* p2;
	Nodo::TClave claveDevuelta;

    arbol.iniciarRecorridoSecuencial();
    cout<<endl<<"* Recorro los elementos secuencialmente hacia adelante *"<<endl;
    cout<<endl<<"( CLAVE ; VALOR )= ";

    while (arbol.tieneSiguiente()) {
            p2 = (int*) arbol.getSiguiente(&claveDevuelta);
            cout <<"("<<claveDevuelta<<";"<< *p2 << ") - ";
            delete[] p2;
    }

    cout<<endl<<endl<<"* Recorro los elementos secuencialmente hacia atras *"<<endl;
    cout <<endl<<"( CLAVE ; VALOR )= ";

    while (arbol.tieneAnterior()) {
            p2 = (int*) arbol.getAnterior(&claveDevuelta);
            cout <<"("<<claveDevuelta<<";"<< *p2 << ") - ";
            delete[] p2;
    }

    cout <<endl;
	cout <<endl<<"**********     PRUEBA 4    ************";
	cout <<endl<<"**********      Buscar     ************"<<endl;
	cout <<      "***************************************"<<endl;

	cout <<endl<<"***********    Arbol b+    ***********"<<endl;
	arbol.visualizar();
	cout <<endl<<"**************************************"<<endl;

	cout<<endl<<"*Busco el elemento 55: como no esta en el arbol encuentra el 56 *"<<endl;
	int * p;


    p = (int *)arbol.Buscar(55,&claveDevuelta);
    cout <<" (CLAVE;ELEMENTO) = ("<< claveDevuelta << ";" << *p <<")"<<endl;
    delete[](p);

    cout<<endl<<"*Busco el elemento 56: como esta en el arbol lo encuentra *"<<endl;
    p = (int *)arbol.Buscar(56,&claveDevuelta);
    cout <<" (CLAVE;ELEMENTO) = (" << claveDevuelta << ";" << *p <<")"<<endl;
    delete[](p);

    cout<<endl<<"*Busco el elemento 90: como esta en el arbol lo encuentra *"<<endl;
    p = (int *)arbol.Buscar(90,&claveDevuelta);
    cout <<" (CLAVE;ELEMENTO) = (" << claveDevuelta << ";" << *p <<")"<<endl<<endl;
    delete[](p);


}

