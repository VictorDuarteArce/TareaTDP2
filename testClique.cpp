#include "Clique.h"

int main() {

    Graph *g = new Graph(4);
    g->agregarVertice(0, 1);
    g->agregarVertice(0, 2);
    g->agregarVertice(1, 2);
    g->agregarVertice(2, 3);

    Clique c(g, 4);

    set<int> *R = new set<int>;
    set<int> *P = new set<int>;
    set<int> *X = new set<int>;
    set<set<int>*> *C = new set<set<int>*>;
    for (int i = 0; i < 4; i++) {
        P->insert(i);
    }
    c.printGraph();
    C = c.BK(R, P, X, C);
    cout << "Cliques: " << endl;
    for (auto it = C->begin(); it != C->end(); it++) {
        for (auto it2 = (*it)->begin(); it2 != (*it)->end(); it2++) {
            cout << *it2 << " ";
        }
        cout << endl;
    }
    return 0;
}