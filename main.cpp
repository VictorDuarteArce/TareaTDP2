#include "Clique.h"

int main(){
    string filename;
    cout << "Ingrese el nombre del archivo: ";
    cin >> filename;
    Clique *c = new Clique(filename);
    c->graph->colorearGrafo();
    
    set<Vertex*, bool(*)(const Vertex*, const Vertex*)> *R = new set<Vertex*, bool(*)(const Vertex*, const Vertex*)>(Vertex::CompareById);
    set<Vertex*, bool(*)(const Vertex*, const Vertex*)> *P = new set<Vertex*, bool(*)(const Vertex*, const Vertex*)>(Vertex::CompareById);
    set<Vertex*, bool(*)(const Vertex*, const Vertex*)> *X = new set<Vertex*, bool(*)(const Vertex*, const Vertex*)>(Vertex::CompareById);
    for(int i=0;i<c->size;i++){
        Vertex* v = new Vertex(i);
        P->insert(v);
    }
    c->printGraph();
    c->BK(R,P,X);
    c->printClique();
    cout << endl;
    return 0;
}
