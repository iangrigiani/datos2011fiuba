#ifndef RECUPERADORBLOQUES_H_
#define RECUPERADORBLOQUES_H_

#include "../EstructurasEnComun/Bloque.h"
#include <iostream>
#include <fstream>
#include "../EstructurasEnComun/ClaveNumerica.h"
#include "../EstructurasEnComun/Registro.h"

class RecuperadorBloques {
private:
	std::string path;
	unsigned int offset;
public:
	RecuperadorBloques();
	RecuperadorBloques (std::string path);
	Bloque * getSiguienteBloque();
	Registro * getRegistro(ClaveNumerica * key,  int offset);
	Registro * getSiguienteRegistro(ClaveNumerica * key,ClaveNumerica * prevKey,  int offset);
	unsigned int getOffset(){
		return offset;
	}
	virtual ~RecuperadorBloques();
};

#endif /* RECUPERADORBLOQUES_H_ */
