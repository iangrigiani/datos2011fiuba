
target = tp

extension = cpp

CFLAGS = -Wall -pedantic -pedantic-errors

LDFLAGS =  

CXXSTD = c++98

CXXFLAGS += $(CFLAGS)

CXXFLAGS += -std=$(CXXSTD)

LD = $(CXX)

occ := $(CC)
ocxx := $(CXX)
orm := $(RM)
old := $(LD)

CC =  @echo "  CC  $@"; $(occ)
CXX = @echo "  CXX $@"; $(ocxx)
RM =  @echo "  CLEAN"; $(orm)
LD =  @echo "  LD  $@"; $(old)


fuentes_common += $(wildcard ArbolB+/*.$(extension))
fuentes_common += $(wildcard EstructurasEnComun/*.$(extension))
fuentes_common += $(wildcard EstructurasHash/*.$(extension))
#fuentes_common += $(wildcard Hash/*.$(extension))
fuentes_common += $(wildcard ManejadoresDeArchivos/*.$(extension))
fuentes_common += $(wildcard ManejadoresInforme/*.$(extension))
fuentes_common += $(wildcard ModuloDePersistencia/*.$(extension))
fuentes_common += $(wildcard ParserLibros/*.$(extension))
.PHONY: all clean

all: $(target) 

o_common_files = $(patsubst %.$(extension),%.o,$(fuentes_common))

%.deps: %.$(extension)
	@set -e; rm -f $@; \
		$(old) -MM -MG -MP $(CXXFLAGS) $(CFLAGS) $< -MF $@.$$$$; \
		sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.$$$$ > $@; \
		rm -f $@.$$$$

-include $(o_common_files:.o=.deps)

$(target): $(o_common_files)
	@if [ -z "$(o_common_files)" ]; \
	then \
		echo "No hay archivos de entrada, recuerde que la extensiÃ³n debe ser '.$(extension)'."; \
		false; \
	fi >&2
	$(LD) $(LDFLAGS) $(o_common_files) $(LOADLIBS) $(LDLIBS) -o $(target)

clean:
	$(RM) $(o_common_files) $(o_common_files:.o=.deps) $(target)