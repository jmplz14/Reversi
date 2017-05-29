CXX = g++
CXXFLAGS = -Wall -g
INCLUDE = -I include/ 

bin/Reversi :  obj/main.o
	$(CXX) $(CXXFLAAGS) -o bin/Reversi obj/jugador.o obj/tablero.o obj/matriz.o obj/main.o 
obj/matriz.o : include/matriz.h src/matriz.cpp
	$(CXX) $(INCLUDE) -c $(CXXFLAAGS) -o obj/matriz.o src/matriz.cpp 
obj/tablero.o : include/matriz.h include/tablero.h src/tablero.cpp
	$(CXX) $(INCLUDE) -c $(CXXFLAAGS) -o obj/tablero.o src/tablero.cpp
obj/jugador.o : include/tablero.h include/jugador.h src/jugador.cpp
	$(CXX) $(INCLUDE) -c $(CXXFLAAGS) -o obj/jugador.o src/jugador.cpp
obj/main.o : obj/jugador.o obj/tablero.o obj/matriz.o src/main.cpp
	$(CXX) $(INCLUDE) -c $(CXXFLAAGS) -o obj/main.o src/main.cpp

