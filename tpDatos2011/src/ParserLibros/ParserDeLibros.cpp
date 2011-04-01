#include "ParserDeLibros.h"

ParserDeLibros::ParserDeLibros() {
}
ParserDeLibros::~ParserDeLibros() {
        delete this->libroActual;
}

char * ParserDeLibros::getAutor(){
        char AutorPatron[] = "Autor:\\s*([^\n\r\t]*)";
        return getFirstMatch(this->libroActual, AutorPatron);
}

char * ParserDeLibros::getTitulo(){
        char TituloPatron[] = "Titulo:\\s*([^\n\r\t]*)";
        return getFirstMatch(this->libroActual, TituloPatron);
}

char * ParserDeLibros::getEditorial(){
        char EditorialtPatron[] = "Editorial:\\s*([^\n]*)";
        return getFirstMatch(this->libroActual, EditorialtPatron);
}

char * ParserDeLibros::getPalabras(){
        char PalabrasPatron[]= "Palabras:\\s*([^\r\t]*)\FINPALABRA";
        return getFirstMatch(this->libroActual, PalabrasPatron);
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
         */
        this->libroActual = libro;
        Registro* nuevoRegistro = new Registro();
        nuevoRegistro->setAutor(this->getAutor());
        nuevoRegistro->setEditorial(this->getEditorial());
        nuevoRegistro->setTitulo(this->getTitulo());

        char * str = this->getPalabras();
        char * pch;
		pch = strtok (str," \n");
		list<string> listaAux;
		listaAux.push_back(pch);
		while (pch != NULL)
		{
			pch = strtok (NULL, " \n");
			if (pch) listaAux.push_back(pch);
		}
		nuevoRegistro->setPalabras(listaAux);
        return nuevoRegistro;
}
