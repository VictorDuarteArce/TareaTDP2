#include <iostream>
#include <set>
#include <fstream>
#include <sstream>
#include "Vertex.h"
using namespace std;

class Graph{
    public:
        int V;
        Vertex** VList; // Lista de punteros a vértices
        int colors;
        Graph(int V);
        Graph(string filename);
        ~Graph();
        void agregarArista(int v, int w);
        void colorearGrafo();
        void printGraph();
};