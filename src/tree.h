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
    typedef Interval<T> Tinvertal;

    Tree() {
        this->root = NULL;
    }

    void print() {
        print(this->root);
        printf("\n");
    }

    Tnode ** search_interval(Tinterval value, Tnode * & parent = NULL) {
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

    void insert_interval(Tinvertal interval) {
        Tnode * parent = NULL;
        Tnode ** search_node = search_interval(interval, parent);
        if (parent != NULL) {
            parent->interval.distance(interval);
        }
        (*searchNode) = new Tnode(value);
        (*searchNode)->parent = parent;
        (*searchNode)->update_weights();
        // if ((*search_node) != NULL) {

        // }
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
