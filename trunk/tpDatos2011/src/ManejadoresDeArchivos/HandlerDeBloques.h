#ifndef HANDLERDEBLOQUES_H_
#define HANDLERDEBLOQUES_H_

#include <sstream>
#include <fstream>
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../EstructurasEnComun/Constantes.h"

using namespace std;

class HandlerDeBloques{

private:
		fstream ff;
		string path;
public:
		int get_tam_arch_bloques();
		HandlerDeBloques();
		HandlerDeBloques(string path);
		virtual ~HandlerDeBloques() {
			ff.close();
		};
		void guardar_bloque(char* buffer, int nro_Bloque);
		char* recuperar_bloque(int nro_Bloque);
		void eliminar_bloque(int nro_Bloque);
};

#endif /* HANDLERDEBLOQUES_H_ */
