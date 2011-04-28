/*
 * HandlerTabla.cpp
 *
 *  Created on: 31/03/2011
 *      Author: angeles
 */

#include "HandlerTabla.h"

HandlerTabla::HandlerTabla() {
	ifstream arch;
	string s;
	stringstream ss;

	arch.open(this->ruta_arch_tabla.c_str());
	getline(arch, s, '|');
	arch.close();

	ss << s;
	ss >> hex >> this->tam_tabla;
}

void HandlerTabla::set_ruta_arch_tabla(const string& ruta_arch_tabla) {
	this->ruta_arch_tabla = ruta_arch_tabla;
}

void HandlerTabla::set_ruta_arch_temporal(const string& ruta_arch_temporal) {
	this->ruta_arch_temporal = ruta_arch_temporal;
}


bool HandlerTabla::tabla_vacia() {
	ifstream arch;
	string s;
	stringstream ss;

	arch.open(this->ruta_arch_tabla.c_str());
	getline(arch, s, '|');
	arch.close();

	ss << s;
	ss >> hex >> this->tam_tabla;
	if (this->tam_tabla == 0)
		return true;

	return false;
}

void HandlerTabla::crear_tabla_inicial(int num_bloque) {
	fstream arch;
	string s;
	stringstream ss;

	this->tam_tabla = 1;

	arch.open(this->ruta_arch_tabla.c_str(), fstream::in | fstream::out);

	arch.width(8);
	arch << hex << this->tam_tabla << '|';
	arch << ' ' << dec << num_bloque;

	arch.close();
}

void HandlerTabla::duplicar_tabla() {
	fstream arch;
	string s;
	long pos;
	int contador = 0;

	arch.open(this->ruta_arch_tabla.c_str(), fstream::in | fstream::out);

	getline(arch, s, '|');

	while (contador != this->tam_tabla) {
		arch >> s;
		pos = arch.tellp();
		arch.seekg(0, fstream::end);
		arch << ' ' << s;
		++ contador;
		arch.seekp(pos);
	}

	this->tam_tabla *= 2;

	arch.seekg(0, fstream::beg);
	arch.width(8);
	arch << hex << this->tam_tabla;

	arch.close();
}

void HandlerTabla::truncar_tabla() {
	ifstream arch;
	ofstream arch_aux;
	string s;
	int contador = 0;

	arch.open(this->ruta_arch_tabla.c_str());
	arch_aux.open(this->ruta_arch_temporal.c_str());

	this->tam_tabla /= 2;
	if (this->tam_tabla < 0)
		this->tam_tabla = 0;
	arch_aux.width(8);
	arch_aux << hex << this->tam_tabla << '|';

	getline(arch, s, '|');

	while (contador != this->tam_tabla) {
		arch >> s;
		arch_aux << ' ' << s;
		++ contador;
	}

	arch.close();
	arch_aux.close();

	remove(this->ruta_arch_tabla.c_str());


	rename(this->ruta_arch_temporal.c_str(), this->ruta_arch_tabla.c_str());

}

bool HandlerTabla::mitades_iguales() const {
	fstream arch;
	string s, s_aux;
	long pos_1, pos_2;
	int contador = 0;
	bool igual = true;

	arch.open(this->ruta_arch_tabla.c_str(), fstream::in);

	getline(arch, s, '|');
	pos_1 = arch.tellp();

	while (contador != this->tam_tabla / 2) {
		arch >> s;
		++ contador;
	}
	pos_2 = arch.tellp();

	contador = 0;
	arch.seekp(pos_1);
	while (contador != this->tam_tabla / 2 && igual == true) {
		arch >> s;
		pos_1 = arch.tellp();

		arch.seekp(pos_2);
		arch >> s_aux;
		pos_2 = arch.tellp();

		if (s.compare(s_aux) != 0)
			igual = false;

		++ contador;
		arch.seekp(pos_1);
	}

	arch.close();

	return igual;
}

int HandlerTabla::get_num_bloque(int clave) const {
	ifstream arch;
	string s;
	int num_bloque;
	int contador = 0;

	arch.open(this->ruta_arch_tabla.c_str());

	getline(arch, s, '|');

	while (contador != clave % this->tam_tabla) {
		arch >> num_bloque;
		++ contador;
	}
	arch >> num_bloque;

	arch.close();

	return num_bloque;
}

int HandlerTabla::get_pos_tabla(int clave) const {
	return (clave % this->tam_tabla);
}

void HandlerTabla::reemplazar_referencia(int num_bloque_a_reemplazar, int num_nuevo_bloque) {
	ifstream arch;
	ofstream arch_aux;
	string s;
	int num_bloque;
	bool encontrado = false;
	int contador = 0;

	arch.open(this->ruta_arch_tabla.c_str());
	arch_aux.open(this->ruta_arch_temporal.c_str());

	arch_aux.width(8);
	arch_aux << hex << this->tam_tabla << '|';

	getline(arch, s, '|');

	while (contador != this->tam_tabla && encontrado == false) {
		arch >> num_bloque;

		if (num_bloque == num_bloque_a_reemplazar) {
			encontrado = true;
			arch_aux << ' ' << dec << num_nuevo_bloque;
		}
		else arch_aux << ' ' << dec << num_bloque;

		++ contador;
	}

	while (contador != this->tam_tabla) {
		arch >> num_bloque;
		arch_aux << ' ' << dec << num_bloque;
		++ contador;
	}

	arch.close();
	arch_aux.close();

	remove(this->ruta_arch_tabla.c_str());
	rename(this->ruta_arch_temporal.c_str(),this->ruta_arch_tabla.c_str());
}

void HandlerTabla::reemplazar_referencias(int pos_inicial, int num_nuevo_bloque, const Bloque& nuevo_bloque) {
	ifstream arch;
	ofstream arch_aux;
	string s;
	int pos_aux, pos;
	int contador = 0;
	int dist_salto = nuevo_bloque.get_tam_disp();

	arch.open(this->ruta_arch_tabla.c_str());
	arch_aux.open(this->ruta_arch_temporal.c_str());

	arch_aux.width(8);
	arch_aux << hex << this->tam_tabla << '|';

	getline(arch, s, '|');

	pos = pos_inicial;
	pos_aux = pos_inicial - dist_salto;
	while (pos_aux >= 0) {
		pos = pos_aux;
		pos_aux = pos - dist_salto;
	}

	while (contador != this->tam_tabla) {
		arch >> s;
		if (contador == pos) {
			arch_aux << ' ' << dec << num_nuevo_bloque;
			pos += dist_salto;
		}
		else arch_aux << ' ' << s;
		++ contador;
	}

	arch.close();
	arch_aux.close();

	remove(this->ruta_arch_tabla.c_str());

	rename(this->ruta_arch_temporal.c_str(), this->ruta_arch_tabla.c_str());

}
/*
void HandlerTabla::reemplazar_referencias(int pos_inicial, int num_nuevo_bloque, const Bloque& nuevo_bloque) {
	ifstream arch;
	ofstream arch_aux;
	string s;
	int contador = this->tam_tabla - pos_inicial;
	int dist_salto = contador;

	arch.open(NOM_ARCH_TABLA);
	arch_aux.open(NOM_ARCH_TEMP);

	arch_aux.width(8);
	arch_aux << hex << this->tam_tabla << '|';

	getline(arch, s, '|');

	while (contador - this->tam_tabla + pos_inicial != this->tam_tabla) {
		arch >> s;

		if (dist_salto == nuevo_bloque.get_tam_disp()) {
			arch_aux << ' ' << dec << num_nuevo_bloque;
			dist_salto = 0;
		}
		else arch_aux << ' ' << s;

		++ contador;
		++ dist_salto;
	}

	arch.close();
	arch_aux.close();

	remove(NOM_ARCH_TABLA);
	rename(NOM_ARCH_TEMP, NOM_ARCH_TABLA);
}
*/
int HandlerTabla::puedo_liberar_bloque(const Bloque& bloque_a_liberar, int pos_actual) const {
	ifstream arch;
	string s;
	int bloque_anterior, bloque_siguiente, pos_anterior, pos_siguiente;
	int contador = 0;

	arch.open(this->ruta_arch_tabla.c_str());

	getline(arch, s, '|');

	pos_anterior = pos_actual - bloque_a_liberar.get_tam_disp() / 2 + 1;
	if (pos_anterior <= 0)
		pos_anterior += this->tam_tabla;

	pos_siguiente = pos_actual + bloque_a_liberar.get_tam_disp() / 2 + 1;
	if (pos_siguiente > this->tam_tabla)
		pos_siguiente -= this->tam_tabla;

	if (pos_anterior < pos_siguiente) {
		while (contador != pos_anterior) {
			arch >> bloque_anterior;
			++ contador;
		}
		while (contador != pos_siguiente) {
			arch >> bloque_siguiente;
			++ contador;
		}
	}
	else {
		if (pos_anterior > pos_siguiente) {
			while (contador != pos_siguiente) {
				arch >> bloque_siguiente;
				++ contador;
			}
			while (contador != pos_anterior) {
				arch >> bloque_anterior;
				++ contador;
			}
		}
		else {
			while (contador != pos_anterior) {
				arch >> bloque_anterior;
				++ contador;
			}
		}
	}

	if (bloque_anterior == bloque_siguiente || pos_anterior == pos_siguiente)
		return bloque_anterior;
	return -1;
}

void HandlerTabla::liberar_referencias(int pos_inicial, int num_bloque_por_reemplazar,
		const Bloque& bloque_por_reemplazar) {
	this->reemplazar_referencias(pos_inicial, num_bloque_por_reemplazar, bloque_por_reemplazar);
}
