#include <set>
#include <iostream>
using namespace std;

class Vertex{
    public:
        Vertex(int id);
        ~Vertex();
        set<Vertex*> *neighbours;
        int id;
        int color;
        int grade;
        int saturation;
        void colorVertex();
        void calculateSaturation();
        void printNeighbours();
        bool operator<(const Vertex &v) const;
};