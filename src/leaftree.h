#ifndef LEAFT_TREE_H
#define LEAFT_TREE_H
#include "interval.h"

#include "includes.h"


template <class T>
class LeafNode {

public:
    typedef Interval<T> Tinterval;
    typedef LeafNode<T> Tnode;
    Tnode * left;
    Tnode * right;
    Tnode * parent;
    T max;

    Tinterval interval;
    string * hashmap;

    LeafNode(Tinterval interval) {
        this->interval = interval;
        T size = interval.right - interval.left;
        hashmap = new string[size];
        for (T i = 0; i < size; i++) {
            hashmap[i] = to_string((i + interval.left) * 2);
        }
    }

    void update_weights() {
        if (this->parent != NULL && this->max > parent->max) {
            parent->max = this->max;
            parent->update_weights();
        }
    }


    void print() {
        printf("[%d, %d](%d)", interval.left, interval.right, max);
    }
};


template <class T>
class LeafTree {

public:
    typedef LeafNode<T> Tnode;
    typedef Interval<T> Tinterval;
    Tnode * root;

    LeafTree() {
        root = NULL;
    }

    T find (Tinterval interval, string * & result) {
        T size = interval.right - interval.left;
        result = new string[interval.right - interval.left];
        Tnode ** visitor = &(this->root);
        int index = 0;
        while ((*visitor) != NULL) {
            if ((*visitor)->interval.left > interval.right) {
                visitor = &((*visitor)->left);
            } else if ((*visitor)->interval.right <= interval.left) {
                visitor = &((*visitor)->right);
            } else {
                if ((*visitor)->interval.right < interval.right) {
                    for (T i = interval.left; i < (*visitor)->interval.right; i++) {
                        result[index + i - interval.left] = (*visitor)->hashmap[i - (*visitor)->interval.left];
                    }
                    index += (*visitor)->interval.right - interval.left;
                    interval = Tinterval((*visitor)->interval.right, interval.right);
                    visitor = &(this->root);
                } else {
                    for (T i = interval.left; i < interval.right; i++) {
                        result[index + i - interval.left] = (*visitor)->hashmap[i - (*visitor)->interval.left];
                    }
                    break;
                }
            }
        }
        return size;
    }

    Tnode ** search(Tinterval interval, Tnode * & parent = NULL) {
        Tnode ** visitor = &(this->root);
        while ((*visitor) != NULL) {
            parent = *visitor;
            if (interval == (*visitor)->interval) {
                break;
            } else if (interval < (*visitor)->interval) {
                visitor = &((*visitor)->left);
            } else {
                visitor = &((*visitor)->right);
            }
        }

        return visitor;
    }

    bool insert(Tinterval value) {
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

};

#endif // LEAFT_TREE_H
