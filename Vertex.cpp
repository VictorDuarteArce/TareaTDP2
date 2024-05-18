#include "Vertex.h"

Vertex::Vertex(int id){
    this->id = id;
    this->neighbours = new multiset<Vertex*, bool(*)(const Vertex*, const Vertex*)>(this->CompareByPointer); //Esto es del paradigma funcionaaaaaaaaaal
    this->grade = 0;
    this->color = -1;
    this->saturation = 0;
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

bool Vertex::operator<(const Vertex &v) const{ //Solucionar con paradigma funcional
    return this->saturation > v.saturation;
}

bool Vertex::CompareByPointer(const Vertex *l, const Vertex* r){
    /*if(l == nullptr || r == nullptr){
        return false;
    }*/
    //cout << "Comparing: " << l->saturation << " with " << r->saturation << endl;
    return l->saturation > r->saturation;
}