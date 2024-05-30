#include "../Headers/Graph.h"

/*
    Method: Constructor->Graph
    Description: Constructor de la clase Graph
    Parameters:
        int V: Número de vértices
    Returns:
        -void
*/
Graph::Graph(int V){
    this->V = V;
    this->VList = (Vertex**)malloc(sizeof(Vertex*) * V);
    for(int i = 0; i < V; i++){
        VList[i] = NULL;
    }
    this->colors = 0;
}

/*
    Method: Constructor->Graph
    Description: Constructor de la clase Graph
    Parameters:
        string filename: Nombre del archivo a leer
    Returns:
        -void
*/
Graph::Graph(string filename){
    ifstream file(filename);
    string line;
    getline(file, line);
    istringstream iss(line);
    iss >> V;
    this->V = V;
    this->VList = (Vertex**)malloc(sizeof(Vertex*) * V);
    for(int i = 0; i < V; i++){
        VList[i] = NULL;
    }
    this->colors = 0;
    int i = 0;
    while (getline(file, line)){
        iss = istringstream(line);
        int j = 0;
        iss >> i >> j;
        this->agregarArista(i, j);
    }
    file.close();
}

/*
    Method: Destructor->Graph
    Description: Destructor de la clase Graph
    Parameters:
        -void
    Returns:
        -void
*/
Graph::~Graph(){
    for(int i = 0; i < V; i++){
        delete VList[i];
    }
    delete VList;
}

/*
    Method: Getter->getV
    Description: Devuelve el número de vértices
    Parameters:
        -void
    Returns:
        -int: Número de vértices
*/
int Graph::getV(){
    return this->V;
}

/*
    Method: Getter->getVertex
    Description: Devuelve un vértice
    Parameters:
        int i: Índice del vértice
    Returns:
        -Vertex*: Vértice
*/
Vertex* Graph::getVertex(int i){
    return VList[i];
}

/*
    Method: Getter->getColors
    Description: Devuelve el número de colores
    Parameters:
        -void
    Returns:
        -int: Número de colores
*/
int Graph::getColors(){
    return this->colors;
}

/*
    Method: agregarArista
    Description: Agrega una arista al grafo
    Parameters:
        int v: Vértice 1
        int w: Vértice 2
    Returns:
        -void
*/
void Graph::agregarArista(int v, int w){
    if(VList[v] == NULL && VList[w] == NULL){
        Vertex* v1 = new Vertex(v);
        VList[v] = v1;
        Vertex* v2 = new Vertex(w);
        VList[w] = v2;
        v1->getNeighbours()->insert(v2);
        v2->getNeighbours()->insert(v1);
    }else if(VList[v] == NULL){
        Vertex* v1 = new Vertex(v);
        VList[v] = v1;
        VList[w]->getNeighbours()->insert(v1);
        v1->getNeighbours()->insert(VList[w]);
    }else if(VList[w] == NULL){
        Vertex* v2 = new Vertex(w);
        VList[w] = v2;
        VList[v]->getNeighbours()->insert(v2);
        v2->getNeighbours()->insert(VList[v]);
    }else{
        VList[v]->getNeighbours()->insert(VList[w]);
        VList[w]->getNeighbours()->insert(VList[v]);
    }
    VList[v]->setGrade(VList[v]->getGrade() + 1);
    VList[w]->setGrade(VList[w]->getGrade() + 1);
}

/*
    Method: colorearGrafo
    Description: Colorea el grafo
    Parameters:
        -void
    Returns:
        -void
*/
void Graph::colorearGrafo(){
    priority_queue<Vertex*, vector<Vertex*>, bool(*)(const Vertex*, const Vertex*)> vertices(Vertex::CompareBySaturation);
    vertices.push(this->VList[0]);
    while(!vertices.empty()){
        Vertex* x = vertices.top();
        
        if(x->getColor() == -1){
            cout << "Coloreando: " << x->getId() << endl;
            x->colorVertex();
            x->actualizar();
        }else{
            while(!vertices.empty()){
                vertices.pop();
            }
        }
        this->calculateSaturation();
        for(int i = 0; i < this->V; i++){
            if(this->VList[i]->getColor() == -1){
                vertices.push(this->VList[i]);
            }
        }
    }
    for(int i = 0; i < this->V; i++){
        if(VList[i]->getColor() > this->colors){
            this->colors = VList[i]->getColor();
        }
    }
    this->colors++;
    for(int i = 0; i < this->V; i++){
        VList[i]->calculateSaturation();
    }
}

/*
    Method: printGraph
    Description: Imprime el grafo
    Parameters:
        -void
    Returns:
        -void
*/
void Graph::printGraph(){
    cout << "Graph with " << V << " vertices, and: " << this->colors << " colors." << endl;
    for(int i = 0; i < V; i++){
        cout << "head: " << i << 
        " Grade: " << VList[i]->getGrade() << 
        " Color: " << VList[i]->getColor() << 
        " Saturation: " << VList[i]->getSaturation() <<endl;
        cout << "neighbours: ";
        VList[i]->printNeighbours();
        cout << endl;
    }
}

/*
    Method: calculateSaturation
    Description: calcula el grado de saturación de todos los vértices del grafo
    Parameters:
        -void
    Returns:
        -void

*/

void Graph::calculateSaturation(){
    for(int i = 0; i < this->V; i++){
        this->VList[i]->calculateSaturation();
    }
}