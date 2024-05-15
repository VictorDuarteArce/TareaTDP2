#include "Vertex.h"

/*
    1-- 
   / \ \
  2---3-4
*/
int main(){
    Vertex* v = new Vertex(1);
    Vertex* w = new Vertex(2);
    Vertex* x = new Vertex(3);
    Vertex* y = new Vertex(4);
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
    cout << "Vertex 1: " << v->color << endl;
    v->printNeighbours();
    cout << "\nVertex 2: " << w->color << endl;
    w->printNeighbours();
    cout << "\nVertex 3: " << x->color << endl;
    x->printNeighbours();
    cout << "\nVertex 4: " << y->color << endl;
    y->printNeighbours();
    cout << endl;
    return 0;
}