#include "HashPalabras.h"


void HashPalabras::crear_condiciones_iniciales() {
	if (this->handler_tabla.tabla_vacia() == true) {
		Cubo bloque;
		unsigned int offset = 0;
		char buffer[this->handler_bloques.get_tam_bloque()];

		bloque.serializar(buffer, offset);
		int num_bloque = this->handler_bloques.guardar_bloque(buffer);
		this->handler_tabla.crear_tabla_inicial(num_bloque);
	}
}

void HashPalabras::insertar_reg(const RegPalabras& reg) {
	int pos_tabla_bloque;
	Cubo bloque;
	unsigned int offset = 0;
	char buffer[this->handler_bloques.get_tam_bloque()];

	int num_bloque = this->handler_tabla.get_num_bloque(reg.get_clave(), pos_tabla_bloque);
	this->handler_bloques.recuperar_bloque(buffer, num_bloque);
	bloque.hidratar(buffer, offset);

	if (bloque.entra_en_bloque(reg) == true) {
		bloque.agregar_nuevo_reg(reg);
		offset = 0;
		bloque.serializar(buffer, offset);
		this->handler_bloques.guardar_bloque(buffer, num_bloque);
	}
	else {
		int num_nuevo_bloque;

		int tam_disp_inicial = bloque.get_tam_disp();

		bloque.duplicar_tam_disp();
		Cubo nuevo_bloque(bloque.get_tam_disp());

		if (tam_disp_inicial == this->handler_tabla.get_tam_tabla()) {
			this->handler_tabla.duplicar_tabla();
			this->insertar_bloque(nuevo_bloque,num_nuevo_bloque);
			this->handler_tabla.reemplazar_referencia(num_bloque, num_nuevo_bloque);
		}
		else {

			this->insertar_bloque(nuevo_bloque,num_nuevo_bloque);
			this->handler_tabla.reemplazar_referencias(pos_tabla_bloque, num_nuevo_bloque, nuevo_bloque);
		}

		list < RegPalabras > regs_desactualizados = bloque.actualizar_regs(num_bloque, this->handler_tabla);

		if(regs_desactualizados.size() > 0){

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

void HashPalabras::insertar_bloque(Cubo& nuevo_bloque,int& num_nuevo_bloque)
{
	char buffer[this->handler_bloques.get_tam_bloque()];
	unsigned int offset = 0;

	nuevo_bloque.serializar(buffer, offset);
	num_nuevo_bloque = this->handler_bloques.guardar_bloque(buffer);
}

void HashPalabras::agregar_nuevos_offsets(Cubo& bloque, int num_bloque, RegPalabras& reg, list < int > & offsets) {
	unsigned int offset;
	char buffer[this->handler_bloques.get_tam_bloque()];

	if (bloque.entra_en_bloque(offsets) == true) {
		reg.agregar_nuevos_offsets(offsets);
		offset = 0;
		bloque.serializar(buffer, offset);
		this->handler_bloques.guardar_bloque(buffer, num_bloque);
	}
	else {
		Cubo bloque_sig;

		if (reg.get_bloque_sig() == -1) {
			RegPalabras reg_aux(reg.get_clave());
			reg_aux.set_offsets(offsets);

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
			RegPalabras& reg_aux = bloque_sig.buscar_reg(reg.get_clave());
			this->agregar_nuevos_offsets(bloque_sig, reg.get_bloque_sig(), reg_aux, offsets);
		}
	}
}

void HashPalabras::insercion(int clave, list < int > & offsets) {
	int pos_tabla_bloque;
	Cubo bloque;
	unsigned int offset = 0;
	char buffer[this->handler_bloques.get_tam_bloque()];

	int num_bloque = this->handler_tabla.get_num_bloque(clave, pos_tabla_bloque);
	this->handler_bloques.recuperar_bloque(buffer, num_bloque);
	bloque.hidratar(buffer, offset);

	if (bloque.existe_reg(clave) == true)
		this->agregar_nuevos_offsets(bloque, num_bloque, bloque.buscar_reg(clave), offsets);
	else {
		RegPalabras reg(clave);
		reg.set_offsets(offsets);
		this->insertar_reg(reg);
	}
}

void HashPalabras::eliminar_offset(Cubo& bloque, int num_bloque, int clave, int offset) {
	unsigned int offset_aux;
	char buffer[this->handler_bloques.get_tam_bloque()];

	if (bloque.existe_reg(clave) == true) {
		RegPalabras& reg = bloque.buscar_reg(clave);
		if (reg.eliminar_offset(offset) == false) {
			if (reg.get_bloque_sig() == -1)
				return;
			else {
				Cubo bloque_sig;
				offset_aux = 0;
				this->handler_bloques.recuperar_bloque(buffer, reg.get_bloque_sig());
				bloque_sig.hidratar(buffer, offset_aux);
				this->eliminar_offset(bloque_sig, reg.get_bloque_sig(), clave, offset);
			}
		}
		else {
			offset_aux = 0;
			bloque.serializar(buffer, offset_aux);
			this->handler_bloques.guardar_bloque(buffer, num_bloque);
		}
	}
}

void HashPalabras::eliminacion(int clave, int offset) {
	int pos_tabla_bloque;
	Cubo bloque;
	unsigned int offset_aux = 0;
	char buffer[this->handler_bloques.get_tam_bloque()];

	int num_bloque = this->handler_tabla.get_num_bloque(clave, pos_tabla_bloque);
	this->handler_bloques.recuperar_bloque(buffer, num_bloque);
	bloque.hidratar(buffer, offset_aux);

	this->eliminar_offset(bloque, num_bloque, clave, offset);

	if (bloque.existe_reg(clave) == true) {
		RegPalabras& reg = bloque.buscar_reg(clave);
		if (reg.get_offsets().empty() == true) {
			if (reg.get_bloque_sig() == -1) {
				this->eliminar_reg(clave);
			}
			else {
				Cubo bloque_sig;
				list < int > bloques_sigs;
				offset_aux = 0;

				this->obtener_registro(reg,bloque_sig,bloques_sigs,clave);

				while (reg.get_offsets().empty() == true && reg.get_bloque_sig() != -1)
					this->obtener_registro(reg,bloque_sig,bloques_sigs,clave);

				if (reg.get_offsets().empty() == true && reg.get_bloque_sig() == -1) {
					list < int > ::iterator it;
					for (it = bloques_sigs.begin(); it != bloques_sigs.end(); ++ it)
						this->handler_bloques.eliminar_bloque(*it);
					this->eliminar_reg(clave);
				}
			}
		}
	}
}

void HashPalabras::obtener_registro(RegPalabras& reg,Cubo& bloque_sig ,list<int>& bloques_sigs,int clave)
{
	char buffer[this->handler_bloques.get_tam_bloque()];
	unsigned int offset_aux = 0;

	this->handler_bloques.recuperar_bloque(buffer, reg.get_bloque_sig());
	bloque_sig.hidratar(buffer,offset_aux);
	bloques_sigs.push_back(reg.get_bloque_sig());
	reg = bloque_sig.buscar_reg(clave);
}


bool HashPalabras::eliminar_reg(int clave) {
	int pos_tabla_bloque;
	Cubo bloque;
	unsigned int offset = 0;
	char buffer[this->handler_bloques.get_tam_bloque()];

	int num_bloque = this->handler_tabla.get_num_bloque(clave, pos_tabla_bloque);
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
