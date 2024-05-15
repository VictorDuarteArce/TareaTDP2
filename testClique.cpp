#include "Clique.h"

int main() {

    Graph *g = new Graph(4);
    g->agregarVertice(0, 1);
    g->agregarVertice(0, 2);
    g->agregarVertice(1, 2);
    g->agregarVertice(2, 3);

    Clique *c = new Clique(g, 4);

    set<int> *R = new set<int>;
    set<int> *P = new set<int>;
    set<int> *X = new set<int>;
    for (int i = 0; i < c->graph->V; i++) {
        P->insert(i);
    }
    c->printGraph();
    c->BK(R, P, X);
    c->printClique();
    return 0;
}