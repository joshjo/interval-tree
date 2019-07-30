#ifndef NODE_H
#define NODE_H
#include <iostream>
#include <utility>

using namespace std;


template <class T>
class Node {
public:
    Node() {
        left = NULL;
        right = NULL;
        value = {0, 0};
    }

    Node(pair<T, T> value) {
        this->value = value;
        left = NULL;
        right = NULL;
    }

    void print() {
        printf("[%d, %d]", value.first, value.second);
    }

    Node <T> * left;
    Node <T> * right;
    pair<T, T> value;
    T max;
};


#endif // NODE_H