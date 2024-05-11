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
    Clique(Graph* graph, int size);
    Clique(string filename);
    set<set<int>*>* BK(set<int> *R,set<int> *P, set<int> *X , set<set<int>*> *C );
    set<int>* neighbours(int v);
    void printGraph();
};