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
