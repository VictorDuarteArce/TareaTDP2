#include "Clique.h"


Clique::Clique(Graph* g, int size){
    this->graph = g;
    this->size = size;
    this->C = set<Vertex*, bool(*)(const Vertex*, const Vertex*)>(Vertex::CompareById);
}

Clique::Clique(string filename){
    this->C = set<Vertex*, bool(*)(const Vertex*, const Vertex*)>(Vertex::CompareById);
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
        this->graph->agregarArista(i, j);
    }
    file.close();
}

void Clique::BK(set<Vertex*, bool(*)(const Vertex*, const Vertex*)> *R,
                set<Vertex*, bool(*)(const Vertex*, const Vertex*)> *P, 
                set<Vertex*, bool(*)(const Vertex*, const Vertex*)> *X){
    if(P->empty() && X->empty()){
        if(R->size() > C.size()){
            this->C = *R;
            return;
        }
    }

    set<Vertex*, bool(*)(const Vertex*, const Vertex*)> *P_new= new set<Vertex*, bool(*)(const Vertex*, const Vertex*)>(*P); // esto copia P
    set<Vertex*, bool(*)(const Vertex*, const Vertex*)> *X_new= new set<Vertex*, bool(*)(const Vertex*, const Vertex*)>(*X); // esto copia X
    set<Vertex*, bool(*)(const Vertex*, const Vertex*)> *P_iter = new set<Vertex*, bool(*)(const Vertex*, const Vertex*)>(*P);
    /*cout << "P_iter: ";
    for(auto x: *P_iter){
        cout << x->id << " ";
    }*/
    //putchar('\n');
    /*cout << "R: ";
    for(auto x: *R){
        cout << x << " ";
    }
    putchar('\n');*/
    for(auto v : *P_iter){
        //cout << "Iterando sobre P con v = " << v->id << endl;
        set<Vertex*, bool(*)(const Vertex*, const Vertex*)> *R1 = new set<Vertex*, bool(*)(const Vertex*, const Vertex*)>(*R);
        R1->insert(v);

        multiset<Vertex*, bool(*)(const Vertex*, const Vertex*)> *vecinos = this->graph->VList[v->id]->neighbours; // vecinos de v
        set<Vertex*, bool(*)(const Vertex*, const Vertex*)>*P1 = this->interseccion(P_new, vecinos); // P1 = P_new interseccion vecinos
        /*cout << "Vecinos de " << v->id << ": ";
        for(auto x: *vecinos){
            cout << x->id << " ";
        }
        cout << "P_new: ";
        for(auto x: *P_new){
            cout << x->id << " ";
        }
        cout << endl;
        cout << "P1: ";
        for(auto x: *P1){
            cout << x->id << " ";
        }
        cout << endl;*/
        set<Vertex*, bool(*)(const Vertex*, const Vertex*)>*
        X1 = this->interseccion(X_new, vecinos); // X1 = X_new interseccion vecinos
        if(R1->size() + P1->size() > C.size()){
            //cout << "Llamado recursivo con V = " << v->id << endl;
            this->BK(R1,P1,X1);
            //cout << "Fin llamado recursivo con V = " << v->id << endl;
        }
        P_new->erase(v);
        X_new->insert(v);
    }
}

void Clique::printGraph(){
    this->graph->printGraph();
}

void Clique::printClique(){
    cout << "Clique máximo: ";
    for(auto v : this->C){
        cout << v->id << " ";
    }
    cout << endl;
    cout << "Tamaño del Clique: " << this->C.size() << endl;
}

set<Vertex*, bool(*)(const Vertex*, const Vertex*)> *Clique::interseccion(
    set<Vertex*, bool(*)(const Vertex*, const Vertex*)> *P, // P es un conjunto de vertices comparados por id
    multiset<Vertex*, bool(*)(const Vertex*, const Vertex*)> *vecinos){ // vecinos es un multiconjunto de vertices comparados por saturacion 
    set<Vertex*, bool(*)(const Vertex*, const Vertex*)> *P1 = new set<Vertex*, bool(*)(const Vertex*, const Vertex*)>(Vertex::CompareById);
    for(auto x: *vecinos){
        if(P->find(x) != P->end()){
            P1->insert(x);
        }
    }
    return P1;
}