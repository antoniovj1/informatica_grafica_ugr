#Existen problemas con OpenGL y los divers de nvidia-340
#Para solucionarlos hay que añadir -L/usr/lib/nvidia-xxx (versión de nuestro dirvers)
#En mi caso la solución es añadir -L/usr/lib/nvidia-340

SRC = src
INC = include
OBJ = obj
BIN = bin
CXX = g++
CPPFLAGS = -Wall -g  -I$(INC) -c
#Para evitar el Warning
#g++: warning: obj/practica1.o: linker input file unused because linking not done
#g++: warning: obj/objetos.o: linker input file unused because linking not done

CPPFLAGS2 = -Wall -g  -I$(INC)  -pthread 
HDRS = $(INC)/objetos.h $(INC)/vertex.h $(INC)/file_ply_stl.h

all: $(BIN)/practica2


# ************ Generación de programas ******************
$(BIN)/practica2: $(OBJ)/practica2.o $(OBJ)/objetos.o  $(OBJ)/file_ply_stl.o
	$(CXX) $(CPPFLAGS2) $^ -o $@ -lGL -lglut -lpthread -L/usr/lib/nvidia-340

$(OBJ)/practica2.o: $(SRC)/practica2.cpp $(HDRS)
	$(CXX) $(CPPFLAGS) $< -o $@

# ************ Generación de modulos ******************
$(OBJ)/objetos.o: $(SRC)/objetos.cpp $(HDRS)
	$(CXX) $(CPPFLAGS) $< -o $@

$(OBJ)/file_ply_stl.o: $(SRC)/file_ply_stl.cc $(HDRS)
	$(CXX) $(CPPFLAGS) $< -o $@

# ************ Generación de documentación ******************
#documentacion:
#	doxygen doc/doxys/Doxyfile


# ************ Limpieza ************
clean :
	-rm  $(BIN) $(OBJ)/* $(SRC)/*~ $(INC)/*~ ./*~

#mrproper : clean
#	-rm $(BIN)/* doc/html/*
