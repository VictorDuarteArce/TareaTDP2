#include "Graph.h"
/*
    0
   / \
  1---2--3
*/
int main(int argc, char** argv){
    Graph* g = new Graph(argv[1]);
    g->colorearGrafo();
    //g->printGraph();
    /*for(int i = 0; i < g->V; i++){
        cout << "Vertex " << i << " has color " << g->VList[i]->color << endl;
    }*/
    cout << "Graph has " << g->colors << " colors." << endl;
    g->~Graph();
    return 0;
}