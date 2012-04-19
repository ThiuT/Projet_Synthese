LFLAGS= -lsfml-audio -lsfml-graphics -lsfml-window -lsfml-system -lBox2D
CFLAGS= -ansi -pedantic

all: Test

Test: main.o DebugDraw.o
	g++ -o Test main.o DebugDraw.o $(LFLAGS)

main.o: main.cpp
	g++ -c main.cpp $(CFLAGS)

DebutDraw.o: DebugDraw.cpp
	g++ -c DebugDraw.cpp $(CFLAGS)
