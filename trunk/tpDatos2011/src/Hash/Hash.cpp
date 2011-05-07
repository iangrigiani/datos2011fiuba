#include "Hash.h"

Hash::Hash(int tam_bloque, const string& ruta_arch_bloques, const string& ruta_arch_esp_libre,
		const string& ruta_arch_tabla, const string& ruta_arch_temporal) {
	this->handler_bloques.set_tam_bloque(tam_bloque);
	this->handler_bloques.set_ruta_arch_bloques(ruta_arch_bloques);
	HandlerEspLibre handler_esp_libre(ruta_arch_esp_libre);
	this->handler_bloques.set_handler_esp_libre(handler_esp_libre);
	this->handler_tabla.set_ruta_arch_tabla(ruta_arch_tabla);
	this->handler_tabla.set_ruta_arch_temporal(ruta_arch_temporal);
}
/*
void Hash::crear_condiciones_iniciales() {
	if (this->handler_tabla.tabla_vacia() == true) {
		Cubo bloque;
		unsigned int offset = 0;
		char buffer[this->handler_bloques.get_tam_bloque()];

		bloque.serializar(buffer, offset);
		int num_bloque = this->handler_bloques.guardar_bloque(buffer);
		this->handler_tabla.crear_tabla_inicial(num_bloque);
	}
}
*/
void Hash::crear_condiciones_iniciales() {
	this->handler_bloques.crear_arch_vacio();
	this->handler_bloques.get_handler_esp_libre().crear_arch_inicial();
	this->handler_tabla.crear_tabla_inicial();

	if (this->handler_tabla.tabla_vacia() == true) {
		Cubo bloque;
		unsigned int offset = 0;
		char buffer[TAM_CUBO];

		bloque.serializar(buffer, offset);
		int num_bloque = this->handler_bloques.guardar_bloque(buffer);
		this->handler_tabla.insertar_primer_referencia(num_bloque);
	}
}

void Hash::insertar_reg(RegIndice& reg) {
	Cubo bloque;
	unsigned int offset = 0;
	char buffer[TAM_CUBO];

	int pos_tabla_bloque = this->handler_tabla.get_pos_tabla(reg.get_clave());
	int num_bloque = this->handler_tabla.get_num_bloque(reg.get_clave());
	this->handler_bloques.recuperar_bloque(buffer, num_bloque);
	bloque.hidratar(buffer, offset);

	if (bloque.entra_en_bloque(reg) == true) {
		bloque.agregar_nuevo_reg(reg);
		offset = 0;
		bloque.serializar(buffer, offset);
		this->handler_bloques.guardar_bloque(buffer, num_bloque);
	}
	else {
		int tam_disp_inicial = bloque.get_tam_disp();
		bloque.duplicar_tam_disp();
		Cubo nuevo_bloque(bloque.get_tam_disp());

		offset = 0;
		nuevo_bloque.serializar(buffer, offset);
		int num_nuevo_bloque = this->handler_bloques.guardar_bloque(buffer);

		if (tam_disp_inicial == this->handler_tabla.get_tam_tabla()) {
			this->handler_tabla.duplicar_tabla();
			this->handler_tabla.reemplazar_referencia(num_bloque, num_nuevo_bloque);
		}
		else this->handler_tabla.reemplazar_referencias(pos_tabla_bloque, num_nuevo_bloque, nuevo_bloque);

		list < RegIndice > regs_desactualizados = bloque.actualizar_regs(num_bloque, this->handler_tabla);

		if (regs_desactualizados.empty() == false) {
			nuevo_bloque.incorporar_regs(regs_desactualizados);
			offset = 0;
			nuevo_bloque.serializar(buffer, offset);
			this->handler_bloques.guardar_bloque(buffer, num_nuevo_bloque);
		}

		offset = 0;
		bloque.serializar(buffer, offset);
		this->handler_bloques.guardar_bloque(buffer, num_bloque);

		this->insertar_reg(reg);
	}
}

void Hash::agregar_nuevos_offsets(Cubo& bloque, int num_bloque, RegIndice& reg, const string& cadena,
		list < int > & offsets) {
	unsigned int offset;
	char buffer[TAM_CUBO];

	if (bloque.entra_en_bloque(cadena, offsets) == true) {
		if (reg.existe_elemento(cadena) == true) {
			Elemento& elemento = reg.buscar_elemento(cadena);
			elemento.agregar_nuevos_offsets(offsets);
		}
		else {
			Elemento elemento(cadena, offsets);
			reg.agregar_nuevo_elemento(elemento);
		}

		offset = 0;
		bloque.serializar(buffer, offset);
		this->handler_bloques.guardar_bloque(buffer, num_bloque);
	}
	else {
		Cubo bloque_sig;

		if (reg.get_bloque_sig() == -1) {
			RegIndice reg_aux(reg.get_clave());

			Elemento elemento(cadena, offsets);
			reg_aux.agregar_nuevo_elemento(elemento);

			bloque_sig.agregar_nuevo_reg(reg_aux);

			offset = 0;
			bloque_sig.serializar(buffer, offset);
			int num_bloque_sig = this->handler_bloques.guardar_bloque(buffer);

			reg.set_bloque_sig(num_bloque_sig);

			offset = 0;
			bloque.serializar(buffer, offset);
			this->handler_bloques.guardar_bloque(buffer, num_bloque);
		}
		else {
			offset = 0;
			this->handler_bloques.recuperar_bloque(buffer, reg.get_bloque_sig());
			bloque_sig.hidratar(buffer, offset);

			RegIndice& reg_aux = bloque_sig.buscar_reg(reg.get_clave());

			this->agregar_nuevos_offsets(bloque_sig, reg.get_bloque_sig(), reg_aux, cadena, offsets);
		}
	}
}

void Hash::alta(int clave, const string& cadena, list < int > & offsets) {
	Cubo bloque;
	unsigned int offset = 0;
	char buffer[TAM_CUBO];

	int num_bloque = this->handler_tabla.get_num_bloque(clave);
	this->handler_bloques.recuperar_bloque(buffer, num_bloque);
	bloque.hidratar(buffer, offset);

	if (bloque.existe_reg(clave) == true)
		this->agregar_nuevos_offsets(bloque, num_bloque, bloque.buscar_reg(clave), cadena, offsets);
	else {
		Elemento elemento(cadena, offsets);
		RegIndice reg(clave);
		reg.agregar_nuevo_elemento(elemento);
		this->insertar_reg(reg);
	}

}

bool Hash::eliminar_reg(int clave) {
	Cubo bloque;
	unsigned int offset = 0;
	char buffer[TAM_CUBO];

	int pos_tabla_bloque = this->handler_tabla.get_pos_tabla(clave);
	int num_bloque = this->handler_tabla.get_num_bloque(clave);
	this->handler_bloques.recuperar_bloque(buffer, num_bloque);
	bloque.hidratar(buffer, offset);

	if (!bloque.eliminar_reg(clave))
		return false;

	if (bloque.esta_vacio() == true) {
		int num_otro_bloque = this->handler_tabla.puedo_liberar_bloque(bloque, pos_tabla_bloque);
		if (num_otro_bloque != -1) {
			Cubo otro_bloque;

			offset = 0;
			this->handler_bloques.recuperar_bloque(buffer, num_otro_bloque);
			otro_bloque.hidratar(buffer, offset);
			this->handler_tabla.liberar_referencias(pos_tabla_bloque, num_otro_bloque, otro_bloque);

			otro_bloque.truncar_tam_disp();
			offset = 0;
			otro_bloque.serializar(buffer, offset);
			this->handler_bloques.guardar_bloque(buffer, num_otro_bloque);
			this->handler_bloques.eliminar_bloque(num_bloque);

			if (this->handler_tabla.mitades_iguales() == true)
				this->handler_tabla.truncar_tabla();
		}
		else {
			bloque.get_regs().clear();
			offset = 0;
			bloque.serializar(buffer, offset);
			this->handler_bloques.guardar_bloque(buffer, num_bloque);
		}
	}
	else {
		offset = 0;
		bloque.serializar(buffer, offset);
		this->handler_bloques.guardar_bloque(buffer, num_bloque);
	}

	return true;
}

void Hash::eliminar_offset(Cubo& bloque, int num_bloque, int clave, const string& cadena, int offset) {
	unsigned int offset_aux;
	char buffer[TAM_CUBO];

	if (bloque.existe_reg(clave) == true) {
		RegIndice& reg = bloque.buscar_reg(clave);

		if (reg.existe_elemento(cadena) == false) {
			if (reg.get_bloque_sig() == -1)
				return;
			else {
				Cubo bloque_sig;

				offset_aux = 0;
				this->handler_bloques.recuperar_bloque(buffer, reg.get_bloque_sig());
				bloque_sig.hidratar(buffer, offset_aux);

				this->eliminar_offset(bloque_sig, reg.get_bloque_sig(), clave, cadena, offset);
			}
		}
		else {
			Elemento& elemento = reg.buscar_elemento(cadena);
			if (elemento.eliminar_offset(offset) == true) {
				if (elemento.get_offsets().empty() == true)
					reg.eliminar_elemento(cadena);

				offset_aux = 0;
				bloque.serializar(buffer, offset_aux);
				this->handler_bloques.guardar_bloque(buffer, num_bloque);
			}
			else {
				if (reg.get_bloque_sig() == -1)
					return;
				else {
					Cubo bloque_sig;

					offset_aux = 0;
					this->handler_bloques.recuperar_bloque(buffer, reg.get_bloque_sig());
					bloque_sig.hidratar(buffer, offset_aux);

					this->eliminar_offset(bloque_sig, reg.get_bloque_sig(), clave, cadena, offset);
				}
			}
		}
	}
}

void Hash::baja(int clave, const string& cadena, int offset) {
	Cubo bloque;
	unsigned int offset_aux = 0;
	char buffer[TAM_CUBO];

	int num_bloque = this->handler_tabla.get_num_bloque(clave);
	this->handler_bloques.recuperar_bloque(buffer, num_bloque);
	bloque.hidratar(buffer, offset_aux);

	this->eliminar_offset(bloque, num_bloque, clave, cadena, offset);

	if (bloque.existe_reg(clave) == true) {
		RegIndice& reg = bloque.buscar_reg(clave);

		if (reg.get_elementos().empty() == true) {
			if (reg.get_bloque_sig() == -1)
				this->eliminar_reg(clave);
			else {
				Cubo bloque_sig;
				list < int > bloques_sigs;
				offset_aux = 0;

				this->obtener_reg(reg, bloque_sig, bloques_sigs, clave);

				while (reg.get_elementos().empty() == true && reg.get_bloque_sig() != -1)
					this->obtener_reg(reg, bloque_sig, bloques_sigs, clave);

				if (reg.get_elementos().empty() == true && reg.get_bloque_sig() == -1) {
					list < int > ::iterator it;
					for (it = bloques_sigs.begin(); it != bloques_sigs.end(); ++ it)
						this->handler_bloques.eliminar_bloque(*it);
					this->eliminar_reg(clave);
				}
			}
		}
	}
}

void Hash::obtener_reg(RegIndice& reg, Cubo& bloque_sig ,list< int > & bloques_sigs, int clave) {
	char buffer[TAM_CUBO];
	unsigned int offset_aux = 0;

	this->handler_bloques.recuperar_bloque(buffer, reg.get_bloque_sig());
	bloque_sig.hidratar(buffer,offset_aux);
	bloques_sigs.push_back(reg.get_bloque_sig());
	reg = bloque_sig.buscar_reg(clave);
}

void Hash::mostrar() {
	Cubo bloque;
	char buffer[TAM_CUBO];
	unsigned int offset;
	int cant_bloques = this->handler_bloques.get_tam_arch_bloques() / TAM_CUBO;

	cout << endl;
	for (int i = 0; i < cant_bloques; ++ i) {
		cout << "N° " << i << ":" << endl;
		offset = 0;
		this->handler_bloques.recuperar_bloque(buffer, i);
		bloque.hidratar(buffer, offset);
		bloque.toString();
		cout << endl;
	}
}
