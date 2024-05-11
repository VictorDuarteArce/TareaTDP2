#include <iostream>
#include <set>
using namespace std;

class Graph{
    public:
        Graph(int V);
        ~Graph();
        void agregarVertice(int v, int w);
        void printGraph();
        int V;
        set<int> *VList;
};