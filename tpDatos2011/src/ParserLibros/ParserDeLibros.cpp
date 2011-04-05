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
        char EditorialtPatron[] = "Editorial:\\s*([^\n\r\t]*)";
        return obtenerPrimerMatch(this->libroActual, EditorialtPatron);
}

char * ParserDeLibros::obtenerPalabras(){
        char PalabrasPatron[]= "Palabras:\\s*([^FINPALABRA/]*)";
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

Registro * ParserDeLibros::obtenerRegistroDeLibro (char * libro){
        this->libroActual = libro;
        Registro* nuevoRegistro = new Registro();
        nuevoRegistro->setAutor(this->obtenerAutor());
        nuevoRegistro->setEditorial(this->obtenerEditorial());
        nuevoRegistro->setTitulo(this->obtenerTitulo());

        char * str = this->obtenerPalabras();
        char * pch;
		pch = strtok (str," \n");
		list<string> listaAux;
		listaAux.push_back(pch);
		while (pch != NULL)
		{
			pch = strtok (NULL, " \n");
			if (pch) {
				if (!esStopWords(pch)){
					listaAux.push_back(caseFolding(pch));
				}
			}
		}
		nuevoRegistro->setPalabras(listaAux);
        return nuevoRegistro;
}

bool ParserDeLibros::esStopWords(char* pch){
	// TODO verificar si es stopWords con busqueda en la lista
	return false;
}

string ParserDeLibros::caseFolding(char* pch){
	// TODO Aplicar el case folding a la palabra antes de almacenarla
	// habria que ver si esto se aplica a todos los parametros y no solo
	// a las palabras, sino que tambien, autor, editorial, etc.
	return pch;
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
