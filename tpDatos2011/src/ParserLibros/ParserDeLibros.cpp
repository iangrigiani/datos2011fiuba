#include "ParserDeLibros.h"

ParserDeLibros::ParserDeLibros() {
}
ParserDeLibros::~ParserDeLibros() {
	delete this->actualHead;
}

char * ParserDeLibros::getAutor(){
	char AutorPatron[] = "Autor:\\s*([^\n\r\t]*)";
	return getFirstMatch(this->actualHead, AutorPatron);
}

char * ParserDeLibros::getTitulo(){
	char TituloPatron[] = "Titulo:\\s*([^\n\r\t]*)";
	return getFirstMatch(this->actualHead, TituloPatron);
}

char * ParserDeLibros::getEditorial(){
	char EditorialtPatron[] = "Editorial:\\s*([^\n]*)";
	return getFirstMatch(this->actualHead, EditorialtPatron);
}

char * ParserDeLibros::getPalabras(){
	char PalabrasPatron[]= "Palabras:\\s*[^,]*,\\s*([^\n]*)";
	return getFirstMatch(this->actualHead, PalabrasPatron);
}

char * ParserDeLibros::getFirstMatch(char * string, char *Patron) {
	regex_t preg;
	regmatch_t pmatch[2];
	char pom[STRING_BUFFER];
	/* it's possible something won't compile like  ./regexp '*' abc */
	regcomp (&preg, Patron, REG_EXTENDED);
	regexec (&preg, string, 2, pmatch, 0);
	strncpy (pom, string + pmatch[1].rm_so,
			pmatch[1].rm_eo - pmatch[1].rm_so);
	pom[pmatch[1].rm_eo - pmatch[1].rm_so] = '\0';
	regfree (&preg);
	return pom;
}

Registro * ParserDeLibros::obtenerRegistroDeLibro (char * libro){
	/*
	 * TODO: Aca iría la logica para las palabras(Downcase y Stopwords)
	 * y crear el registro que se almacenara en un bloque y en el B+ y hash
	 */
	this->actualHead = libro;
	Registro* nuevoRegistro = new Registro();
}
