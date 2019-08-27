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
    bool debug;

    Tree() {
        this->root = NULL;
        threshold = 100;
        debug = false;
    }

    void print() {
        cout << "Root: ";
        root->print();
        cout << endl;
        print(this->root);
        printf("\n");
    }

    Tnode ** search_interval(Tinterval interval, Tnode * & parent = NULL, Tnode ** from_node = NULL) {
        Tnode ** visitor = &(this->root);
        while ((*visitor) != NULL) {
            parent = *visitor;
            if (interval == (*visitor)->interval) {
                break;
            } else if (interval <= (*visitor)->interval) {
                visitor = &((*visitor)->left);
                cout << "<";
            } else {
                visitor = &((*visitor)->right);
                cout << ">";
            }
        }

        return visitor;
    }

    void insert_interval_intern(Tinterval interval) {
        cout << "Inserting: " << interval << " ";
        Tnode * parent = NULL;
        Tnode ** search_node = search_interval(interval, parent, &root);
        cout << "*search_node " << (*search_node) << " ";
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
                if (debug) {
                    cout << endl;
                    print();
                    cout << endl;
                }
                if (interval <= parent->interval) {
                    left = new Tnode(interval);
                    right = new Tnode(parent->interval);
                } else {
                    left = new Tnode(parent->interval);
                    right = new Tnode(interval);
                }
                if(debug) {
                    cout << "parent: " << parent << " left " << left << " right: " << right << " ";
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
        cout << "***" << endl;

        (*search_node) = new Tnode(interval);
        (*search_node)->parent = parent;
        (*search_node)->update_weights();
    }

    void insert_interval(Tinterval interval, bool dbg=false) {
        vector<Tinterval > arr;
        debug = dbg;
        interval.slice(threshold, arr);
        for (auto & it: arr) {
            insert_interval_intern(it);
        }
    }

    void print(Tnode * visitor) {
        if (visitor != NULL) {
            visitor->print();
            // cout << "[";
            // if (visitor->parent != NULL) {
            //     visitor->parent->print();
            // }
            // if (visitor->left != NULL) {
            //     cout << "left: ";
            //     visitor->left->print();
            //     cout << " |";
            // }
            // if (visitor->right != NULL) {
            //     cout << "right: ";
            //     visitor->right->print();
            //     cout << " |";
            // }
            // cout << "] " << endl;
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
