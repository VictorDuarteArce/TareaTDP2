#include <iostream>
using namespace std;

// Estructura para representar un nodo AVL
struct Node {
    int key;
    Node* left;
    Node* right;
    int height;
    Node(int key){
        this->key = key;
        this->left = nullptr;
        this->right = nullptr;
        this->height = 1;
    };
    ~Node(){
        delete left;
        delete right;
    };
};

class AVL{
    public:
        Node* root;
        AVL();
        ~AVL();
        void insert(int key);
        void inorder();
        int height(Node* node);
        int getBalance(Node* node);
        int max(int a, int b);
        Node* rightRotate(Node* y);
        Node* leftRotate(Node* x);
        Node* insert(Node* node, int key);
        void inorder(Node* node);
};