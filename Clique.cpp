#include "Clique.h"


Clique::Clique(Graph* g, int size){
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

void Clique::BK(set<int> *R,set<int> *P, set<int> *X){
    if(P->empty() && X->empty()){
        if(R->size() > C.size()){
            this->C = *R;
            return;
        }
    }

    set<int> *P_new= new set<int>(*P); // esto copia P
    set<int> *X_new= new set<int>(*X); // esto copia X
    set<int> *P_iter = new set<int>(*P);
    /*cout << "P_iter: ";
    for(auto x: *P_iter){
        cout << x << " ";
    }
    putchar('\n');
    cout << "R: ";
    for(auto x: *R){
        cout << x << " ";
    }
    putchar('\n');*/
    for(auto v : *P_iter){
        set<int> *R1 = new set<int>(*R);
        R1->insert(v);

        set<int> *vecinos = new set<int>; // vecinos de v
        for(auto x: *this->graph->VList[v]->neighbours){
            vecinos->insert(x->id);
        }
        set<int> *P1 = new set<int>;
        set_intersection(P_new->begin(), P_new->end(), vecinos->begin(), vecinos->end(), inserter(*P1, P1->begin()));

        set<int> *X1 = new set<int>;
        set_intersection(X_new->begin(), X_new->end(), vecinos->begin(), vecinos->end(), inserter(*X1, X1->begin()));
        if(R1->size() + P1->size() > C.size()){
            //cout << "Llamado recursivo con V = " << v << endl;
            this->BK(R1,P1,X1);
            //cout << "Fin llamado recursivo con V = " << v << endl;
        }
        P_new->erase(v);
        X_new->insert(v);
    }
}

void Clique::printGraph(){
    this->graph->printGraph();
}

void Clique::printClique(){
    for(auto v : this->C){
        cout << v << " ";
    }
    cout << endl;
}
