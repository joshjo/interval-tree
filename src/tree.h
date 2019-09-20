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

    Tree(int threshold=100) {
        this->root = NULL;
        this->threshold = threshold;
        // debug = true;
        debug = false;
    }

    void print() {
        cout << "Root: ";
        root->print();
        cout << endl;
        print(this->root);
        printf("\n");
    }

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
            return LEFT;
        }
        if (rightNode != NULL && interval.left >= rightNode->interval.left) {
            return RIGHT;
        }

        if (middle < parentMiddle) {
            return LEFT_PARENT;
        } else {
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
            if (interval.includes((*visitor)->interval)) {
                if (debug ){
                    cout << "includes" << endl;
                }
                Tinterval tmp = (*visitor)->interval;
                if (tmp.distance() < threshold) {
                    tmp.expand(interval);
                    (*visitor)->left = NULL;
                    (*visitor)->right = NULL;
                    break;
                }
            }

            int direction = decide(interval, visitor);
            if (debug) {
                cout << "direction " << direction << " Interval " << interval << endl;
                cout << "left  ifs: " << (direction == LEFT || direction == LEFT_PARENT) << endl;
                cout << "right ifs: " << (direction == RIGHT || direction == RIGHT_PARENT) << endl;
            }
            if (direction == LEFT || direction == LEFT_PARENT) {
                Tnode * sibling = ((*visitor)->right);
                if(debug) {
                    cout << "visitor: " << (*visitor)->interval << endl;
                    cout << "sibling " << sibling << endl;
                }
                if (LEFT_PARENT && sibling != NULL) {
                    if (sibling->interval.intersects(interval)) {
                        Tinterval slice(sibling->interval.left, interval.right);
                        if (slice.distance() > 0) {
                            pending.push(slice);
                        }
                        interval.right = sibling->interval.left;
                    }
                }
                if (((*visitor)->left) == NULL) {
                    Tinterval tmp = (*visitor)->interval;
                    tmp.expand(interval);
                    if (tmp.distance() <= threshold && (*visitor)->interval.intersects(interval)) {
                        if (debug) cout << "update nodes" << endl;
                        (*visitor)->interval = tmp;
                        (*visitor)->update_weights();
                        (*visitor)->left = NULL;
                        (*visitor)->right = NULL;
                    } else {
                        Tnode * parent = (*visitor);
                        if (debug) {
                            cout << "intersects? " << (*visitor)->interval.intersects(interval) << endl;
                            cout << "parent: " << parent->interval << endl;
                        }
                        if ((*visitor)->interval.intersects(interval)) {
                            parent->interval.expand(interval);
                            parent->split();
                            parent->update_weights();
                        } else {
                            Tnode * leftNode = new Tnode(interval);
                            Tnode * rightNode = new Tnode(parent->interval);
                            parent->interval.expand(interval);
                            leftNode->parent = parent;
                            rightNode->parent = parent;
                            (*visitor)->left = leftNode;
                            (*visitor)->right = rightNode;
                            parent->update_weights();
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
                        if (slice.distance() > 0) {
                            pending.push(slice);
                        }
                        interval.left = sibling->interval.right;
                    }
                }
                if (((*visitor)->right) == NULL) {
                    Tinterval tmp = (*visitor)->interval;
                    tmp.expand(interval);
                    if (tmp.distance() <= threshold && (*visitor)->interval.intersects(interval)) {
                        (*visitor)->interval = tmp;
                        (*visitor)->left = NULL;
                        (*visitor)->right = NULL;
                        (*visitor)->update_weights();
                    } else {
                        Tnode * parent = (*visitor);
                        if ((*visitor)->interval.intersects(interval)) {
                            parent->interval.expand(interval);
                            parent->split();
                            parent->update_weights();
                        } else {
                            if (debug) {
                                cout << "new node at left" << endl;
                            }
                            Tnode * leftNode = new Tnode(parent->interval);
                            Tnode * rightNode = new Tnode(interval);
                            parent->interval.expand(interval);
                            leftNode->parent = parent;
                            rightNode->parent = parent;
                            (*visitor)->left = leftNode;
                            (*visitor)->right = rightNode;
                            parent->update_weights();
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
                break;
            }
        }
    }

    void insert_interval(Tinterval interval, bool dbg=false) {
        vector<Tinterval > arr;
        debug = dbg;
        interval.slice(threshold, arr);

        for (auto & it: arr) {
            insert_interval_intern(it);
        }
        while (!pending.empty()) {
            Tinterval tmp = pending.front();
            insert_interval_intern(tmp);
            pending.pop();
        }
    }

    int numberLeafs() {
        int counter = 0;
        numberLeafs(root, counter);
        return counter;
    }

    int numberLeafs(Tnode * visitor, int & counter) {
        if (visitor != NULL) {
            if (visitor->left == NULL && visitor->right == NULL) {
                counter += 1;
            }
            numberLeafs(visitor->left, counter);
            numberLeafs(visitor->right, counter);
        }
        return 0;
    }

    void getLeafs(vector<Tinterval> & leafs) {
        getLeafs(root, leafs);
    }

    void getLeafs(Tnode * visitor, vector<Tinterval> & leafs) {
        if(visitor != NULL) {
            if (visitor->left == NULL && visitor->right == NULL) {
                // cout << visitor->interval << " | ";
                leafs.push_back(visitor->interval);
            }
            getLeafs(visitor->left, leafs);
            getLeafs(visitor->right, leafs);
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

    void graphviz(Tnode *node, string & tree, string iter="") {
        if (node != NULL) {
            if (node->parent == NULL && node->left == NULL && node->right == NULL) {
                tree += node->interval.to_graphviz(iter);
            }
            if (node->left != NULL) {
                tree += node->interval.to_graphviz(iter) + " -> " + node->left->interval.to_graphviz(iter) + " ";
            }
            if (node->right != NULL) {
                tree += node->interval.to_graphviz(iter) + " -> " + node->right->interval.to_graphviz(iter) + " ";
            }
            if (node->left == NULL && node->right == NULL) {
                tree += node->interval.to_graphviz(iter) + " [shape=box color=blue fillcolor=blue fontcolor=white style=filled]";
            }
            graphviz(node->left, tree, iter);
            graphviz(node->right, tree, iter);
        }
    }


    string graphviz(string iter="1"){
        // string str = "digraph G {\n";
        string tree = "";
        graphviz(root, tree, iter);
        // str += tree + "}";
        return tree;
    }

    Tnode * root;
    T threshold;
};


#endif // TREE_H
