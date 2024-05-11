#include "Graph.h"

Graph::Graph(int V){
    this->V = V;
    VList = new set<int>[V];
}

Graph::~Graph(){
    delete[] VList;
}

void Graph::agregarVertice(int v, int w){
    VList[v].insert(w);
    VList[w].insert(v);
}

void Graph::printGraph(){
    for(int i = 0; i < V; i++){
        cout << "Adjacency list of vertex " << i << endl;
        cout << "head: " << i;
        for(auto x : VList[i]){
            cout << " -> " << x;
        }
        cout << endl;
    }
}