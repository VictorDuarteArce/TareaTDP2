#include "../Headers/Clique.h"

int main() {

    Graph *g = new Graph(4);
    g->agregarArista(0, 1);
    g->agregarArista(0, 2);
    g->agregarArista(1, 2);
    g->agregarArista(2, 3);

    Clique *c = new Clique(g, 4);
    c->getGraph()->colorearGrafo();

    set<Vertex*, bool(*)(const Vertex*, const Vertex*)> *
    R = new set<Vertex*, bool(*)(const Vertex*, const Vertex*)>(Vertex::CompareById);
    multiset<Vertex*, bool(*)(const Vertex*, const Vertex*)> *
    P = new multiset<Vertex*, bool(*)(const Vertex*, const Vertex*)>(Vertex::CompareByHeuristic);
    set<Vertex*, bool(*)(const Vertex*, const Vertex*)> *X = new set<Vertex*, bool(*)(const Vertex*, const Vertex*)>(Vertex::CompareById);
    for (int i = 0; i < c->getSize(); i++) {
        c->getGraph()->getVertex(i)->calculateHeuristic();
        P->insert(c->getGraph()->getVertex(i));
        cout << "Vertex: " << c->getGraph()->getVertex(i)->getId() << " Heuristic: " << c->getGraph()->getVertex(i)->getHeuristic() << endl;
    }
    for(auto x: *P) cout << "Vertex: " << x->getId() << " Heuristic: " << x->getHeuristic() << endl;
    c->printGraph();
    c->BK(R, P, X);
    c->printClique();
    return 0;
}