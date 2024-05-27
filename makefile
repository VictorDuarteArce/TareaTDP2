FLAG ?= -O2

all: Graph.o Clique.o Vertex.o testGraph testClique main

Vertex.o: ./Headers/Vertex.h ./Implementations/Vertex.cpp
	g++ -c $(FLAG) ./Implementations/Vertex.cpp

Graph.o: Vertex.o ./Headers/Graph.h ./Implementations/Graph.cpp
	g++ -c $(FLAG) ./Implementations/Graph.cpp

Clique.o: Graph.o ./Headers/Clique.h ./Implementations/Clique.cpp 
	g++ -c $(FLAG) ./Implementations/Clique.cpp

Hash.o: ./Headers/Hash.h
	g++ -c $(FLAG) ./Implementations/Hash.cpp

testGraph: ./tests/testGraph.cpp Graph.o
	g++ $(FLAG) ./tests/testGraph.cpp Vertex.o Graph.o -o testGraph

testClique: ./tests/testClique.cpp Clique.o
	g++ $(FLAG) ./tests/testClique.cpp Vertex.o Graph.o Clique.o -o testClique

testVertex: ./tests/testVertex.cpp Vertex.o
	g++ $(FLAG) ./tests/testVertex.cpp Vertex.o -o testVertex

testHash: Vertex.o Hash.o ./tests/testHash.cpp
	g++ $(FLAG) Hash.o -o testHash

generator: ./Graphs/generator.cpp
	g++ $(FLAG) ./Graphs/generator.cpp -o generator

main: main.cpp Clique.o
	g++ $(FLAG) main.cpp Vertex.o Graph.o Clique.o -o main
	
clear:
	rm -f *.o testClique testGraph testGraph testVertex testHash generator main
