#ifndef NODE_H
#define NODE_H
#include "interval.h"

using namespace std;


template <class T>
class Node {
public:
    typedef Node<T> Tnode;
    typedef Interval<T> Tinterval;
    vector <Tnode* > leafs;
    vector <Tinterval *> queries;
    bool withLeafs;


    Node() {
        left = NULL;
        right = NULL;
        parent = NULL;
        withLeafs = true;

        if (withLeafs) {
            leafs.push_back(this);
        }
    }

    Node(Tinterval interval) : Node() {
        this->interval = interval;
    }

    Node(Tinterval interval, Tinterval * query) : Node(interval) {
        queries.push_back(query);
    }

    bool is_interval() {
        return (interval.left != interval.right);
    }

    void update_interval(T elem) {
        if (elem > interval.left) {
            interval.right = elem;
            top = elem;
        } else {
            interval.left = elem;
            top = interval.left;
        }
    }

    void splitLeft(Tinterval newIntervl) {

    }

    void split() {
        Tinterval left_interval, right_interval;
        interval.split(left_interval, right_interval);
        left = new Node(left_interval);
        right = new Node(right_interval);
        left->parent = this;
        right->parent = this;
    }

    void replace(Tinterval newInterval) {
        interval = newInterval;
        left = NULL;
        right = NULL;
    }

    bool is_leaf() {
        return ((left == NULL) && (right == NULL));
    }

    void updateWeights() {
        bool shouldUpdateLeafs = false;

        int leftNodes = this->left != NULL ? this->left->leafs.size() : 0;
        int rightNodes = this->right != NULL ? this->right->leafs.size() : 0;

        if ((leftNodes + rightNodes) != leafs.size() || leafs.size() == 0) {
            shouldUpdateLeafs = true;
        }
        if (withLeafs && shouldUpdateLeafs) {
            updateLeafs();
        }

        if (this->parent != NULL) {
            if (this->interval.left < parent->interval.left) {
                parent->interval.left = this->interval.left;
            }
            if (this->interval.right > parent->interval.right) {
                parent->interval.right = this->interval.right;
            }
            parent->updateWeights();
        }
    }

    void updateLeafs() {
        leafs.clear();
        if (left != NULL) {
            if (left->is_leaf()) {
                leafs.push_back(left);
            } else {
                leafs.insert(leafs.end(), left->leafs.begin(), left->leafs.end());
            }
        }
        if (right != NULL) {
            if (right->is_leaf()) {
                leafs.push_back(right);
            } else {
                leafs.insert(leafs.end(), right->leafs.begin(), right->leafs.end());
            }
        }
        if (right == NULL && left == NULL) {
            leafs.push_back(this);
        }
    }

    void printNodes() {
        cout << "interval" << interval << endl;
        cout << "this: " << this << endl;
        cout << "left: " << left << endl;
        cout << "right: " << right << endl;
        cout << "parent: " << parent << endl;
    }

    void print() {
        // printf("[%d, %d](%d)", interval.left, interval.right, top);
        std::cout << interval;
        // std::cout << interval;
    }

    Tnode * left;
    Tnode * right;
    Tnode * parent;
    Tinterval interval;
    T top;
};


#endif // NODE_H
