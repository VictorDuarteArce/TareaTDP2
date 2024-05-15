#include "Clique.h"

int main(){
    string filename;
    cout << "Ingrese el nombre del archivo: ";
    cin >> filename;
    Clique *c = new Clique(filename);
    
    set<int> *R = new set<int>;
    set<int> *P = new set<int>;
    set<int> *X = new set<int>;
    for(int i=0;i<c->size;i++){
        P->insert(i);
    }
    c->printGraph();
    c->BK(R,P,X);
    cout << "Clique máximo: " << endl;
    for(auto v: c->C){
        cout<< v << " ";
    }
    cout << endl;
    return 0;
}
