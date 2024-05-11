#include "Clique.h"


Clique::Clique(Graph* g, int size) {
    this->graph = g;
    this->size = size;
}

Clique::Clique(string filename){
    ifstream file(filename);
    string line;
    getline(file, line);
    istringstream iss(line);
    iss >> size;
    this->graph = new Graph(size);
    int i = 0;
    while (getline(file, line)){
        iss = istringstream(line);
        int j = 0;
        iss >> i >> j;
        this->graph->agregarVertice(i, j);
    }
    file.close();
}

set<int>* Clique::neighbours(int v) {
    set<int> *neibors=new set<int>;
    neibors = &this->graph->VList[v];
    return neibors;
} 

set<set<int>*> * Clique::BK(set<int> *R,set<int> *P, set<int> *X , set<set<int>*> *C){
    if (P->empty() && X->empty()){
        C->insert(R);
        return(C);
    }

    set<int> *P_new= new set<int>(*P); // esto copia P
    set<int> *X_new= new set<int>(*X); // esto copia X

    set<int> *P_iter = new set<int>(*P);
    for(auto v : *P_iter) {
        set<int> *R1 = new set<int>(*R);
        R1->insert(v);

        set<int> *vecinos = this->neighbours(v);
        set<int> *P1 = new set<int>;
        set_intersection(P_new->begin(), P_new->end(), vecinos->begin(), vecinos->end(), inserter(*P1, P1->begin()));

        set<int> *X1 = new set<int>;
        set_intersection(X_new->begin(), X_new->end(), vecinos->begin(), vecinos->end(), inserter(*X1, X1->begin()));
        C = this->BK(R1,P1,X1,C);

        P_new->erase(v);
        X_new->insert(v);
    }
    return C;


}
void Clique::printGraph(){
    this->graph->printGraph();
}