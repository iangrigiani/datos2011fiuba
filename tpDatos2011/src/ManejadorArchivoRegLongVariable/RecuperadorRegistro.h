/*
 * RecuperadorRegistro.h
 *
 *  Created on: 30/03/2011
 *      Author: catu
 */

#ifndef RECUPERADORREGISTRO_H_
#define RECUPERADORREGISTRO_H_

#include <iostream>
#include <fstream>

using namespace std;

class RecuperadorRegistro {

	private:

			unsigned int  offset;
			std::string path;

	public:

			RecuperadorRegistro();
			RecuperadorRegistro(std::string path);
			virtual ~RecuperadorRegistro();
			char * obtenerLibro(int offset);
			unsigned int getOffset();
			void setOffset(unsigned int offset);
};

#endif /* RECUPERADORREGISTRO_H_ */
