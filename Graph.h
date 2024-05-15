#include <iostream>
#include <set>
#include "Vertex.h"
using namespace std;

class Graph{
    public:
        Graph(int V);
        ~Graph();
        void agregarVertice(int v, int w);
        void colorearGrafo();
        void printGraph();
        int V;
        Vertex** VList; // Lista de punteros a vértices
};