#include "ParserDeLibros.h"

ParserDeLibros::ParserDeLibros() {
	obtenerListaStopWords();
}
ParserDeLibros::~ParserDeLibros() {
        delete this->libroActual;
}

char * ParserDeLibros::obtenerAutor(){
        char AutorPatron[] = "Autor:\\s*([^\n\r\t]*)";
        return obtenerPrimerMatch(this->libroActual, AutorPatron);
}

char * ParserDeLibros::obtenerTitulo(){
        char TituloPatron[] = "Titulo:\\s*([^\n\r\t]*)";
        return obtenerPrimerMatch(this->libroActual, TituloPatron);
}

char * ParserDeLibros::obtenerEditorial(){
        char EditorialPatron[] = "Editorial:\\s*([^\n\r\t]*)";
        return obtenerPrimerMatch(this->libroActual, EditorialPatron);
}

char * ParserDeLibros::obtenerPalabras(){
        char PalabrasPatron[] = "Palabras:\\s*([^|/]*)";
        return obtenerPrimerMatch(this->libroActual, PalabrasPatron);
}

char * ParserDeLibros::obtenerPrimerMatch(char * string, char *patronDeFiltro) {
    regex_t preg;
    regmatch_t pmatch[2];
    char* pom = (char*)calloc(STRING_BUFFER, sizeof(char));
    /* it's possible something won't compile like  ./regexp '*' abc */
    regcomp (&preg, patronDeFiltro, REG_EXTENDED);
    regexec (&preg, string, 2, pmatch, 0);
    strncpy (pom, string + pmatch[1].rm_so,
                    pmatch[1].rm_eo - pmatch[1].rm_so);
    pom[pmatch[1].rm_eo - pmatch[1].rm_so] = '\0';
    regfree (&preg);
    return pom;
}

list < string > ParserDeLibros::obtenerDatos(char* cadena) {
	list < string > elementos;
	char* pch = strtok(cadena, "¿?¡!:;., \n\t\r");
	string str;

	while (pch != NULL) {
		str = pch;
		this->downCase(str);
		if (!esStopWords(pch)) {
			elementos.push_back(str);
		}
		str.clear();
		pch = strtok(NULL, "¿?¡!:;., \n\t\r");
	}
	return elementos;
}

Registro * ParserDeLibros::obtenerRegistroDeLibro(char* libro) {
	this->libroActual = libro;
	Registro* nuevoRegistro = new Registro();
	nuevoRegistro->setAutor(this->obtenerAutor());
	if (this->obtenerEditorial()){
		nuevoRegistro->setEditorial(this->obtenerEditorial());
	}else{
		nuevoRegistro->setEditorial(EDITORIAL);
	}
	nuevoRegistro->setTitulo(this->obtenerTitulo());

	list < string > palabras = this->obtenerDatos(this->obtenerPalabras());
	nuevoRegistro->setPalabras(palabras);

	return nuevoRegistro;
}

void ParserDeLibros::downCase(string& str) {
	char c;
	for (unsigned int i = 0; i < str.size(); ++ i) {
		if (isalnum(str[i])) {
			if (!islower(str[i])) {
				c = tolower(str[i]);
				str[i] = c;
			}
		}
		else str[i] = 'z';
	}
}

bool ParserDeLibros::esStopWords(char* palabra){

	// @Nacho: IMPLEMENTACION CON BUSQUEDA BINARIA

	int totalElem = this->listaStopWords.size();
	int medio, pivotDer, pivotIzq;
	pivotIzq=0;
	pivotDer=totalElem-1;

	stringstream ss;
	ss << palabra;

	string palabraStr = ss.str();

	while ( pivotIzq <= pivotDer) { // el elemento que esta ala izquierda debe de ser menor que el de la derecha
		medio = ( pivotIzq + pivotDer )/2; // calculo el elemento central
		if ( palabraStr > this->listaStopWords[medio] ) // si el elemento buscado es mayor que el centro entonces busco en la segunda mitad del vector
			pivotIzq = medio + 1; // el primer valor del vector pasa hacer la mitad mas 1
		else if ( palabraStr < this->listaStopWords[medio] ) // si el elemento buscado buscado es menor que la mitad entonces buscamos en la primera mitad del vector
			pivotDer = medio - 1;
		else return true; // si encontro la palabra, devuelvo true
	}

	return false;

}

void ParserDeLibros::obtenerListaStopWords(){
	ifstream fd;
	fd.open(PATH_STOPWORDS, ios_base::in);
	fd.seekg(0, ios_base::end);
	int tamanio = fd.tellg();
	fd.seekg(0, ios_base::beg);
	char* lista = (char*)calloc(tamanio, sizeof(char));
	fd.read(lista, tamanio);
	char * pch;
	pch = strtok (lista,"\n");
	this->listaStopWords.push_back(pch);
	while (pch != NULL)
	{
		pch = strtok (NULL, "\n");
		if (pch) this->listaStopWords.push_back(pch);
	}
	fd.close();
}
