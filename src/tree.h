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

    Tnode ** search_interval(Tinterval & interval, Tnode * & parent = NULL) {
        Tnode ** visitor = &(this->root);
        while ((*visitor) != NULL) {
            parent = *visitor;
            if (interval == (*visitor)->interval) {
            } else if (interval.includes((*visitor)->interval)) {
                cout << "%";

                // Here is missing to delete nodes
                break;
            } else if (interval <= (*visitor)->interval) {
                Tnode * right = ((*visitor)->right);
                cout << "<";
                if (right != NULL) {
                    cout << "+";
                    interval.slice_right(right->interval);
                }
                visitor = &((*visitor)->left);

            } else {
                cout << ">";
                Tnode * left = ((*visitor)->left);
                if (left != NULL) {
                    cout << "*";
                    interval.slice_left(left->interval);
                }
                visitor = &((*visitor)->right);
            }
        }

        cout << " ";

        return visitor;
    }

    void insert_interval_intern(Tinterval & interval) {
        cout << "Inserting: " << interval << " ";
        Tnode * parent = NULL;
        Tnode ** search_node = search_interval(interval, parent);
        if (parent != NULL && parent->is_leaf()) {
            cout << "Parent is a leaf | ";
            if (parent->interval.intersects(interval)) {
                cout << "Intersects | ";
                parent->expand(interval);
                if (parent->interval.distance() > threshold) {
                    cout << "Split | ";
                    parent->split();
                }
            } else {
                Tnode * left, * right;
                cout << "No intersection | ";
                if (parent->interval >= interval) {
                    left = new Tnode(interval);
                    right = new Tnode(parent->interval);
                } else {
                    left = new Tnode(parent->interval);
                    right = new Tnode(interval);
                }
                parent->expand(interval);
                parent->left = left;
                parent->right = right;
                left->parent = parent;
                right->parent = parent;
            }
            parent->update_weights();
            cout << endl;
            return;
        }
        cout << endl;
        (*search_node) = new Tnode(interval);
        (*search_node)->parent = parent;
        (*search_node)->update_weights();
    }

    void insert_interval(Tinterval interval) {
        vector<Tinterval > arr;
        interval.splice(threshold, arr);
        for (auto & it: arr) {
            insert_interval_intern(it);
        }
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
