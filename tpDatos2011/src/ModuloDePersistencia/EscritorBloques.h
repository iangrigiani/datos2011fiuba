#ifndef ESCRITORBLOQUES_H_
#define ESCRITORBLOQUES_H_

#include "../EstructurasEnComun/Bloque.h"
#include "../EstructurasEnComun/Registro.h"
#include "../EstructurasEnComun/Constantes.h"
#include <iostream>
#include <fstream>

class EscritorBloques {
private:
	char * buffer;
	Bloque * bloque;
	unsigned int bufferOffset;
	unsigned int fileOffset;
	std::string path;
	
public:
	EscritorBloques();
	EscritorBloques (std::string path);
	int GrabarRegistro(Registro * reg);
	void GrabarBloqueEnArchivo();
	int getOffset(){
		return this->fileOffset;
	}
	virtual ~EscritorBloques();
};

#endif /* ESCRITORBLOQUES_H_ */
