#ifndef NODE_H
#define NODE_H
#include "interval.h"

using namespace std;


template <class T>
class NodeSimple {
public:
    typedef NodeSimple<T> Tnode;
    typedef Interval<T> Tinterval;
    typedef typename set <Tinterval *>::iterator it;

    NodeSimple() {
        left = NULL;
        right = NULL;
        parent = NULL;
    }

    NodeSimple(Tinterval interval) : NodeSimple() {
        this->interval = interval;
    }

    NodeSimple(Tinterval interval, Tinterval * query) : NodeSimple(interval) {
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

    void splitLeft(Tinterval newInterval, Tinterval * query) {
        Tnode * leftNode = new Tnode(newInterval, query);
        Tnode * rightNode = new Tnode(interval, query);
        interval.expand(newInterval);
        leftNode->parent = this;
        rightNode->parent = this;

        left = leftNode;
        right = rightNode;
        updateWeights();
    }

    void splitRight(Tinterval newInterval, Tinterval * query) {
        Tnode * leftNode = new Tnode(interval, query);
        Tnode * rightNode = new Tnode(newInterval, query);
        interval.expand(newInterval);
        leftNode->parent = this;
        rightNode->parent = this;

        left = leftNode;
        right = rightNode;
        updateWeights();
    }

    void replaceDestroy(Tinterval newInterval, Tinterval * query, double & a) {
        interval = newInterval;
        updateWeights();
        left = NULL;
        right = NULL;
    }

    void expandDestroy(Tinterval newInterval, Tinterval * query) {
        interval.expand(newInterval);
        left = NULL;
        right = NULL;
        updateWeights();
    }

    void split(Tinterval * query) {
        // Here problably we will need to store the queries from left or right
        Tinterval left_interval, right_interval;
        interval.split(left_interval, right_interval);
        left = new Tnode(left_interval, query);
        right = new Tnode(right_interval, query);
        left->parent = this;
        right->parent = this;
        updateWeights();
    }

    bool is_leaf() {
        return ((left == NULL) && (right == NULL));
    }

    void updateWeights() {
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


template <class T>
class NodeLeafs : public NodeSimple <T> {
public:
    typedef Interval<T> Tinterval;
    typedef NodeLeafs<T> Tnode;

    // using NodeSimple;

    NodeLeafs() : NodeSimple<T> () {
    }
    NodeLeafs(Tinterval interval) : NodeSimple<T> (interval) {}
    NodeLeafs(Tinterval interval, Tinterval * query) : NodeSimple<T> (interval, query) {}

};


#endif // NODE_H
