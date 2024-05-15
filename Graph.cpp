#include "Graph.h"

Graph::Graph(int V){
    this->V = V;
    this->VList = (Vertex**)malloc(sizeof(Vertex*) * V);
}

Graph::~Graph(){
    for(int i = 0; i < V; i++){
        delete VList[i];
    }
    delete VList;
}

void Graph::agregarVertice(int v, int w){
    if(VList[v] == NULL && VList[w] == NULL){
        Vertex* v1 = new Vertex(v);
        VList[v] = v1;
        Vertex* v2 = new Vertex(w);
        VList[w] = v2;
        v1->neighbours->insert(v2);
        v2->neighbours->insert(v1);
    }else if(VList[v] == NULL){
        Vertex* v1 = new Vertex(v);
        VList[v] = v1;
        VList[w]->neighbours->insert(v1);
        v1->neighbours->insert(VList[w]);
    }else if(VList[w] == NULL){
        Vertex* v2 = new Vertex(w);
        VList[w] = v2;
        VList[v]->neighbours->insert(v2);
        v2->neighbours->insert(VList[v]);
    }else{
        VList[v]->neighbours->insert(VList[w]);
        VList[w]->neighbours->insert(VList[v]);
    }
    VList[v]->grade++;
    VList[w]->grade++;
}

void Graph::colorearGrafo(){
    set<Vertex*> vertices;
    for(int i = 0; i < this->V; i++){
        vertices.insert(this->VList[i]);
    }
    for(auto x: vertices){
        x->colorVertex();
        x->calculateSaturation();
    }
    for(auto x: vertices){
        x->calculateSaturation();
    }
}

void Graph::printGraph(){
    cout << "Graph with " << V << " vertex" << endl;
    for(int i = 0; i < V; i++){
        cout << "head: " << i << 
        " Grade: " << VList[i]->grade << 
        " Color: " << VList[i]->color << 
        " Saturation: " << VList[i]->saturation <<endl;
        cout << "neighbours: ";
        VList[i]->printNeighbours();
        cout << endl;
    }
}