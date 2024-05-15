#include "Vertex.h"

Vertex::Vertex(int id){
    this->id = id;
    this->neighbours = new set<Vertex*>;
    this->grade = 0;
    this->color = -1;
    this->saturation = 0;
}

Vertex::~Vertex(){
    delete neighbours;
}

void Vertex::colorVertex(){ //Se puede mejorar aprovechando la estructura
    this->color = 0;
    auto it = this->neighbours->begin();
    while(it != this->neighbours->end()){
        if(this->color == (*it)->color){
            this->color++;
            it = this->neighbours->begin();
        }else{
            it++;
        }
    }
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
    for(auto it = neighbours->begin(); it != neighbours->end(); it++){
        cout << " -> " << (*it)->id;
    }
}

bool Vertex::operator<(const Vertex &v) const{ //Solucionar con paradigma funcional
    return -this->saturation < -v.saturation;
}