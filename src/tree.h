#ifndef TREE_H
#define TREE_H
#include <iostream>
#include <utility>
#include <limits>

#include "node.h"

using namespace std;


template <class Tr>
class Tree {
public:
    typedef typename Tr::T T;
    typedef Node<Tr> Tnode;
    typedef Interval<T> Tinterval;
    Tnode * root;
    T threshold;
    int extra_operations;
    int extra_insertions;
    double counter;
    int insertions = 0;
    double update_time;

    bool debug;
    queue <pair<Tinterval, Tinterval *> > npending;
    int number_pending;

    Tree(int threshold=100) {
        this->root = NULL;
        this->threshold = threshold;
        debug = true;
        number_pending = 0;
        extra_operations = 0;
        extra_insertions = 0;
        counter = 0;
        insertions = 0;
        update_time = 0;
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

    void insert_interval_intern(Tinterval interval, Tinterval * query, bool count = false) {
        insertions += 1;

        if (root == NULL) {
            root = new Tnode(interval, query);
            return;
        }

        Tnode ** visitor = &root;
        Tnode * parent = NULL;
        while((*visitor) != NULL) {
            if (interval.includes((*visitor)->interval)) {
                Tinterval tmp = (*visitor)->interval;
                tmp.expand(interval);
                if (tmp.distance() < threshold) {
                    update_time += (*visitor)->replaceDestroy(tmp, query, counter);
                    break;
                }
            }
            int direction = decide(interval, visitor);
            if (direction == LEFT || direction == LEFT_PARENT) {
                Tnode * sibling = ((*visitor)->right);
                if (LEFT_PARENT && sibling != NULL) {
                    if (sibling->interval.intersects(interval)) {
                        Tinterval slice(sibling->interval.left, interval.right);
                        if (slice.distance() > 0) {
                            npending.push(make_pair(slice, query));
                        }
                        interval.right = sibling->interval.left;
                    }
                }
                if (((*visitor)->left) == NULL) {
                    Tinterval tmp = (*visitor)->interval;
                    tmp.expand(interval);
                    if (tmp.distance() <= threshold && (*visitor)->interval.intersects(interval)) {
                        update_time += (*visitor)->replaceDestroy(tmp, query, counter);
                    } else {
                        if ((*visitor)->interval.intersects(interval)) {
                            (*visitor)->interval.expand(interval);
                            update_time += (*visitor)->split(query);
                        } else {
                            update_time += (*visitor)->splitLeft(interval, query);
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
                            npending.push(make_pair(slice, query));
                        }
                        interval.left = sibling->interval.right;
                    }
                }
                if (((*visitor)->right) == NULL) {
                    Tinterval tmp = (*visitor)->interval;
                    tmp.expand(interval);
                    if (tmp.distance() <= threshold && (*visitor)->interval.intersects(interval)) {
                        update_time += (*visitor)->replaceDestroy(tmp, query, counter);
                    } else {
                        if ((*visitor)->interval.intersects(interval)) {
                            (*visitor)->interval.expand(interval);
                            update_time += (*visitor)->split(query);
                        } else {
                            update_time += (*visitor)->splitRight(interval, query);
                        }
                    }
                    break;
                }
                visitor = &(*visitor)->right;
            }
            if (direction == MIDDLE) {
                update_time += (*visitor)->expandDestroy(interval, query);
                break;
            }
        }
    }

    int insert_interval(Tinterval & interval, bool dbg=false) {
        vector<Tinterval > arr;
        debug = dbg;
        interval.slice(threshold, arr);

        for (auto & it: arr) {
            insert_interval_intern(it, &interval);
        }
        number_pending += npending.size();
        while (!npending.empty()) {
            pair<Tinterval, Tinterval *> tmp = npending.front();
            insert_interval_intern(tmp.first, tmp.second, true);
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

    void getLeafs(vector<Tinterval *> & leafs) {
        getLeafs(root, leafs);
    }

    void getLeafs(Tnode * visitor, vector<Tinterval *> & leafs) {
        if(visitor != NULL) {
            if (visitor->left == NULL && visitor->right == NULL) {
                // cout << visitor->interval << " | ";
                leafs.push_back(&(visitor->interval));
            }
            getLeafs(visitor->left, leafs);
            getLeafs(visitor->right, leafs);
        }
    }

    T * getLeafsData() {
        vector<Tinterval *> leafs;
        T inf = numeric_limits<T>::max();
        getLeafs(leafs);
        size_t size = leafs.size();
        T res[4] = {size, 0, inf, -inf};


        for (int i = 0; i < size; i += 1) {
            T width = leafs[i]->right - leafs[i]->left;
            res[1] += width;
            if (width < res[2]) {
                res[2] = width;
            }
            if (width > res[3]) {
                res[3] = width;
            }
        }

        res[1] = res[1] / size;

        return res;
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
