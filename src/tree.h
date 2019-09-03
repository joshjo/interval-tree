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
    // queue <pair<Tinterval, Tnode* >> pending;
    queue <Tinterval> pending;

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

    // Tnode ** search_interval(Tinterval & interval, Tnode * & parent = NULL, Tnode ** from_node = NULL) {
    //     Tnode ** visitor = &(this->root);
    //     while ((*visitor) != NULL) {
    //         parent = *visitor;
    //         Tnode leftNode = parent->left;
    //         Tnode rightNode = parent->right;
    //         cout << " comparing " << (*visitor)->interval << " == ";
    //         if (interval.includes((*visitor)->interval)) {
    //             cout << " includes in search ";
    //             visitor = &((*visitor)->left);
    //             break;
    //         } else if (leftNode->interval.interects(interval)) {


    //         } else if () {
    //         }else if (interval <= (*visitor)->interval) {
    //             Tnode * sibling = parent->right;
    //             visitor = &((*visitor)->left);
    //             cout << " go left " << (*visitor)->interval;
    //             if (sibling != NULL && sibling->interval.intersects(interval)) {
    //                 Tinterval intervalLeft(interval.left, sibling->interval.left);
    //                 Tinterval intervalRight(sibling->interval.left, interval.right);
    //                 if (intervalLeft.distance() > 0) {
    //                     cout << " right intersection left: " << intervalLeft << " | right: " << intervalRight;
    //                     interval = intervalLeft;
    //                     pending.push(intervalRight);
    //                 }
    //             }
    //         } else if (interval >= (*visitor)->interval) {
    //             visitor = &((*visitor)->right);
    //             Tnode * sibling = parent->left;
    //             if (sibling != NULL && sibling->interval.intersects(interval)) {
    //                 Tinterval temp((*visitor)->interval.left, interval.left);
    //                 interval.left = (*visitor)->interval.left;
    //                 cout << " left intersection " << temp << " | " << interval;
    //                 if (interval.distance() > 0) {
    //                     pending.push(temp);
    //                 }
    //             }
    //         }
    //     }

    //     return visitor;
    // }

    // void insert_interval_intern(Tinterval interval) {
    //     cout << "Inserting: " << interval << " ";
    //     Tnode * parent = NULL;
    //     Tnode ** search_node = search_interval(interval, parent, &root);
    //     if (parent != NULL) {
    //         if (parent->is_leaf()) {
    //             cout << " Parent is a leaf " << parent->interval << " | ";
    //             if (parent->interval.intersects(interval)) {
    //                 cout << "Intersects " << interval << " | ";
    //                 parent->expand(interval);
    //                 if (parent->interval.distance() > threshold) {
    //                     cout << "Split | ";
    //                     parent->split();
    //                 }
    //             } else {
    //                 Tnode * left, * right;
    //                 cout << "No intersection | ";
    //                 if (debug) {
    //                     cout << endl;
    //                     print();
    //                     cout << endl;
    //                 }
    //                 if (interval <= parent->interval) {
    //                     left = new Tnode(interval);
    //                     right = new Tnode(parent->interval);
    //                 } else {
    //                     left = new Tnode(parent->interval);
    //                     right = new Tnode(interval);
    //                 }
    //                 if(debug) {
    //                     cout << "parent: " << parent << " left " << left << " right: " << right << " ";
    //                 }
    //                 parent->expand(interval);
    //                 parent->left = left;
    //                 parent->right = right;
    //                 left->parent = parent;
    //                 right->parent = parent;
    //             }
    //             parent->update_weights();
    //         } else {
    //             parent->expand(interval);
    //             parent->left = NULL;
    //             parent->right = NULL;
    //         }

    //     } else {

    //         (*search_node) = new Tnode(interval);
    //         (*search_node)->parent = parent;
    //         (*search_node)->update_weights();
    //     }
    //     // cout << "pending size " << pending.size();
    // }

    int decide(Tnode ** parent, Tnode ** node, Tnode ** sibling) {
        Tnode leftNode = (*visitor_node)->left;
        Tnode rightNode = (*visitor_node)->right;

        if (leftNode == NULL && rightNode == NULL) {

        }


        // if (leftNode == rightNode) {

        // }
    }

    void insert_interval_intern(Tinterval interval) {
        if (root == NULL ) {
            root = new Tnode(interval);
            return;
        }
        Tnode ** visitor_node = &root;
        while(visitor_node != NULL) {

            if (leftNode != NULL && interval.on_left_of(leftNode->interval)) {

            } else if (rightNode != NULL && interval.on_right_of(rightNode->interval)) {

            }
            // if (leftNode->interval)
            // if ((*visitor_node)->left !=)
        }

    }

    void insert_interval(Tinterval interval, bool dbg=false) {
        vector<Tinterval > arr;
        debug = dbg;
        interval.slice(threshold, arr);
        for (auto & it: arr) {
            insert_interval_intern(it);
        }
        cout << endl;
        while (!pending.empty()) {
            Tinterval tmp = pending.front();
            insert_interval_intern(tmp);
            pending.pop();
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
