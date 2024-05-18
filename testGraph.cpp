#include "Graph.h"
/*
    0
   / \
  1---2--3
*/
int main(){
    Graph* g = new Graph("graph2.txt");
    g->colorearGrafo();
    g->printGraph();
    g->~Graph();
    return 0;
}