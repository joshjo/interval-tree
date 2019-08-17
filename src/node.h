#ifndef NODE_H
#define NODE_H
#include "interval.h"

using namespace std;


template <class T>
class Node {
public:
    typedef Node<T> Tnode;
    typedef Interval<T> Tinterval;

    Node() {
        left = NULL;
        right = NULL;
    }

    Node(Tinterval interval) {
        this->interval = interval;
        top = interval.right;
        left = NULL;
        right = NULL;
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

    void update_weights() {
        if (this->parent != NULL && this->top > parent->top) {
            parent->top = this->top;
            parent->update_weights();
        }
    }

    void expand(Tinterval & other_interval) {
        this->interval.expand(other_interval);
        this->top = this->interval.right;
    }

    void print() {
        // printf("[%d, %d](%d)", interval.left, interval.right, top);
        std::cout << interval << '[' << top << ']';
    }

    Tnode * left;
    Tnode * right;
    Tnode * parent;
    Tinterval interval;
    T top;
};


#endif // NODE_H
