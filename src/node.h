#ifndef NODE_H
#define NODE_H


template <class T>
class Node {
public:
    Node() {
        left = NULL;
        right = NULL;
    }
    Node(T value) {
        this->value = value;
        left = NULL;
        right = NULL;
    }

    Node <T> * left;
    Node <T> * right;
    T value;
};


#endif // NODE_H