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

    int decide(Tinterval & interval ,Tnode ** parent) {
        Tnode * leftNode = (*parent)->left;
        Tnode * rightNode = (*parent)->right;
        Tinterval parentInterval = (*parent)->interval;
        T parentMiddle = (*parent)->interval.middle();
        T middle = interval.middle();

        if (interval.includes(parentInterval)) {
            return MIDDLE;
        }
        if (leftNode != NULL && interval.right <= leftNode->interval.right) {
            // node = &leftNode;
            // sibling = &rightNode;
            return LEFT;
        }
        if (rightNode != NULL && interval.left >= rightNode->interval.left) {
            // node = &rightNode;
            // sibling = &leftNode;
            return RIGHT;
        }

        if (middle < parentMiddle) {
            // node = &leftNode;
            // sibling = &rightNode;
            return LEFT_PARENT;
        } else {
            // node = &rightNode;
            // sibling = &rightNode;
            return RIGHT_PARENT;
        }
    }

    void insert_interval_intern(Tinterval interval) {
        if (root == NULL ) {
            root = new Tnode(interval);
            return;
        }
        Tnode ** visitor = &root;
        Tnode * parent = NULL;
        while((*visitor) != NULL) {
            Tinterval tmp = (*visitor)->interval;
            if ((*visitor)->interval.includes(interval)) {
                if (tmp.distance() < threshold) {
                    tmp.expand(interval);
                    (*visitor)->left = NULL;
                    (*visitor)->right = NULL;
                    break;
                }
            }

            int direction = decide(interval, visitor);
            if (direction == LEFT || direction == LEFT_PARENT) {
                Tnode * sibling = ((*visitor)->right);
                if (LEFT_PARENT && sibling != NULL) {
                    if (sibling->interval.intersects(interval)) {
                        Tinterval slice(sibling->interval.left, interval.right);
                        pending.push(slice);
                        interval.right = sibling->interval.left;
                    }
                }
                if (((*visitor)->left) == NULL) {
                    Tinterval tmp = (*visitor)->interval;
                    tmp.expand(interval);
                    if (tmp.distance() <= threshold) {
                        // cout << "LEFT NULL" << interval << endl;
                        (*visitor)->interval = tmp;
                        (*visitor)->update_weights();
                        (*visitor)->left = NULL;
                        (*visitor)->right = NULL;
                    } else {
                        // cout << "LEFT UPDATE" << interval << endl;
                        Tnode * parent = (*visitor);
                        if ((*visitor)->interval.intersects(interval)) {
                            parent->expand(interval);
                            parent->update_weights();
                            parent->split();
                        } else {
                            Tnode * leftNode = new Tnode(interval);
                            Tnode * rightNode = new Tnode(parent->interval);
                            leftNode->parent = parent;
                            rightNode->parent = parent;
                            parent->expand(interval);
                            (*visitor)->left = leftNode;
                            (*visitor)->right = rightNode;
                        }
                    }
                    break;
                }
                visitor = &(*visitor)->left;
            }
            if (direction == RIGHT || direction == RIGHT_PARENT) {
                Tnode * sibling = ((*visitor)->left);
                if (RIGHT_PARENT && sibling != NULL) {
                    if (sibling->interval.intersects(interval)) {
                        Tinterval slice(interval.left, sibling->interval.right);
                        pending.push(slice);
                        interval.left = sibling->interval.right;
                    }
                }
                if (((*visitor)->right) == NULL) {
                    Tinterval tmp = (*visitor)->interval;
                    tmp.expand(interval);
                    if (tmp.distance() <= threshold) {
                        (*visitor)->interval = tmp;
                        (*visitor)->update_weights();
                        (*visitor)->left = NULL;
                        (*visitor)->right = NULL;
                    } else {
                        // cout << "RIGHT UPDATE" << interval << endl;
                        Tnode * parent = (*visitor);
                        if ((*visitor)->interval.intersects(interval)) {
                            parent->expand(interval);
                            parent->update_weights();
                            parent->split();
                        } else {
                            Tnode * leftNode = new Tnode(parent->interval);
                            Tnode * rightNode = new Tnode(interval);
                            parent->expand(interval);
                            leftNode->parent = parent;
                            rightNode->parent = parent;
                            (*visitor)->left = leftNode;
                            (*visitor)->right = rightNode;
                        }
                    }
                    break;
                }
                visitor = &(*visitor)->right;
            }
            if (direction == MIDDLE) {
                (*visitor)->interval.expand(interval);
                (*visitor)->left = NULL;
                (*visitor)->right = NULL;
                // parent = NULL;
                // cout << "here" << interval << endl;
                break;
            }
        }
    }

    void insert_interval(Tinterval interval, bool dbg=false) {
        vector<Tinterval > arr;
        debug = dbg;
        interval.slice(threshold, arr);
        for (auto & it: arr) {
            // cout << " it: " << it << endl;
            insert_interval_intern(it);
        }
        while (!pending.empty()) {
            Tinterval tmp = pending.front();
            insert_interval_intern(tmp);
            pending.pop();
        }
    }

    void getLeafs() {
        getLeafs(root);
    }

    void getLeafs(Tnode * visitor) {
        if(visitor != NULL) {
            if (visitor->left == NULL && visitor->right == NULL) {
                cout << visitor->interval << " | ";
            }
            getLeafs(visitor->left);
            getLeafs(visitor->right);
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
