#include "../Headers/Hash.h"
#include "../Headers/Vertex.h"
#include <iostream>
#include <set>
using namespace std;

int main(){
    Hash<set*<Vertex*>, Vertex*> *h = new Hash<set*<Vertex*>, Vertex*>(1000);
    for(int i = 0; i < 100; i++){
        for(int j = 0; j < 100; j++){
            Vertex* v = new Vertex(j);
            h->insert(v);
        }
    }
    return 0;
}