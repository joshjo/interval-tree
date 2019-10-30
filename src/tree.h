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
    Tnode * root;
    T threshold;
    int extra_operations;
    int extra_insertions;
    int middle;

    bool debug;
    // queue <pair<Tinterval, Tnode* >> pending;
    queue <Tinterval> pending;
    queue <pair<Tinterval, Tinterval> > npending;
    int number_pending;

    Tree(int threshold=100) {
        this->root = NULL;
        this->threshold = threshold;
        // debug = true;
        debug = false;
        number_pending = 0;
        extra_operations = 0;
        extra_insertions = 0;
        middle = 0;
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

    void insert_interval_intern(Tinterval interval, Tinterval * query, bool count = false, int iteration = 0) {
        if (count) {
            extra_operations += 1;
        }
        if (debug) {
            cout << "inserting: " << interval << endl;
        }

        if (root == NULL ) {
            root = new Tnode(interval, query);
            root->leafs.push_back(root);
            if (count) {
                extra_insertions += 1;
            }
            return;
        }

        Tnode ** visitor = &root;
        Tnode * parent = NULL;
        while((*visitor) != NULL) {
            if (interval.includes((*visitor)->interval)) {
                Tinterval tmp = (*visitor)->interval;
                tmp.expand(interval);
                if (debug) {
                    cout << "******* " << interval << " includes " << (*visitor)->interval << endl;
                    cout << "expand? " << (tmp.distance() < threshold) << endl;
                }
                if (tmp.distance() <= threshold) {
                    // (*visitor)->interval = tmp;
                    // (*visitor)->left = NULL;
                    // (*visitor)->right = NULL;

                    (*visitor)->expand(tmp, query);
                    // (*visitor)->update_weights();
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
                            // pending.push(slice);
                            npending.push(make_pair(slice, interval));
                        }
                        interval.right = sibling->interval.left;
                    }
                }
                if (((*visitor)->left) == NULL) {
                    Tinterval tmp = (*visitor)->interval;
                    tmp.expand(interval);
                    if (tmp.distance() <= threshold && (*visitor)->interval.intersects(interval)) {
                        if (debug) cout << "update nodes" << endl;
                        (*visitor)->expand(tmp, query);
                        // (*visitor)->interval = tmp;
                        // (*visitor)->left = NULL;
                        // (*visitor)->right = NULL;
                        // (*visitor)->update_weights();
                    } else {
                        Tnode * parent = (*visitor);
                        if (debug) {
                            cout << "intersects? " << (*visitor)->interval.intersects(interval) << endl;
                            cout << "parent: " << parent->interval << endl;
                        }
                        if ((*visitor)->interval.intersects(interval)) {
                            // parent->interval.expand(interval);
                            parent->split_half(interval, query);
                            // parent->update_weights();
                        } else {
                            if (count) {
                                extra_insertions += 2;
                            }
                            (*visitor)->split_left(interval, query);
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
                            npending.push(make_pair(slice, interval));
                        }
                        interval.left = sibling->interval.right;
                    }
                }
                if (((*visitor)->right) == NULL) {
                    Tinterval tmp = (*visitor)->interval;
                    tmp.expand(interval);
                    if (tmp.distance() <= threshold && (*visitor)->interval.intersects(interval)) {
                        (*visitor)->expand(tmp, query);
                        // (*visitor)->interval = tmp;
                        // (*visitor)->left = NULL;
                        // (*visitor)->right = NULL;
                        // (*visitor)->update_weights();
                    } else {
                        Tnode * parent = (*visitor);
                        if ((*visitor)->interval.intersects(interval)) {
                            // parent->interval.expand(interval);
                            (*visitor)->split_half(interval, query);
                            // parent->update_weights();
                        } else {
                            if (debug) {
                                cout << "new node at left" << endl;
                            }
                            if (count) {
                                extra_insertions += 2;
                            }
                            (*visitor)->split_right(interval, query);
                        }
                    }
                    break;
                }
                visitor = &(*visitor)->right;
            }
            if (direction == MIDDLE) {
                middle += 1;
                // cout << "here: " << interval << endl;
                (*visitor)->interval.expand(interval);
                (*visitor)->left = NULL;
                (*visitor)->right = NULL;
                (*visitor)->update_weights();
                break;
            }
        }
    }

    int insert_interval(Tinterval & interval, bool dbg=false, int iteration = 0) {
        vector<Tinterval > arr;
        debug = dbg;
        interval.slice(threshold, arr);

        for (auto & it: arr) {
            insert_interval_intern(it, &interval, true, iteration);
        }
        number_pending += npending.size();
        while (!npending.empty()) {
            pair<Tinterval, Tinterval> tmp = npending.front();
            insert_interval_intern(tmp.first, &interval, true);
            npending.pop();
        }
        return 0;
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


    string graphviz(string iter=""){
        // string str = "digraph G {\n";
        string tree = "";
        graphviz(root, tree, iter);
        // str += tree + "}";
        return tree;
    }
};


#endif // TREE_H
