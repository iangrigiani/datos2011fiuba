#ifndef SERIALIZABLE_H_
#define SERIALIZABLE_H_

class Serializable {
public:
	Serializable(){

	}
	virtual void serializar(char * buffer, unsigned int &offset)=0;
	virtual void hidratar(char * buffer, unsigned int &offset)=0;
	virtual ~Serializable(){

	}
};

#endif /* SERIALIZABLE_H_ */
