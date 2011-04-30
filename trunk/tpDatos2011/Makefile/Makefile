# Makefile de ejemplo para C++
#
# Creado: jue abr 15 15:34:19 ART 2004
#
# Copyleft 2004 - Leandro Lucarella, Bajo licencia GPL [http://www.gnu.org/]
#

# CONFIGURACION
################

# Nombre del ejecutable.
#target = tp

# Extensión de los archivos a compilar (c para C, cpp o cc o cxx para C++).
extension = cpp


# Archivos con el código fuente que componen los ejecutables.
fuentesArbolB = $(wildcard ArbolB+/*.$(extension)) 
fuentesEstructurasEnComun = $(wildcard EstructurasEnComun/*.$(extension))
fuentesEstructurasHash = $(wildcard EstructurasHash/*.$(extension))
fuentesHash = $(wildcard Hash/*.$(extension))
fuentesManejadoresDeArchivos = $(wildcard ManejadoresDeArchivos/*.$(extension))
fuentesManejadoresInforme = $(wildcard ManejadoresInforme/*.$(extension))
fuentesModuloDePersistencia = $(wildcard ModuloDePersistencia/*.$(extension))
fuentesParserLibros = $(wildcard ParserLibros/*.$(extension))
fuentesMain = $(wildcard *.$(extension))


# Si usa funciones de math.h, descomentá (quitale el '#' a) la siguiente línea.
#math = si

# Si usa pthreads, descomentá (quitale el '#' a) la siguiente línea.
#pthreads = si

# Si usa gthreads, descomentá (quitale el '#' a) la siguiente línea.
#gthreads = si

# Si es un programa GTK+, descomentá (quitale el '#' a) la siguiente línea.
#gtk = si

# Si es un programa gtkmm, descomentá (quitale el '#' a) la siguiente línea.
#gtkmm = si

# Descomentar si se quiere ver como se invoca al compilador
#verbose = si


# CONFIGURACION "AVANZADA"
###########################

# Opciones para el compilador C/C++ en modo ansi.
#CFLAGS = -Wall -pedantic -pedantic-errors

# Para que explote lo mas posible
#CFLAGS += -O3 -DNDEBUG

# Para valgrind o debug
CFLAGS += -ggdb -DDEBUG -fno-inline

# Opciones del enlazador.
#LDFLAGS =

# Estandar de C a usar
#CSTD = c99

# Estandar de C++ a usar
CXXSTD = c++98

# Si se quiere compilar estaticamente, descomentar la siguiente linea
#static = si


# VARIABLES CALCULADAS A PARTIR DE LA CONFIGURACION
####################################################

# Agrego flags y libs de GTK+ de ser necesario.
ifdef gtk
CFLAGS += $(shell pkg-config --cflags gtk+-2.0)
LDFLAGS += $(shell pkg-config --libs gtk+-2.0)
endif

# Agrego flags y libs de GTK+ de ser necesario.
ifdef gtkmm
CFLAGS += $(shell pkg-config --cflags gtkmm-2.4)
LDFLAGS += $(shell pkg-config --libs gtkmm-2.4)
endif

# Agrego flags y libs de gthreads de ser necesario.
ifdef gthreads
CFLAGS += $(shell pkg-config --cflags gthread-2.0)
LDFLAGS += $(shell pkg-config --libs gthread-2.0)
endif

# Linkeo con libm de ser necesario.
ifdef math
LDFLAGS += -lm
endif

# Linkeo con pthreads de ser necesario.
ifdef pthreads
LDFLAGS += -lpthread -pthread
endif

ifdef static
LDFLAGS += -static
endif

# Pongo flags de C para C++ también
CXXFLAGS += $(CFLAGS)

# Uso enlazador de c++ si es código no C.
ifeq ($(extension), c)
CFLAGS += -std=$(CSTD)
LD = $(CC)
else
CXXFLAGS += -std=$(CXXSTD)
LD = $(CXX)
endif

# Si no especifica archivos, tomo todos.
#fuentes ?= $(wildcard *.$(extension))

occ := $(CC)
ocxx := $(CXX)
orm := $(RM)
old := $(LD)
ifdef verbose
RM := $(RM) -v
else
CC =  @echo "  CC  $@"; $(occ)
CXX = @echo "  CXX $@"; $(ocxx)
RM =  @echo "  CLEAN"; $(orm)
LD =  @echo "  LD  $@"; $(old)
endif


# REGLAS
#########

.PHONY: all clean

all: main

o_moduloDePersistencia_files = $(patsubst %.$(extension),%.o,$(fuentesModuloDePersistencia))
o_estructurasEnComun_files = $(patsubst %.$(extension),%.o,$(fuentesEstructurasEnComun)) $(o_moduloDePersistencia_files)
o_arbolB_files = $(patsubst %.$(extension),%.o,$(fuentesArbolB)) $(o_estructurasEnComun_files) 
o_estructurasHash_files = $(patsubst %.$(extension),%.o,$(fuentesEstructurasHash)) $(o_estructurasEnComun_files)
o_hash_files = $(patsubst %.$(extension),%.o,$(fuentesHash)) $(o_estructurasHash_files)
o_manejadoresDeArchivos_files = $(patsubst %.$(extension),%.o,$(fuentesManejadoresDeArchivos)) $(o_estructurasEnComun_files)
o_parserLibros_files = $(patsubst %.$(extension),%.o,$(fuentesParserLibros)) $(o_estructurasEnComun_files)
o_manejadoresInforme_files = $(patsubst %.$(extension),%.o,$(fuentesManejadoresInforme)) $(o_arbolB_files) $(o_hash_files) $(o_parserLibros_files) $(o_manejadoresDeArchivos_files)
o_main_files = $(patsubst %.$(extension),%.o,$(fuentesMain)) $(o_manejadoresInforme_files)


%.deps: %.$(extension)
	@set -e; rm -f $@; \
		$(old) -MM -MG -MP $(CXXFLAGS) $(CFLAGS) $< -MF $@.$$$$; \
		sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.$$$$ > $@; \
		rm -f $@.$$$$

-include $(o_files:.o=.deps)

main: $(o_main_files)
	@if [ -z "$(o_main_files)" ]; \
	then \
		echo "No hay archivos de entrada, recuerde que la extensión debe ser '.$(extension)'."; \
		false; \
	fi >&2
	$(LD) $(LDFLAGS) $(o_main_files) $(LOADLIBS) $(LDLIBS) -o main $(LDADD)

clean:
	@$(RM) -fv *.o main



