SRC = src
INC = include
OBJ = obj
BIN = bin
CXX = g++
CPPFLAGS = -Wall -g  -I$(INC) -c
#Para evitar el Warning
#g++: warning: obj/practica1.o: linker input file unused because linking not done
#g++: warning: obj/objetos.o: linker input file unused because linking not done

CPPFLAGS2 = -Wall -g  -I$(INC)
HDRS = $(INC)/objetos.h $(INC)/vertex.h

all: $(BIN)/practica1

# ************ Generación de programas ******************
$(BIN)/practica1: $(OBJ)/practica1.o $(OBJ)/objetos.o
	$(CXX) $(CPPFLAGS2) $^ -o $@ -lGL -lglut

$(OBJ)/practica1.o: $(SRC)/practica1.cpp $(HDRS)
	$(CXX) $(CPPFLAGS) $< -o $@

# ************ Generación de modulos ******************
$(OBJ)/objetos.o: $(SRC)/objetos.cpp $(HDRS)
	$(CXX) $(CPPFLAGS) $< -o $@

# ************ Generación de documentación ******************
#documentacion:
#	doxygen doc/doxys/Doxyfile


# ************ Limpieza ************
clean :
	-rm $(OBJ)/* $(SRC)/*~ $(INC)/*~ ./*~

#mrproper : clean
#	-rm $(BIN)/* doc/html/*
