#include "../Headers/Vertex.h"

/*
    Method: Constructor->Vertex
    Description: Constructor de la clase Vertex
    Parameters:
        int id: Identificador del vértice
    Returns: 
        -void
*/
Vertex::Vertex(int id){
    this->id = id;
    this->neighbours = new multiset<Vertex*, bool(*)(const Vertex*, const Vertex*)>(this->CompareBySaturation); 
    this->grade = 0;
    this->color = -1;
    this->saturation = 0;
    this->heuristic = 0.0;
}

/*
    Method: Destructor->Vertex
    Description: Destructor de la clase Vertex
    Parameters:
        -void
    Returns: 
        -void
*/
Vertex::~Vertex(){
    delete this->neighbours;
}

/*
    Method: Getter->getId
    Description: Devuelve el identificador del vértice
    Parameters:
        -void
    Returns: 
        -int: Identificador del vértice
*/
int Vertex::getId(){return this->id;}

/*
    Method: Getter->getColor
    Description: Devuelve el color del vértice
    Parameters:
        -void
    Returns: 
        -int: Color del vértice
*/
int Vertex::getColor(){return this->color;}

/*
    Method: Getter->getGrade
    Description: Devuelve el grado del vértice
    Parameters:
        -void
    Returns: 
        -int: Grado del vértice
*/
int Vertex::getGrade(){return this->grade;}

/*
    Method: Getter->getSaturation
    Description: Devuelve la saturación del vértice
    Parameters:
        -void
    Returns: 
        -int: Saturación del vértice
*/
int Vertex::getSaturation(){return this->saturation;}

/*
    Method: Getter->getHeuristic
    Description: Devuelve la heurística del vértice
    Parameters:
        -void
    Returns: 
        -float: Heurística del vértice
*/
float Vertex::getHeuristic(){return this->heuristic;}

/*
    Method: Getter->getNeighbours
    Description: Devuelve los vecinos del vértice
    Parameters:
        -void
    Returns: 
        -multiset<Vertex*, bool(*)(const Vertex*, const Vertex*)>*: Vecinos del vértice
*/
multiset<Vertex*, bool(*)(const Vertex*, const Vertex*)> *Vertex::getNeighbours(){return this->neighbours;}

/*
    Method: Setter->setGrade
    Description: Establece el grado del vértice
    Parameters:
        int id: grado del vértice
    Returns: 
        -void
*/
void Vertex::setGrade(int grade){this->grade = grade;}

/*
    Method: colorVertex
    Description: Colorea el vértice
    Parameters:
        -void
    Returns: 
        -void
*/
void Vertex::colorVertex(){
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
    this->calculateSaturation();
    this->actualizar();
}

/*
    Method: calculateSaturation
    Description: Calcula la saturación del vértice
    Parameters:
        -void
    Returns: 
        -void
*/
void Vertex::calculateSaturation(){
    this->saturation = 0;
    for(auto x: *this->neighbours){
        if(x->color != -1){
            this->saturation++;
        }
    }
}

/*
    Method: printNeighbours
    Description: Imprime los vecinos del vértice
    Parameters:
        -void
    Returns: 
        -void
*/
void Vertex::printNeighbours(){
    for(auto it = neighbours->begin(); it != neighbours->end(); *it++){
        if(*it != nullptr)
        cout << " -> " << (*it)->id;
        else return;
    }
}

/*
    Method: actualizar
    Description: Actualiza los vecinos del vértice
    Parameters:
        -void
    Returns: 
        -void
*/
void Vertex::actualizar(){ 
    
    int i = 0;
    Vertex** vertices = new Vertex*[this->neighbours->size()];
    for(auto it = this->neighbours->begin(); it != this->neighbours->end(); it++){
        vertices[i] = *it;
        i++;
    }
    int n = i;
    this->neighbours->clear();
    
    for(i = 0; i < n; i++){
        if(vertices[i] == nullptr) continue;
        this->neighbours->insert(vertices[i]);
    }
    delete[] vertices;
}

/*
    Method: calculateHeuristic
    Description: Calcula la heurística del vértice
    Parameters:
        -void
    Returns: 
        -void
*/
void Vertex::calculateHeuristic(){
    this->heuristic += this->grade;
}

/*
    Method: calculateHeuristic
    Description: Calcula la heurística del vértice
    Parameters:
        Vertex* v: Vértice
        multiset<Vertex*, bool(*)(const Vertex*, const Vertex*)> *P: Conjunto de vértices
    Returns: 
        -void
*/
void Vertex::calculateHeuristic(Vertex* v, multiset<Vertex*, bool(*)(const Vertex*, const Vertex*)> *P){ 
    
    for(auto x: *this->neighbours){
        if(x->id == v->id) v->heuristic += 1000000;
    }
    //Actualizar P
    int i = 0;
    Vertex** vertices = new Vertex*[P->size()];
    for(auto it = P->begin(); it != P->end(); it++){
        vertices[i] = *it;
        i++;
    }
    int n = i;
    P->clear();
    for(i = 0; i < n; i++){
        if(vertices[i] == nullptr) continue;
        P->insert(vertices[i]);
    }
    delete[] vertices;
}

/*
    Method: CompareBySaturation
    Description: Compara dos vértices por saturación
    Parameters:
        const Vertex* l: Vértice 1
        const Vertex* r: Vértice 2
    Returns: 
        -bool: Resultado de la comparación
*/
bool Vertex::CompareBySaturation(const Vertex *l, const Vertex* r){
    if(l == nullptr || r == nullptr){
        return false;
    }
    return l->saturation > r->saturation;
}

/*
    Method: CompareById
    Description: Compara dos vértices por id
    Parameters:
        const Vertex* l: Vértice 1
        const Vertex* r: Vértice 2
    Returns: 
        -bool: Resultado de la comparación
*/
bool Vertex::CompareById(const Vertex *l, const Vertex* r){
    if(l == nullptr || r == nullptr){
        return false;
    }
    return l->id < r->id;
}

/*
    Method: CompareByHeuristic
    Description: Compara dos vértices por heurística
    Parameters:
        const Vertex* l: Vértice 1
        const Vertex* r: Vértice 2
    Returns: 
        -bool: Resultado de la comparación
*/
bool Vertex::CompareByHeuristic(const Vertex *l, const Vertex* r){
    if(l == nullptr || r == nullptr){
        return false;
    }
    return l->heuristic < r->heuristic;
}