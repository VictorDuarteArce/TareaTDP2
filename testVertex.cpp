#include "Vertex.h"
#include <queue>

/*
    1__
   / \ \
  2---3-4
*/

int main(){
    Vertex* v = new Vertex(1);
    Vertex* w = new Vertex(2);
    Vertex* x = new Vertex(3);
    Vertex* y = new Vertex(4);
    //cout << "Inserting neighbours" << endl;
    v->neighbours->insert(w);
    w->neighbours->insert(v);
    v->neighbours->insert(x);
    x->neighbours->insert(v);
    x->neighbours->insert(w);
    w->neighbours->insert(x);
    x->neighbours->insert(y);
    y->neighbours->insert(x);
    v->neighbours->insert(y);
    y->neighbours->insert(v);
    v->colorVertex();
    w->colorVertex();
    x->colorVertex();
    y->colorVertex();

    cout << "Vertex 1: " << v->color << " Saturation: " << v->saturation << endl;
    v->printNeighbours();
    cout << "\nVertex 2: " << w->color << " Saturation: " << w->saturation << endl;
    w->printNeighbours();
    cout << "\nVertex 3: " << x->color << " Saturation: " << x->saturation << endl;
    x->printNeighbours();
    cout << "\nVertex 4: " << y->color << " Saturation: " << y->saturation << endl;
    y->printNeighbours();
    cout << endl;
    multiset<Vertex*, bool(*)(const Vertex*, const Vertex*)> vertices(Vertex::CompareByPointer);
    vertices.insert(v);
    vertices.insert(w);
    vertices.insert(x);
    vertices.insert(y);
    for(auto it = vertices.begin(); it != vertices.end(); it++){
        cout << "Vertex: " << (*it)->id << " Saturation: " << (*it)->saturation << endl;
    }
    cout << endl;
    return 0;
}