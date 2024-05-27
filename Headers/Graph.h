#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <set>
#include <fstream>
#include <sstream>
#include "./Vertex.h"
using namespace std;

class Graph{
    private:
        int V;
        Vertex** VList; // Lista de punteros a vértices
        int colors;
    public:
        Graph(int V);
        Graph(string filename);
        ~Graph();
        int getV();
        Vertex* getVertex(int i);
        int getColors();
        
        void agregarArista(int v, int w);
        void colorearGrafo();
        void printGraph();
};

#endif /* GRAPH_H */