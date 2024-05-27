#include "../Headers/Graph.h"
/*
    0
   / \
  1---2--3
*/
int main(int argc, char** argv){
    Graph* g = new Graph(argv[1]);
    g->colorearGrafo();
    g->printGraph();
    for(int i = 0; i < g->getV(); i++)
        cout << "Vertex " << i << " has color " << g->getVertex(i)->getColor() << endl;
    
    cout << "Graph has " << g->getColors() << " colors." << endl;
    g->~Graph();
    return 0;
}