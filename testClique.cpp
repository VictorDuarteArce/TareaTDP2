#include "Clique.h"

int main() {

    Graph *g = new Graph(4);
    g->agregarArista(0, 1);
    g->agregarArista(0, 2);
    g->agregarArista(1, 2);
    g->agregarArista(2, 3);

    Clique *c = new Clique(g, 4);
    c->graph->colorearGrafo();

    set<Vertex*, bool(*)(const Vertex*, const Vertex*)> *R = new set<Vertex*, bool(*)(const Vertex*, const Vertex*)>(Vertex::CompareById);
    set<Vertex*, bool(*)(const Vertex*, const Vertex*)> *P = new set<Vertex*, bool(*)(const Vertex*, const Vertex*)>(Vertex::CompareById);
    set<Vertex*, bool(*)(const Vertex*, const Vertex*)> *X = new set<Vertex*, bool(*)(const Vertex*, const Vertex*)>(Vertex::CompareById);
    for (int i = 0; i < c->graph->V; i++) {
        Vertex* v = new Vertex(i);
        cout << "Insertando " << v->id << endl;
        P->insert(v);
    }
    c->printGraph();
    c->BK(R, P, X);
    c->printClique();
    return 0;
}