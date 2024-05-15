#include "Graph.h"

int main(){
    Graph *g = new Graph(4);
    g->agregarVertice(0, 1);
    g->agregarVertice(0, 2);
    g->agregarVertice(1, 2);
    g->agregarVertice(2, 3);
    g->colorearGrafo();
    g->printGraph();
    g->~Graph();
    return 0;
}