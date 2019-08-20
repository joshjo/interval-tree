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
    typedef Interval<T> Tinterval;

    Tree() {
        this->root = NULL;
        threshold = 100;
    }

    void print() {
        print(this->root);
        printf("\n");
    }

    Tnode ** search_interval(Tinterval interval, Tnode * & parent = NULL, Tnode ** from_node = NULL) {
        Tnode ** visitor = &(this->root);
        // if (from_node != NULL) {
        //     visitor = from_node;
        // }
        while ((*visitor) != NULL) {
            parent = *visitor;
            if (interval == (*visitor)->interval) {
                break;
            } else if (interval <= (*visitor)->interval) {
                visitor = &((*visitor)->left);
            } else {
                visitor = &((*visitor)->right);
            }
        }

        return visitor;
    }

    void insert_interval(Tinterval interval) {
        cout << "Inserting: " << interval << " ";
        Tnode * parent = NULL;
        Tnode ** search_node = search_interval(interval, parent, &root);
        if (parent != NULL) {
            T distance = parent->interval.distance(interval);
            if (distance <= threshold) {
                parent->expand(interval);
                cout << "Expanding ";
                cout << endl;
                return;
            }
            if (parent->interval.intersects(interval)) {
                parent->expand(interval);
                cout << "Expanding ";
                if (parent->interval.distance() > threshold) {
                    cout << "Split ";
                }
            }
            // if (parent->interval <= interval && parent->interval < interval)
        }
        cout << endl;
        (*search_node) = new Tnode(interval);
        (*search_node)->parent = parent;
        // (*search_node)->update_weights();
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
    T threshold;
};


#endif // TREE_H
