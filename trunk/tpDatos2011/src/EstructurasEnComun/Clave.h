#ifndef CLAVE_H_
#define CLAVE_H_
#include "../ModuloDePersistencia/Persistencia.h"
#include "../ModuloDePersistencia/Serializable.h"
class Clave : public Serializable{
private:
	std::string clave;
public:
	Clave();

	Clave(std::string clave);

	Clave(const Clave &a){
		this->clave = a.clave;
	}
	std::string getClave();

	void serializar(char * buffer, unsigned int &offset);
	void hidratar(char * buffer, unsigned int &offset);

	bool igual (Clave *a);

	bool esMenor(Clave *a);

	void setValorClave (std::string valor){
		this->clave = valor;
	}
	void toString();
	int getTamanio()const{
		return (strlen(this->clave.c_str()));
	}
	Clave * getClaveNula(){
		return new Clave("0");
	}
	Clave * getClaveError(){
		return new Clave("-1");
	}
	bool esMenorIgual(Clave *a);
	virtual ~Clave();
};

#endif /* CLAVE_H_ */
