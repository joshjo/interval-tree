#include "src/includes.h"

using namespace std;


template <class T>
class NodeBase {
public:
    T value;

    NodeBase(T val): value(val) {

    }

    void foo () {
        cout << "Hello NodeBase" << endl;
    }
};

template <class T>
class NodeLeafs: public NodeBase <T> {

public:
    NodeLeafs(T val): NodeBase<T>(val) {

    }

    void foo() {
        cout << "Hello NodeLeafs" << endl;
        NodeBase<T>::foo();
    }
};


template <class Tr>
class Tree {
public:
    typedef typename Tr::T T;
    typedef typename Tr::Node Node;
    Node * root;
    T value;

    Tree(T val) {
        value = val;
        root = new Node(val);
    }

    void foo() {
        root->foo();
    }
};


class TraitsBase {
    public:
        typedef long T;
        typedef NodeBase<T> Node;
};


class TraitsLeafs {
    public:
        typedef long T;
        typedef NodeLeafs<T> Node;

    void loop() {

    }
};


int main(int argc, char** argv) {
    Tree<TraitsLeafs> tree(3);
    tree.foo();
    // tree = tree2;
    // cout << tree->value << endl;
    return 0;
}

