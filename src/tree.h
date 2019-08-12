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

    bool insert_interval(Interval value) {
        Tnode * parent = NULL;
        Tnode ** searchNode = this->search(value, parent);
        if ((*searchNode) != NULL) {
            return false;
        }
        (*searchNode) = new Tnode(value);
        (*searchNode)->parent = parent;
        (*searchNode)->update_weights();

        return true;
    }

    bool insert_element(T elem) {
        Interval interval = make_pair(elem, elem);
        Tnode * parent = NULL;
        Tnode ** searchNode = this->search(interval, parent);
        if ((*searchNode) == NULL) {
            if (parent != NULL && ( ! parent->is_interval())) {
                parent->update_interval(elem);
                parent->update_weights();
            } else {
                (*searchNode) = new Tnode(interval);
                (*searchNode)->parent = parent;
                (*searchNode)->update_weights();
            }
        }

        return true;
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
