#include "FrontCoding.h"

FrontCoding::FrontCoding(){
	this->cadena = "";
	this->distinto = 0;
	this->igual = 0;

}

FrontCoding::~FrontCoding() {
}

string FrontCoding::pasarAFrontCoding(string primerPalabraNodo, string palabra){
	aplicarFrontCoding(primerPalabraNodo, palabra);
	ostringstream oss;
	oss << this->offset << "." <<  this->igual << "." << this->distinto << "." << this->cadena;
	string retorno = oss.str();
	return retorno;
}

void FrontCoding::obtenerOffset(string primerPalabraNodo){
	fstream ifs;
	ifs.open(PATH_FRONT_CODING, std::ios_base::in | std::ios_base::out);
	char* cadena = (char*)calloc(100, sizeof(char));
	bool encontrado  = false;
	string cad;

	while (!encontrado && !ifs.eof()){
		this->offset = ifs.tellg();
		ifs.getline(cadena, 100);
		cad = cadena;
		if (cad.length() > 0 && cad == primerPalabraNodo){
			encontrado = true;
		}
	}
	if (!encontrado){
		ifs.close();
		grabarAlFinal(primerPalabraNodo);
	}
}

void FrontCoding::aplicarFrontCoding(string primerPalabraNodo , string palabra){
	obtenerOffset(primerPalabraNodo);
	if(primerPalabraNodo == palabra){
		this->cadena = "";
		this->distinto = 0;
		this->igual = primerPalabraNodo.length();
	}else{
		int tamanio = primerPalabraNodo.length();
		int i = 0;
		int cont = 0;
		bool distinto = false;
		ostringstream oss;
		while (i < tamanio && !distinto){
			if (primerPalabraNodo[i] == palabra[i]){
				++i;
				++cont;
				this->igual = i;
			}else{
				distinto = true;
			}
		}
		this->distinto = primerPalabraNodo.length() - this->igual;
		for (unsigned int i = cont ; i < palabra.length(); i++)
			oss << palabra[i];
		this->cadena = oss.str();
	}
}

void FrontCoding::grabarAlFinal(string primerPalabraNodo){
	fstream ifs;
	ifs.open(PATH_FRONT_CODING, ios_base::in | ios_base::out);
	ifs.seekg(0, ios_base::end);
	int tamanio = ifs.tellg();
	ifs.seekg(0, ios_base::beg);
	this->offset = tamanio;
	ostringstream oss;
	oss << primerPalabraNodo << "\n";
	string ss = oss.str();
	ifs.seekg(tamanio);
	ifs.write(ss.c_str(), ss.length());
	ifs.flush();
	ifs.close();
}

string FrontCoding::obtenerPalabra(){
	fstream ifs;
	string retorno;
	ifs.open(PATH_FRONT_CODING, ios_base::in | ios_base::out);
	ifs.seekg(this->offset);
	char* cadena = (char*)calloc(100, sizeof(char));
	ifs.getline(cadena, 100);
	ifs.close();
	retorno = cadena;
	if (retorno.length() > 0)
		return	retorno ;
	return "";
}


string FrontCoding::interpretarFrontCoding(string frontCoding){
	int cont = 0;
	ostringstream off;
	ostringstream igu;
	ostringstream cad;
	ostringstream final;
	for (unsigned int i = 0; i < frontCoding.length(); i++){
		const char a = frontCoding.at(i);
		if (a != 46){
			switch (cont) {
				case 0:
					off << frontCoding[i];
					break;
				case 1:
					igu << frontCoding[i];
					break;
				case 3:
					cad << frontCoding[i];
					break;
			}
		}else{
			++cont;
		}
	}

	this->offset = atoi(off.str().c_str());
	string primeraPalabra = obtenerPalabra();
	if (primeraPalabra.length() > 0){
		this ->igual = atoi(igu.str().c_str());
		for (int i = 0; i < this->igual ; i++){
			final << primeraPalabra[i];
		}
		final << cad.str();
		return (final.str());
	}else{
		return NULL;
	}
}
