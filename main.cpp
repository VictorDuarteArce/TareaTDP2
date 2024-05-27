#include "./Headers/Clique.h"
#include <ctime>


int main(int argc, char *argv[]){
    Clique *c;
    if(argc < 2){
        string filename;
        cout << "Ingrese el nombre del archivo: ";
        cin >> filename;
        c = new Clique(filename);
    }else{
        c = new Clique(argv[1]);
    }
    c->getGraph()->colorearGrafo();
    for(int i = 0; i < c->getSize(); i++){
        c->getGraph()->getVertex(i)->calculateHeuristic();
    }
    cout << "Heuristicas calculadas" << endl;
    set<Vertex*, bool(*)(const Vertex*, const Vertex*)> *
    R = new set<Vertex*, bool(*)(const Vertex*, const Vertex*)>(Vertex::CompareById);
    multiset<Vertex*, bool(*)(const Vertex*, const Vertex*)> *
    P = new multiset<Vertex*, bool(*)(const Vertex*, const Vertex*)>(Vertex::CompareByHeuristic);
    set<Vertex*, bool(*)(const Vertex*, const Vertex*)> *
    X = new set<Vertex*, bool(*)(const Vertex*, const Vertex*)>(Vertex::CompareById);
    for(int i=0;i<c->getSize();i++){
        Vertex* v = c->getGraph()->getVertex(i);
        P->insert(v);
    }
    
    clock_t start = clock();
    c->BK(R,P,X);
    clock_t end = clock();
    double elapsed_time = double(end-start)/CLOCKS_PER_SEC;
    cout << "Tiempo de ejecucion: " << elapsed_time << " segundos" << endl;
    c->printClique();
    cout << endl;
    cout << "Es Clique? " << c->isClique() << endl;
    return 0;
}
