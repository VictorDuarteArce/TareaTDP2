#include <set>
#include <iostream>
using namespace std;

class Vertex{
    public:
        Vertex(int id);
        ~Vertex();
        multiset<Vertex*, bool(*)(const Vertex* l, const Vertex* r)> *neighbours;
        int id;
        int color;
        int grade;
        int saturation;
        float heuristic;
        void colorVertex();
        void calculateSaturation();
        void printNeighbours();
        void actualizar();
        void calculateHeuristic();
        void calculateHeuristic(Vertex* v, multiset<Vertex*, bool(*)(const Vertex* l, const Vertex* r)> *C);
        
        static bool CompareBySaturation(const Vertex *l, const Vertex* r);
        static bool CompareById(const Vertex *l, const Vertex* r);
        static bool CompareByHeuristic(const Vertex *l, const Vertex* r);

};