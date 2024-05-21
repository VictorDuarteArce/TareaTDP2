#include <iostream>
#include <algorithm>
#include <iterator>
#include <vector>
#include <set>
#include "./Graph.h"
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
        multiset<Vertex*, bool(*)(const Vertex*, const Vertex*)> *P, 
        set<Vertex*, bool(*)(const Vertex*, const Vertex*)> *X);
    multiset<Vertex*, bool(*)(const Vertex*, const Vertex*)> *interseccion(
        multiset<Vertex*, bool(*)(const Vertex*, const Vertex*)> *P,
        multiset<Vertex*, bool(*)(const Vertex*, const Vertex*)> *vecinos);
    set<Vertex*, bool(*)(const Vertex*, const Vertex*)> *interseccion(
        set<Vertex*, bool(*)(const Vertex*, const Vertex*)> *P,
        multiset<Vertex*, bool(*)(const Vertex*, const Vertex*)> *vecinos);
    vector<Vertex*>* resta(vector<Vertex*>* P, multiset<Vertex*, bool(*)(const Vertex*, const Vertex*)>*pivotNeighbours);
    void printGraph();
    void printClique();
};
