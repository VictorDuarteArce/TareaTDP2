all: Graph.o Clique.o Vertex.o testGraph testClique main

Vertex.o: ./Headers/Vertex.h ./Implementations/Vertex.cpp
	g++ -c ./Implementations/Vertex.cpp

Graph.o: Vertex.o ./Headers/Graph.h ./Implementations/Graph.cpp
	g++ -c ./Implementations/Graph.cpp

Clique.o: Graph.o ./Headers/Clique.h ./Implementations/Clique.cpp 
	g++ -c ./Implementations/Clique.cpp

Hash.o: ./Headers/Hash.h
	g++ -c ./Implementations/Hash.cpp

testGraph: ./tests/testGraph.cpp Graph.o
	g++ ./tests/testGraph.cpp Vertex.o Graph.o -o testGraph

testClique: ./tests/testClique.cpp Clique.o
	g++ ./tests/testClique.cpp Vertex.o Graph.o Clique.o -o testClique

testVertex: ./tests/Vertex.cpp Vertex.o
	g++ ./tests/Vertex.cpp Vertex.o -o testVertex

testHash: Vertex.o Hash.o ./tests/testHash.cpp
	g++ Hash.o -o testHash

generator: ./generator.cpp
	g++ ./generator.cpp -o generator

main: main.cpp Clique.o
	g++ main.cpp Vertex.o Graph.o Clique.o -o main
	
clear:
	rm -f *.o testClique testGraph testGraph testVertex testHash generator main
