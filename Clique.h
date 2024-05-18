#include <iostream>
#include <algorithm>
#include <iterator>
#include <vector>
#include <set>
#include "Graph.h"
#include <fstream>
#include <sstream>


using namespace std;

class Clique {
    public:
    Graph *graph;
    int size;
    set<Vertex*, bool(*)(const Vertex*, const Vertex*)> C; //El clique maximo
    Clique(Graph* graph, int size);
    Clique(string filename);
    void BK(
        set<Vertex*, bool(*)(const Vertex*, const Vertex*)> *R,
        set<Vertex*, bool(*)(const Vertex*, const Vertex*)> *P, 
        set<Vertex*, bool(*)(const Vertex*, const Vertex*)> *X);
    set<Vertex*, bool(*)(const Vertex*, const Vertex*)> *interseccion(
        set<Vertex*, bool(*)(const Vertex*, const Vertex*)> *P,
        multiset<Vertex*, bool(*)(const Vertex*, const Vertex*)> *vecinos);
    void printGraph();
    void printClique();
};
