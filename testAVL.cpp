#include "AVL.h"

int main(){
    AVL *avl = new AVL();
    for(int i = 0; i < 1000; i++){
        avl->insert(rand() % 100);
    }
    avl->inorder();
    avl->~AVL();
    return 0;
}