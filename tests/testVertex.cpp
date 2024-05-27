#include "../Headers/Vertex.h"
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
    v->getNeighbours()->insert(w);
    w->getNeighbours()->insert(v);
    v->getNeighbours()->insert(x);
    x->getNeighbours()->insert(v);
    x->getNeighbours()->insert(w);
    w->getNeighbours()->insert(x);
    x->getNeighbours()->insert(y);
    y->getNeighbours()->insert(x);
    v->getNeighbours()->insert(y);
    y->getNeighbours()->insert(v);
    v->colorVertex();
    w->colorVertex();
    x->colorVertex();
    y->colorVertex();

    cout << "Vertex 1: " << v->getColor() << " Saturation: " << v->getSaturation() << endl;
    v->printNeighbours();
    cout << "\nVertex 2: " << w->getColor() << " Saturation: " << w->getSaturation() << endl;
    w->printNeighbours();
    cout << "\nVertex 3: " << x->getColor() << " Saturation: " << x->getSaturation() << endl;
    x->printNeighbours();
    cout << "\nVertex 4: " << y->getColor() << " Saturation: " << y->getSaturation() << endl;
    y->printNeighbours();
    cout << endl;
    multiset<Vertex*, bool(*)(const Vertex*, const Vertex*)> vertices(Vertex::CompareBySaturation);
    vertices.insert(v);
    vertices.insert(w);
    vertices.insert(x);
    vertices.insert(y);
    for(auto it = vertices.begin(); it != vertices.end(); it++) 
        cout << "Color of Vertex " << (*it)->getId() << ": " << (*it)->getColor() << " Saturation: " << (*it)->getSaturation() << endl;
    cout << endl;
    return 0;
}