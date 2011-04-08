#ifndef REGISTRO_H_
#define REGISTRO_H_

#include <string>
#include "Clave.h"
#include <iostream>
#include <string.h>
#include <list>
#include "../ModuloDePersistencia/Serializable.h"
#include "../ModuloDePersistencia/Persistencia.h"
using namespace std;

class Registro: public Serializable {
private:
	string titulo;
	string editorial;
	string autor;
	list<string> palabras;
	Clave * clave;

public:
	Registro();
	Registro(string titulo,string autor,string editorial,list<string> palabras, string uiKey);
	Registro (Clave* uiKey);
	Registro (const Registro &a);

	void toString();

	int getTamanio(){
		int size = 0;
		size += this->titulo.length()+ this->editorial.length()
				+this->autor.length()+ sizeof(int)+1;
		size += sizeof(int);
		list<string>::iterator it = this->palabras.begin();
		while( it != this->palabras.end()){
			size += (*it).length();
			++it;
		}
		return size;
	}

	void serializar(char * buffer, unsigned int &offset);

	void hidratar(char * buffer, unsigned int &offset);

	virtual ~Registro();


/*------------- GETTERS AND SETTERS ---------------*/
    string getAutor() const{
        return autor;
    }
    Clave* getClave() const{
        return clave;
    }
    string getEditorial() const{
        return editorial;
    }
    list<string> getPalabras() const{
        return palabras;
    }
    string getTitulo() const{
        return titulo;
    }
    void setAutor(string autor){
        this->autor = autor;
    }
    void setClave(Clave * clave){
        this->clave = clave;
    }
    void setEditorial(string editorial){
        this->editorial = editorial;
    }
    void setPalabras(list<string> palabras){
        this->palabras = palabras;
    }
    void setTitulo(string titulo){
        this->titulo = titulo;
    }

};

#endif /* REGISTRO_H_ */
