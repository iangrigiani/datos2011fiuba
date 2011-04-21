#include "Hash.h"

Hash::Hash(const string& ruta_arch_bloques, const string& ruta_arch_esp_libre) {
	this->handler_bloques.set_ruta_arch_bloques(ruta_arch_bloques);
	HandlerEspLibre handler_esp_libre(ruta_arch_esp_libre);
	this->handler_bloques.set_handler_esp_libre(handler_esp_libre);
}

void Hash::crear_condiciones_iniciales() {
	if (this->handler_tabla.tabla_vacia() == true) {
		Cubo bloque;
		int num_bloque = this->handler_bloques.guardar_bloque(bloque);
		this->handler_tabla.crear_tabla_inicial(num_bloque);
	}
}

void Hash::insercion(int clave, int offset) {
	int pos_tabla_bloque;
	Cubo bloque;
	Reg reg;

	int num_bloque = this->handler_tabla.get_num_bloque(clave, pos_tabla_bloque);
	this->handler_bloques.recuperar_bloque(bloque, num_bloque);

	if (bloque.buscar_reg(clave, reg) == true)
		this->agregar_nuevo_offset(bloque, num_bloque, reg, offset);
	else {
		reg.set_clave(clave);
		reg.agregar_nuevo_offset(offset);
		this->insertar_reg(reg);
	}
}

bool Hash::insertar_reg(const Reg& reg) {
	int pos_tabla_bloque;
	Cubo bloque;

	int num_bloque = this->handler_tabla.get_num_bloque(reg.get_clave(), pos_tabla_bloque);
	this->handler_bloques.recuperar_bloque(bloque, num_bloque);

	if (bloque.entra_en_bloque(reg.get_tam()) == true) {
		bloque.agregar_nuevo_reg(reg);
		this->handler_bloques.guardar_bloque(bloque, num_bloque);
	}
	else {
		int num_nuevo_bloque;

		int tam_disp_inicial = bloque.get_tam_disp();

		bloque.duplicar_tam_disp();
		Cubo nuevo_bloque(bloque.get_tam_disp());

		if (tam_disp_inicial == this->handler_tabla.get_tam_tabla()) {
			this->handler_tabla.duplicar_tabla();
			num_nuevo_bloque = this->handler_bloques.guardar_bloque(nuevo_bloque);
			this->handler_tabla.reemplazar_referencia(num_bloque, num_nuevo_bloque);
		}
		else {
			num_nuevo_bloque = this->handler_bloques.guardar_bloque(nuevo_bloque);
			this->handler_tabla.reemplazar_referencias(pos_tabla_bloque, num_nuevo_bloque, nuevo_bloque);
		}

		list < Reg > regs_desactualizados = this->handler_tabla.actualizar_regs(num_bloque, bloque);
		nuevo_bloque.incorporar_regs(regs_desactualizados);

		this->handler_bloques.guardar_bloque(bloque, num_bloque);
		this->handler_bloques.guardar_bloque(nuevo_bloque, num_nuevo_bloque);

		this->insertar_reg(reg);
	}
	return true;
}

void Hash::compactar_bloque(Cubo& bloque) {
	list < Reg > ::iterator it;

	it = bloque.get_regs().begin();
	while (it != bloque.get_regs().end()) {
		if ((*it).get_bloque_sig() != -1) {
			Reg reg_aux;
			Cubo bloque_sig;
			this->handler_bloques.recuperar_bloque(bloque_sig, (*it).get_bloque_sig());
			bloque_sig.buscar_reg((*it).get_clave(), reg_aux);
			if (bloque.entra_en_bloque(reg_aux.get_tam() - 2 * sizeof(int))) {
				(*it).incorporar_offsets(reg_aux.get_offsets());
				this->handler_bloques.get_handler_esp_libre().actualizar_alta_bloque_libre((*it).get_bloque_sig());
				(*it).set_bloque_sig(-1);
			}
		}
		++ it;
	}
}

bool Hash::eliminar_reg(int clave) {
	int pos_tabla_bloque;
	Cubo bloque;

	int num_bloque = this->handler_tabla.get_num_bloque(clave, pos_tabla_bloque);
	this->handler_bloques.recuperar_bloque(bloque, num_bloque);

	if (bloque.eliminar_reg(clave) == false)
		return false;

	if (bloque.esta_vacio() == true) {
		int num_otro_bloque = this->handler_tabla.puedo_liberar_bloque(bloque, pos_tabla_bloque);
		if (num_otro_bloque != -1) {
			Cubo otro_bloque;

			this->handler_bloques.recuperar_bloque(otro_bloque, num_otro_bloque);
			this->handler_tabla.liberar_referencias(pos_tabla_bloque, num_otro_bloque, otro_bloque);

			otro_bloque.truncar_tam_disp();
			this->handler_bloques.guardar_bloque(otro_bloque, num_otro_bloque);
			this->handler_bloques.eliminar_bloque(num_bloque);

			if (this->handler_tabla.mitades_iguales() == true)
				this->handler_tabla.truncar_tabla();
		}
		else {
			bloque.get_regs().clear();
			this->handler_bloques.guardar_bloque(bloque, num_bloque);
		}
	}
	else {
		this->compactar_bloque(bloque);
		this->handler_bloques.guardar_bloque(bloque, num_bloque);
	}

	return true;
}

void Hash::agregar_nuevo_offset(Cubo& bloque, int num_bloque, Reg& reg, int offset) {
	if (bloque.entra_en_bloque(sizeof(int)) == true) {
		reg.agregar_nuevo_offset(offset);
		this->handler_bloques.guardar_bloque(bloque, num_bloque);
	}
	else {
		if (reg.get_bloque_sig() == -1) {
			Reg reg_aux(reg.get_clave());
			Cubo bloque_sig;

			reg_aux.agregar_nuevo_offset(offset);
			bloque_sig.agregar_nuevo_reg(reg_aux);
			int num_bloque_sig = this->handler_bloques.guardar_bloque(bloque_sig);
			reg.set_bloque_sig(num_bloque_sig);
			this->handler_bloques.guardar_bloque(bloque);
		}
		else {
			Reg reg_aux;
			Cubo bloque_sig;

			this->handler_bloques.recuperar_bloque(bloque_sig, reg.get_bloque_sig());
			bloque_sig.buscar_reg(reg.get_clave(), reg_aux);
			reg_aux.agregar_nuevo_offset(offset);
			this->handler_bloques.guardar_bloque(bloque_sig, reg.get_bloque_sig());
		}
	}
}

bool Hash::eliminar_offset(int clave, int offset) {

}
