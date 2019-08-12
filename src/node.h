#ifndef NODE_H
#define NODE_H
#include <iostream>
#include <utility>

using namespace std;


template <class T>
class Node {
public:
    typedef Node<T> Tnode;
    typedef pair<T, T> Interval;

    Node() {
        left = NULL;
        right = NULL;
    }

    Node(Interval value) {
        this->value = value;
        max = value.second;
        left = NULL;
        right = NULL;
    }

    bool is_interval() {
        return (value.first != value.second);
    }

    void update_interval(T elem) {
        if (elem > value.first) {
            value.second = elem;
            max = elem;
        } else {
            value.first = elem;
            max = value.first;
        }
    }

    void update_weights() {
        if (this->parent != NULL && this->max > parent->max) {
            parent->max = this->max;
            parent->update_weights();
        }
    }

    void print() {
        printf("[%d, %d](%d)", value.first, value.second, max);
    }

    Tnode * left;
    Tnode * right;
    Tnode * parent;
    Interval value;
    T max;
};


#endif // NODE_H
