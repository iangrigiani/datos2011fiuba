
target = bookerio

extension = cpp

CFLAGS = -Wall -pedantic -pedantic-errors -g

LDFLAGS =  

LDFLAGSTESTS =
LOADLIBSTESTS = -lcppunit
LDLIBSTESTS = -ldl
targettests = tpDatosTests

main = src/Main.cpp
maintest = test/main.cpp

CXXFLAGS += $(CFLAGS)

LD = $(CXX)

occ := $(CC)
ocxx := $(CXX)
orm := $(RM)
old := $(LD)

CC =  @echo "  CC  $@"; $(occ)
CXX = @echo "  CXX $@"; $(ocxx)
RM =  @echo "  CLEAN"; $(orm)
LD =  @echo "  LD  $@"; $(old)


fuentes_common += $(wildcard src/ArbolB+/*.$(extension))
fuentes_common += $(wildcard src/EstructurasEnComun/*.$(extension))
fuentes_common += $(wildcard src/EstructurasHash/*.$(extension))
fuentes_common += $(wildcard src/Hash/*.$(extension))
fuentes_common += $(wildcard src/ManejadoresDeArchivos/*.$(extension))
fuentes_common += $(wildcard src/ManejadoresInforme/*.$(extension))
fuentes_common += $(wildcard src/ModuloDePersistencia/*.$(extension))
fuentes_common += $(wildcard src/ParserLibros/*.$(extension))

fuentes_tests += $(wildcard test/Test*.cpp)
.PHONY: all clean

all: $(target) 

o_common_files = $(patsubst %.$(extension),%.o,$(fuentes_common))
o_common_test_files = $(patsubst %.$(extension),%.o,$(fuentes_tests))

%.deps: %.$(extension)
	@set -e; rm -f $@; \
		$(old) -MM -MG -MP $(CXXFLAGS) $(CFLAGS) $< -MF $@.$$$$; \
		sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.$$$$ > $@; \
		rm -f $@.$$$$

-include $(o_common_files:.o=.deps)
-include $(o_common_test_files:.o=.deps)

$(target): $(o_common_files)
	@if [ -z "$(o_common_files)" ]; \
	then \
		echo "No hay archivos de entrada, recuerde que la extension debe ser '.$(extension)'."; \
		false; \
	fi >&2
	$(LD) $(LDFLAGS) $(main) $(o_common_files) $(LOADLIBS) $(LDLIBS) -o $(target)

clean:
	$(RM) $(o_common_files) $(o_common_files:.o=.deps)

test: $(o_common_files) $(o_common_test_files)
#	$(LD) $(LDFLAGSTESTS) $(maintest) $(o_common_files) $(LOADLIBSTESTS) $(LDLIBSTESTS) -o $(targettests)
	g++ "test/main.cpp" $(o_common_test_files) $(o_common_files) -lcppunit -ldl -o tests
