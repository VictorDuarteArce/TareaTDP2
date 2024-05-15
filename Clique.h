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
    set<int> C; //El clique maximo
    Clique(Graph* graph, int size);
    Clique(string filename);
    void BK(set<int> *R,set<int> *P, set<int> *X);
    set<int>* neighbours(int v);
    void printGraph();
    void printClique();
};
