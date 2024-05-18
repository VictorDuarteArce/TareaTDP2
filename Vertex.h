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
        void colorVertex();
        void calculateSaturation();
        void printNeighbours();
        void actualizar();
        bool operator<(const Vertex &v) const;
        static bool CompareByPointer(const Vertex *l, const Vertex* r);
};