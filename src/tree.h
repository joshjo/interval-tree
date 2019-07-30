#ifndef TREE_H
#define TREE_H
#include <iostream>
#include <utility>

#include "node.h"

using namespace std;


template <class T>
class Tree {
public:
    typedef Node<T> Tnode;
    typedef pair<T, T> Interval;

    Tree() {
        this->root = NULL;
    }

    Tnode ** search(Interval value) {
        Tnode ** visitor = &(this->root);
        while ((*visitor) != NULL) {
            if (value == (*visitor)->value) {
                break;
            } else if (value < (*visitor)->value) {
                visitor = &((*visitor)->left);
            } else {
                visitor = &((*visitor)->right);
            }
        }
        return visitor;
    }

    bool insert(Interval value) {
        Tnode ** searchNode = this->search(value);
        if ((*searchNode) != NULL) {
            return false;
        }
        (*searchNode) = new Tnode(value);
        return true;
    }

    void print() {
        print(this->root);
        printf("\n");
    }

    void print(Tnode * visitor) {
        if (visitor != NULL) {
            printf("%d -> ", visitor->value);
            print(visitor->left);
            print(visitor->right);
        } else {
            printf("nil | ");
        }
    }

    Tnode * root;
};


#endif // TREE_H