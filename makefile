all: Graph.o Clique.o Vertex.o testGraph testClique main

Vertex.o: Vertex.h Vertex.cpp
	g++ -c Vertex.cpp

Graph.o: Vertex.o Graph.h Graph.cpp
	g++ -c Graph.cpp

Clique.o: Graph.o Clique.h Clique.cpp 
	g++ -c Clique.cpp

AVL.o: AVL.h AVL.cpp
	g++ -c AVL.cpp
	
testGraph: testGraph.cpp Graph.o
	g++ testGraph.cpp Vertex.o Graph.o -o testGraph

testClique: testClique.cpp Clique.o
	g++ testClique.cpp Vertex.o Graph.o Clique.o -o testClique

testVertex: testVertex.cpp Vertex.o
	g++ testVertex.cpp Vertex.o -o testVertex

testAVL: testAVL.cpp AVL.o
	g++ testAVL.cpp AVL.o -o testAVL

main: main.cpp Clique.o
	g++ main.cpp Vertex.o Graph.o Clique.o -o main
	
clear:
	rm -f *.o testClique testGraph main
