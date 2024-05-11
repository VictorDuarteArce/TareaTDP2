all: Graph.o Clique.o testClique main

Graph.o: Graph.h Graph.cpp
	g++ -c Graph.cpp

Clique.o: Graph.o Clique.h Clique.cpp 
	g++ -c Clique.cpp

testClique: testClique.cpp Clique.o
	g++ testClique.cpp Graph.o Clique.o -o testClique

main: main.cpp Clique.o
	g++ main.cpp Graph.o Clique.o -o main
	
clean:
	rm -f *.o testClique