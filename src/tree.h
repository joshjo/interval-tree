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

    Tnode ** search(Interval value, Tnode * & parent = NULL) {
        Tnode ** visitor = &(this->root);
        while ((*visitor) != NULL) {
            parent = *visitor;
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
        Tnode * parent = NULL;
        Tnode ** searchNode = this->search(value, parent);
        if ((*searchNode) != NULL) {
            return false;
        }
        (*searchNode) = new Tnode(value);
        (*searchNode)->parent = parent;
        update_weights(searchNode);
        return true;
    }

    void update_weights(Tnode ** visitor) {
        Tnode * parent = (*visitor)->parent;
        if (parent != NULL) {
            if ((*visitor)->max > parent->max) {
                parent->max = (*visitor)->max;
                update_weights(&parent);
            }
        }
    }

    void print() {
        print(this->root);
        printf("\n");
    }

    void print(Tnode * visitor) {
        if (visitor != NULL) {
            visitor->print();
            printf(" -> ");
            print(visitor->left);
            print(visitor->right);
        } else {
            printf("nil | ");
        }
    }

    Tnode * root;
};


#endif // TREE_H
