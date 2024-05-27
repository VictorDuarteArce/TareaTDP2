#ifndef VERTEX_H
#define VERTEX_H

#include <set>
#include <iostream>
using namespace std;

class Vertex{
    private:
        int id;
        int color;
        int grade;
        int saturation;
        float heuristic;
        multiset<Vertex*, bool(*)(const Vertex* l, const Vertex* r)> *neighbours;
    public:
        //Constructors
        Vertex(int id);

        //Destructor
        ~Vertex();
        
        //Getters
        int getId();
        int getColor();
        int getGrade();
        int getSaturation();
        float getHeuristic();
        multiset<Vertex*, bool(*)(const Vertex* l, const Vertex* r)> *getNeighbours();
        
        //Setters
        void setGrade(int grade);
        
        //Methods
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

#endif /* VERTEX_H */