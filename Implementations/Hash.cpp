#include "../Headers/Hash.h"

template<typename T, typename V>
Hash<T, V>::Hash(int n){
    this->size = n;
    this->array = new T**[n];
}

template<typename T, typename V>
Hash<T, V>::~Hash(){
    delete[] this->array;
}

template<typename T, typename V>
void Hash<T, V>::insert(V v){
    int k = key(v);
    if(this->array[k] == nullptr){
        this->array[k] = new T();
        this->array[k]->insert(v);
    }else{
        T* aux = this->array[k];
        aux->insert(v);
    }
}

template<typename T, typename V>
void Hash<T, V>::erase(V v){
    int k = key(v);
    T* aux = this->array[k];
    auto it = find_if(aux->begin(), aux->end(), [v](V vertex) { // función lambda para que compare a los vértices por id
        return v->id == vertex->id;
    });
    if(it != aux->end()){
        aux->erase(it);
    }
}

template<typename T, typename V>
bool Hash<T, V>::find(V v){
    int k = key(v);
    T* aux = this->array[k];
    auto it = find_if(aux->begin(), aux->end(), [v](V vertex) { // función lambda para que compare a los vértices por id
        return v->id == vertex->id;
    });
    return it != aux->end();
}

template<typename T, typename V>
V Hash<T, V>::get(V v){
    int k = key(v);
    T* aux = this->array[k];
    auto it = find_if(aux->begin(), aux->end(), [v](V vertex) { // función lambda para que compare a los vértices por id
        return v->id == vertex->id;
    });
    return *it;
}

template<typename T, typename V>
int Hash<T, V>::key(V v){
    return v->id % this->size;
}
