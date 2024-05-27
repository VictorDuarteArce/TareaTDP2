#include "../Headers/Clique.h"
/*
    Method: Constructor->Clique
    Description: Constructor de la clase Clique
    Parameters:
        Graph* g: Grafo a analizar
        int size: Tamaño del grafo
    Returns: 
        -void
*/
Clique::Clique(Graph* g, int size){
    this->graph = g;
    this->size = size;
    this->C = set<Vertex*, bool(*)(const Vertex*, const Vertex*)>(Vertex::CompareById);
}

/*
    Method: Constructor->Clique
    Description: Constructor de la clase Clique
    Parameters:
        string filename: Nombre del archivo a leer
    Returns: 
        -void
*/
Clique::Clique(string filename){
    this->C = set<Vertex*, bool(*)(const Vertex*, const Vertex*)>(Vertex::CompareById);
    ifstream file(filename);
    string line;
    getline(file, line);
    istringstream iss(line);
    iss >> size;
    this->graph = new Graph(filename);
    file.close();
}

/*
    Method: Getter->getSize
    Description: Devuelve el tamaño del grafo
    Parameters:
        -void
    Returns: 
        -int: Tamaño del grafo
*/
int Clique::getSize(){
    return this->size;
}

/*
    Method: Getter->getGraph
    Description: Devuelve el grafo
    Parameters:
        -void
    Returns: 
        -Graph*: Grafo
*/
Graph* Clique::getGraph(){
    return this->graph;
}

/*
    Method: Getter->getClique
    Description: Devuelve el clique
    Parameters:
        -void
    Returns: 
        -set<Vertex*, bool(*)(const Vertex*, const Vertex*)>*: Clique
*/
set<Vertex*, bool(*)(const Vertex*, const Vertex*)>* Clique::getClique(){
    return &this->C;
}

/*
    Method: BK
    Description: Algoritmo de Bron-Kerbosch
    Parameters:
        set<Vertex*, bool(*)(const Vertex*, const Vertex*)> *R: Conjunto de vértices
        multiset<Vertex*, bool(*)(const Vertex*, const Vertex*)> *P: Conjunto de vértices
        set<Vertex*, bool(*)(const Vertex*, const Vertex*)> *X: Conjunto de vértices
    Returns: 
        -void

*/
void Clique::BK(set<Vertex*, bool(*)(const Vertex*, const Vertex*)> *R,
                multiset<Vertex*, bool(*)(const Vertex*, const Vertex*)> *P, 
                set<Vertex*, bool(*)(const Vertex*, const Vertex*)> *X){
    if(P->empty() && X->empty()){
        //cout << "Clique encontrada" << endl;
        if(R->size() > C.size()) this->C = *R;
        return;
    }
    vector<Vertex*>* P_iter = new vector<Vertex*>(); 
    for(auto it = P->begin(); it != P->end(); it++) P_iter->push_back(*it);
    Vertex* pivot = P_iter->back();
    P_iter = resta(P_iter, pivot->getNeighbours());
    pivot = *P_iter->begin();
    P_iter = resta(P_iter, pivot->getNeighbours());
    multiset<Vertex*, bool(*)(const Vertex*, const Vertex*)> *
    P_new= new multiset<Vertex*, bool(*)(const Vertex*, const Vertex*)>(*P); 
    set<Vertex*, bool(*)(const Vertex*, const Vertex*)> *
    X_new= new set<Vertex*, bool(*)(const Vertex*, const Vertex*)>(*X); 
    for(auto iter = P_iter->begin(); iter != P_iter->end(); iter++){
        Vertex* v = (*iter);
        set<Vertex*, bool(*)(const Vertex*, const Vertex*)> *
        R1 = new set<Vertex*, bool(*)(const Vertex*, const Vertex*)>(*R);
        R1->insert(v); 
        multiset<Vertex*, bool(*)(const Vertex*, const Vertex*)> *
        vecinos = v->getNeighbours(); 
        multiset<Vertex*, bool(*)(const Vertex*, const Vertex*)>*
        P1 = this->interseccion(P_new, vecinos); 
        set<Vertex*, bool(*)(const Vertex*, const Vertex*)>*
        X1 = this->interseccion(X_new, vecinos); 
        if(R1->size() + P1->size() > C.size() && this->getColors(R1, P1) > this->getColors(&C)){
            this->BK(R1,P1,X1);
        }
        auto it = find_if(P_new->begin(), P_new->end(), [v](Vertex* vertex) { 
            if(v == nullptr || vertex == nullptr) return false;
            return v->getId() == vertex->getId();
            });
        if(it != P_new->end()){
            P_new->erase(it);
        }
        X_new->insert(v);
        delete R1;
        delete P1;
        delete X1;
    }
    delete P_new;
    delete P_iter;
}

/*
    Method: printGraph
    Description: Imprime el grafo
    Parameters:
        -void
    Returns: 
        -void
*/
void Clique::printGraph(){
    this->graph->printGraph();
}

/*
    Method: printClique
    Description: Imprime el clique
    Parameters:
        -void
    Returns: 
        -void
*/
void Clique::printClique(){
    cout << "Clique máximo: ";
    for(auto v : this->C){
        cout << v->getId() << " ";
    }
    cout << endl;
    cout << "Tamaño del Clique: " << this->C.size() << endl;
}

/*
    Method: interseccion
    Description: Realiza la intersección de dos conjuntos
    Parameters:
        multiset<Vertex*, bool(*)(const Vertex*, const Vertex*)> *P: Conjunto de vértices
        multiset<Vertex*, bool(*)(const Vertex*, const Vertex*)> *vecinos: Conjunto de vértices
    Returns: 
        -multiset<Vertex*, bool(*)(const Vertex*, const Vertex*)>*: Intersección de los conjuntos
*/
multiset<Vertex*, bool(*)(const Vertex*, const Vertex*)> *Clique::interseccion(
    multiset<Vertex*, bool(*)(const Vertex*, const Vertex*)> *P, 
    multiset<Vertex*, bool(*)(const Vertex*, const Vertex*)> *vecinos){ 
    multiset<Vertex*, bool(*)(const Vertex*, const Vertex*)> *
    P1 = new multiset<Vertex*, bool(*)(const Vertex*, const Vertex*)>(Vertex::CompareByHeuristic);
    for (auto x : *vecinos) {
        auto it = find_if(P->begin(), P->end(), [x](Vertex* vertex) { 
            return x->getId() == vertex->getId();
        });
        if (it != P->end()) {
            P1->insert(x);
        }
    }

    return P1;
}

/*
    Method: interseccion
    Description: Realiza la intersección de dos conjuntos
    Parameters:
        set<Vertex*, bool(*)(const Vertex*, const Vertex*)> *P: Conjunto de vértices
        multiset<Vertex*, bool(*)(const Vertex*, const Vertex*)> *vecinos: Conjunto de vértices
    Returns: 
        -set<Vertex*, bool(*)(const Vertex*, const Vertex*)>*: Intersección de los conjuntos
*/
set<Vertex*, bool(*)(const Vertex*, const Vertex*)> *Clique::interseccion(
    set<Vertex*, bool(*)(const Vertex*, const Vertex*)> *P, 
    multiset<Vertex*, bool(*)(const Vertex*, const Vertex*)> *vecinos){ 
    set<Vertex*, bool(*)(const Vertex*, const Vertex*)> *
    P1 = new set<Vertex*, bool(*)(const Vertex*, const Vertex*)>(Vertex::CompareById);
    for(auto x: *vecinos){
        auto it = find_if(P->begin(), P->end(), [x](Vertex* vertex) { 
            return x->getId() == vertex->getId();
        });
        if (it != P->end()) {
            P1->insert(x);
        }
    }
    return P1;
}

/*
    Method: resta
    Description: Realiza la resta de dos conjuntos
    Parameters:
        vector<Vertex*>* P: Conjunto de vértices
        multiset<Vertex*, bool(*)(const Vertex*, const Vertex*)>* pivotNeighbours: Conjunto de vértices
    Returns: 
        -vector<Vertex*>*: Resta de los conjuntos
*/
vector<Vertex*>* Clique::resta(vector<Vertex*>* P, multiset<Vertex*, bool(*)(const Vertex*, const Vertex*)>* pivotNeighbours){
    if(P->empty()) return P;
    if(pivotNeighbours->empty()) return P;
    if(P == nullptr) return nullptr;
    if(pivotNeighbours == nullptr) return P;
    vector<Vertex*>* P_new = new vector<Vertex*>();
    for(auto x: *P){
        auto it = find_if(pivotNeighbours->begin(), pivotNeighbours->end(), [x](Vertex* vertex) { 
            return x->getId() == vertex->getId();
        });
        if(it == pivotNeighbours->end()){
            P_new->push_back(x);
        }
    }
    return P_new;
}

/*
    Method: isClique
    Description: Verifica si el conjunto es un clique
    Parameters:
        -void
    Returns: 
        -bool: Si es un clique

*/
bool Clique::isClique(){
    for(auto v: this->C){
        for(auto w: this->C){
            if(v->getId() == w->getId()) continue;
            
            auto it = find_if(v->getNeighbours()->begin(), v->getNeighbours()->end(), [w](Vertex* vertex) { 
                return w->getId() == vertex->getId();
            });

            if(it == v->getNeighbours()->end()) return false;
        }
    }
    return true;
}

/*
    Method: getColors
    Description: Obtiene el número de colores
    Parameters:
        set<Vertex*, bool(*)(const Vertex*, const Vertex*)> *vertices: Conjunto de vértices
    Returns: 
        -int: Número de colores
*/
int Clique::getColors(set<Vertex*, bool(*)(const Vertex*, const Vertex*)> *vertices){
    int colors = 0;
    set<int> colorsCheck;
    for(auto v: *vertices){
        if(colorsCheck.find(v->getColor()) == colorsCheck.end()){
            colorsCheck.insert(v->getColor());
            colors++;
        }
    }
    return colors;
}

/*
    Method: getColors
    Description: Obtiene el número de colores
    Parameters:
        multiset<Vertex*, bool(*)(const Vertex*, const Vertex*)> *vertices: Conjunto de vértices
    Returns:
        -int: Número de colores
*/
int Clique::getColors(multiset<Vertex*, bool(*)(const Vertex*, const Vertex*)> *vertices){
    int colors = 0;
    set<int> colorsCheck;
    for(auto v: *vertices){
        if(colorsCheck.find(v->getColor()) == colorsCheck.end()){
            colorsCheck.insert(v->getColor());
            colors++;
        }
    }
    return colors;
}

int Clique::getColors(set<Vertex*, bool(*)(const Vertex*, const Vertex*)>*R,
                    multiset<Vertex*, bool(*)(const Vertex*, const Vertex*)>*P){
    int colors = 0;
    set<int> colorsCheck;
    for(auto v: *R){
        if(colorsCheck.find(v->getColor()) == colorsCheck.end()){
            colorsCheck.insert(v->getColor());
            colors++;
        }
    }
    for(auto v: *P){
        if(colorsCheck.find(v->getColor()) == colorsCheck.end()){
            colorsCheck.insert(v->getColor());
            colors++;
        }
    }
    return colors;
}