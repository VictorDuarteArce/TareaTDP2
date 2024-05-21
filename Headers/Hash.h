#ifndef HASH_H
#define HASH_H

template <typename T, typename V> //T debe ser un tipo de set, y V debe ser un tipo de Vertex
class Hash{
    public:
        T** array; //arreglo de punteros
        int size;
        Hash(int n);
        ~Hash();
        void insert(V v);
        void erase(V v);
        bool find(V v);
        V get(V v);
        int key(V v);
};

#include "../Implementations/Hash.cpp"
#endif