#include "AVL.h"

AVL::AVL(){root = nullptr;}
AVL::~AVL(){delete root;}

// Función para obtener la altura de un nodo
int AVL::height(Node* node) {
    if (node == nullptr) return 0;
    return node->height;
}

// Función para obtener el máximo de dos enteros
int AVL::max(int a, int b) {
    return (a < b) ? b : a;
}

// Función para rotar hacia la derecha un subárbol
Node* AVL::rightRotate(Node* y) {
    Node* x = y->left;
    Node* T2 = x->right;

    // Realizar la rotación
    x->right = y;
    y->left = T2;

    // Actualizar alturas
    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    // Devolver nueva raíz
    return x;
}

// Función para rotar hacia la izquierda un subárbol
Node* AVL::leftRotate(Node* x) {
    Node* y = x->right;
    Node* T2 = y->left;

    // Realizar la rotación
    y->left = x;
    x->right = T2;

    // Actualizar alturas
    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    // Devolver nueva raíz
    return y;
}

// Función para obtener el balance de un nodo
int AVL::getBalance(Node* node) {
    if (node == nullptr) return 0;
    return height(node->left) - height(node->right);
}

// Función para insertar un nodo en un árbol AVL
Node* AVL::insert(Node* node, int key) {
    // Paso 1: Insertar nodo en un árbol binario de búsqueda
    if (node == nullptr) return new Node(key);

    if (key < node->key)
        node->left = insert(node->left, key);
    else if (key > node->key)
        node->right = insert(node->right, key);
    else // Claves iguales se permiten en este árbol AVL
        node->left = insert(node->left, key);

    // Paso 2: Actualizar altura de este nodo padre
    node->height = 1 + max(height(node->left), height(node->right));

    // Paso 3: Obtener el factor de balance de este nodo para verificar si se ha desequilibrado
    int balance = getBalance(node);

    // Si el nodo se ha desequilibrado, hay cuatro casos posibles

    // Caso izquierda-izquierda
    if (balance > 1 && key <= node->left->key)
        return rightRotate(node);

    // Caso derecha-derecha
    if (balance < -1 && key > node->right->key)
        return leftRotate(node);

    // Caso izquierda-derecha
    if (balance > 1 && key > node->left->key) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    // Caso derecha-izquierda
    if (balance < -1 && key <= node->right->key) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    // Devolver el puntero del nodo sin cambios si no se ha desequilibrado
    return node;
}

// Función para recorrer un árbol AVL en orden
void AVL::inorder(Node* root) {
    if (root != nullptr) {
        inorder(root->left);
        cout << root->key << " ";
        inorder(root->right);
    }
}

// Función pública para insertar un nodo
void AVL::insert(int key) {
    root = insert(root, key);
}

// Función pública para recorrer en orden el árbol AVL
void AVL::inorder() {
    inorder(root);
}