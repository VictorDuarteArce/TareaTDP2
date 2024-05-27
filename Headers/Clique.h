#ifndef CLIQUE_H
#define CLIQUE_H

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
    private:
        Graph *graph;
        int size;
        set<Vertex*, bool(*)(const Vertex*, const Vertex*)> C; 
    public:
        Clique(Graph* graph, int size);
        Clique(string filename);
        Graph* getGraph();
        int getSize();

        set<Vertex*, bool(*)(const Vertex*, const Vertex*)>* getClique();
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
        vector<Vertex*>* resta(vector<Vertex*>* P, 
            multiset<Vertex*, bool(*)(const Vertex*, const Vertex*)>*pivotNeighbours);
        int getColors(set<Vertex*, bool(*)(const Vertex*, const Vertex*)> *vertices);
        int getColors(multiset<Vertex*, bool(*)(const Vertex*, const Vertex*)> *vertices);
        void printGraph();
        void printClique();
        bool isClique();
    
};

#endif /* CLIQUE_H */