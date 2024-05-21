#include "../Headers/Vertex.h"

Vertex::Vertex(int id){
    this->id = id;
    this->neighbours = new multiset<Vertex*, bool(*)(const Vertex*, const Vertex*)>(this->CompareBySaturation); //Esto es del paradigma funcionaaaaaaaaaal
    this->grade = 0;
    this->color = -1;
    this->saturation = 0;
    this->heuristic = 0.0;
}

Vertex::~Vertex(){
    
}

void Vertex::colorVertex(){ //Se puede mejorar aprovechando la estructura
    this->color = 0;
    auto it = this->neighbours->begin();
    //cout << "Id" << this->id << endl;
    while(it != this->neighbours->end()){
        if(this->color == (*it)->color){
            this->color++;
            //cout << "Color: " << this->color << " Neighbour: " << (*it)->id << endl;
            it = this->neighbours->begin();
        }else{
            //cout << "Neighbour: " << (*it)->id << " Color: " << (*it)->color << endl;
            //cout << "Color: " << this->color << " Neighbour: " << (*it)->id << endl;
            it++;
        }
    }
    this->calculateSaturation();
    this->actualizar();
}
void Vertex::calculateSaturation(){
    this->saturation = 0;
    for(auto x: *this->neighbours){
        if(x->color != -1){
            this->saturation++;
        }
    }
}
void Vertex::printNeighbours(){
    for(auto it = neighbours->begin(); it != neighbours->end(); *it++){
        if(*it != nullptr)
        cout << " -> " << (*it)->id;
        else return;
    }
}

void Vertex::actualizar(){ //O(n) en tiempo, O(n) en espacio
    //cout << "Updating vertex: " << this->id << endl;
    int i = 0;
    Vertex** vertices = new Vertex*[this->neighbours->size()];
    for(auto it = this->neighbours->begin(); it != this->neighbours->end(); it++){
        vertices[i] = *it;
        //cout << "Putting vertex " << vertices[i]->id << " in the array" << endl;
        i++;
    }
    int n = i;
    this->neighbours->clear();
    //cout << "Remaking de multiset..."<< endl;
    for(i = 0; i < n; i++){
        if(vertices[i] == nullptr) continue;
        this->neighbours->insert(vertices[i]);
    }
    delete[] vertices;
}

void Vertex::calculateHeuristic(){
    /*for(auto x: *this->neighbours){
        if(x->color != this->color){
            this->heuristic += 0.1;
            //cout << "Vertex " << this->id << " has a neighbour with a different color" << endl;
            //cout << "Heuristic: " << this->heuristic << endl;
        }
    }*/
    this->heuristic += this->grade;
}

void Vertex::calculateHeuristic(Vertex* v, multiset<Vertex*, bool(*)(const Vertex*, const Vertex*)> *P){ 
    //P podría ser una cola de prioridad, pero en ese caso habría que hacer un update de la cola de prioridad, entonces no sé si eso es más dificil que hacer un update de un multiset
    for(auto x: *this->neighbours){
        if(x->id == v->id) v->heuristic += 1000000;
    }
    //Actualizar P
    int i = 0;
    Vertex** vertices = new Vertex*[P->size()];
    for(auto it = P->begin(); it != P->end(); it++){
        vertices[i] = *it;
        //cout << "Putting vertex " << vertices[i]->id << " in the array" << endl;
        i++;
    }
    int n = i;
    P->clear();
    //cout << "Remaking de multiset..."<< endl;
    for(i = 0; i < n; i++){
        if(vertices[i] == nullptr) continue;
        P->insert(vertices[i]);
    }
    delete[] vertices;
}

bool Vertex::CompareBySaturation(const Vertex *l, const Vertex* r){
    if(l == nullptr || r == nullptr){
        return false;
    }
    //cout << "Comparing: " << l->saturation << " with " << r->saturation << endl;
    return l->saturation > r->saturation;
}

bool Vertex::CompareById(const Vertex *l, const Vertex* r){
    if(l == nullptr || r == nullptr){
        return false;
    }
    return l->id < r->id;
}

bool Vertex::CompareByHeuristic(const Vertex *l, const Vertex* r){
    if(l == nullptr || r == nullptr){
        return false;
    }
    return l->heuristic < r->heuristic;
}