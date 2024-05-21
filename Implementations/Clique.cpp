#include "../Headers/Clique.h"


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
//int i = 0;
void Clique::BK(set<Vertex*, bool(*)(const Vertex*, const Vertex*)> *R,
                multiset<Vertex*, bool(*)(const Vertex*, const Vertex*)> *P, 
                set<Vertex*, bool(*)(const Vertex*, const Vertex*)> *X){
    
    if(P->empty() && X->empty()){
        cout << "Clique encontrada" << endl;
        
        if(R->size() > C.size()){
            this->C = *R;
        }
        delete R;
        delete P;
        delete X;
        return;
    }
    

    vector<Vertex*>* P_iter = new vector<Vertex*>(); // Esto es para poder iterar sobre P
    
    for(auto it = P->begin(); it != P->end(); it++){
        P_iter->push_back(*it);
    }
    Vertex* pivot = P_iter->back();
    cout << "Pivot: " << pivot->id << " Heuristic: " << pivot->heuristic << endl;
    P_iter = resta(P_iter, pivot->neighbours);
    pivot = *P_iter->begin();
    cout << "Pivot: " << pivot->id << " Heuristic: " << pivot->heuristic << endl;
    P_iter = resta(P_iter, pivot->neighbours);
    multiset<Vertex*, bool(*)(const Vertex*, const Vertex*)> *
    P_new= new multiset<Vertex*, bool(*)(const Vertex*, const Vertex*)>(*P); //Esto debe poder intersectarse fácilmente, o sea tener un fácil acceso a datos, podría ser una hash de sets
    set<Vertex*, bool(*)(const Vertex*, const Vertex*)> *
    X_new= new set<Vertex*, bool(*)(const Vertex*, const Vertex*)>(*X); // Esto también debe poder intersectarse fácilmente, o sea tener un fácil acceso a datos, podría ser un hash de sets
    
    for(auto iter = P_iter->begin(); iter != P_iter->end(); iter++){
        cout << "Iterando sobre: " << (*iter)->id << endl;
        Vertex* v = (*iter);
        set<Vertex*, bool(*)(const Vertex*, const Vertex*)> *
        R1 = new set<Vertex*, bool(*)(const Vertex*, const Vertex*)>(*R);
        R1->insert(v); // esto puede ser un set para insertarse sin repeticiones, es necesario que los elementos de este conjunto no se repitan
        multiset<Vertex*, bool(*)(const Vertex*, const Vertex*)> *
        vecinos = this->graph->VList[v->id]->neighbours; // vecinos de v ya implementados, solamente se copia la referencia
        multiset<Vertex*, bool(*)(const Vertex*, const Vertex*)>*
        P1 = this->interseccion(P_new, vecinos); // P1 debe poder copiarse rápidamente, podría ser un hash de sets
        
        set<Vertex*, bool(*)(const Vertex*, const Vertex*)>*
        X1 = this->interseccion(X_new, vecinos); // esto debe poder copiarse rápidamente, podría ser un hash de sets
        
        
        cout << "R1: ";
        for(auto x: *R1){
            cout << x->id << " ";
        }
        cout << endl;
        cout << "P1: ";
        for(auto x: *P1){
            cout << x->id << " ";
        }
        cout << endl;
        cout << "X1: ";
        for(auto x: *X1){
            cout << x->id << " ";
        }
        cout << endl;
        if(R1->size() + P1->size() > C.size()){
            cout << "Llamado recursivo con V = " << v->id << endl;
            this->BK(R1,P1,X1);
            cout << "Fin de llamado recursivo con V = " << v->id << endl;
        }
        auto it = find_if(P_new->begin(), P_new->end(), [v](Vertex* vertex) { // función lambda para que compare a los vértices por id
            if(v == nullptr || vertex == nullptr) return false;
            return v->id == vertex->id;
            });
        if(it != P_new->end()){
            P_new->erase(it);
        }
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

multiset<Vertex*, bool(*)(const Vertex*, const Vertex*)> *Clique::interseccion(
    multiset<Vertex*, bool(*)(const Vertex*, const Vertex*)> *P, // P es un conjunto de vertices comparados por heurística
    multiset<Vertex*, bool(*)(const Vertex*, const Vertex*)> *vecinos){ // vecinos es un multiconjunto de vertices comparados por saturacion 
    multiset<Vertex*, bool(*)(const Vertex*, const Vertex*)> *
    P1 = new multiset<Vertex*, bool(*)(const Vertex*, const Vertex*)>(Vertex::CompareByHeuristic);
    for (auto x : *vecinos) {
        auto it = find_if(P->begin(), P->end(), [x](Vertex* vertex) { // función lambda para que compare a los vértices por id
            return x->id == vertex->id;
        });
        if (it != P->end()) {
            P1->insert(x);
        }
    }

    return P1;
}

set<Vertex*, bool(*)(const Vertex*, const Vertex*)> *Clique::interseccion(
    set<Vertex*, bool(*)(const Vertex*, const Vertex*)> *P, // P es un conjunto de vertices comparados por id
    multiset<Vertex*, bool(*)(const Vertex*, const Vertex*)> *vecinos){ // vecinos es un multiconjunto de vertices comparados por saturacion 
    set<Vertex*, bool(*)(const Vertex*, const Vertex*)> *
    P1 = new set<Vertex*, bool(*)(const Vertex*, const Vertex*)>(Vertex::CompareById);
    for(auto x: *vecinos){
        auto it = find_if(P->begin(), P->end(), [x](Vertex* vertex) { // función lambda para que compare a los vértices por id
            return x->id == vertex->id;
        });
        if (it != P->end()) {
            P1->insert(x);
        }
    }
    return P1;
}

vector<Vertex*>* Clique::resta(vector<Vertex*>* P, multiset<Vertex*, bool(*)(const Vertex*, const Vertex*)>* pivotNeighbours){
    if(P->empty()) return P;
    if(pivotNeighbours->empty()) return P;
    if(P == nullptr) return nullptr;
    if(pivotNeighbours == nullptr) return P;
    vector<Vertex*>* P_new = new vector<Vertex*>();
    for(auto x: *P){
        auto it = find_if(pivotNeighbours->begin(), pivotNeighbours->end(), [x](Vertex* vertex) { // función lambda para que compare a los vértices por id
            return x->id == vertex->id;
        });
        if(it == pivotNeighbours->end()){
            P_new->push_back(x);
        }
    }
    return P_new;
}
