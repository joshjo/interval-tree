#ifndef NODE_H
#define NODE_H
#include "interval.h"

using namespace std;


template <class T>
class Node {
public:
    typedef Node<T> Tnode;
    typedef Interval<T> Tinterval;
    typedef typename set <Tinterval *>::iterator it;
    vector <Tnode* > leafs;
    set <Tinterval *> queries;
    bool withLeafs;
    bool withQueries;

    Node() {
        left = NULL;
        right = NULL;
        parent = NULL;
        withLeafs = true;
        withQueries = withLeafs && true;

        if (withLeafs) {
            leafs.push_back(this);
        }
    }

    Node(Tinterval interval) : Node() {
        this->interval = interval;
    }

    Node(Tinterval interval, Tinterval * query) : Node(interval) {
        if (withQueries) {
            queries.insert(query);
        }
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

        if (withQueries) {
            leftNode->queries.insert(queries.begin(), queries.end());
            rightNode->queries.insert(queries.begin(), queries.end());
        }

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

        if (withQueries) {
            leftNode->queries.insert(queries.begin(), queries.end());
            rightNode->queries.insert(queries.begin(), queries.end());
        }

        left = leftNode;
        right = rightNode;
        updateWeights();
    }

    void replaceDestroy(Tinterval newInterval, Tinterval * query, double & a) {
        interval = newInterval;
        if (withQueries) {
            auto start_time = std::chrono::system_clock::now();
            // cout << leafs.size() << endl;
            for(int i = 0; i < leafs.size(); i += 1) {
                // if (leafs[i] != this) {
                    this->queries.insert(leafs[i]->queries.begin(), leafs[i]->queries.end());
                // }
            }
            this->queries.insert(query);
            auto end_time = std::chrono::system_clock::now();
            chrono::duration<double> elapsed_seconds = end_time - start_time;
            a += elapsed_seconds.count();
        }
        updateWeights();
        left = NULL;
        right = NULL;
    }

    void expandDestroy(Tinterval newInterval, Tinterval * query) {
        interval.expand(newInterval);

        if (withQueries) {
            queries.insert(query);
            for(int i = 0; i < leafs.size(); i += 1) {
                queries.insert(leafs[i]->queries.begin(), leafs[i]->queries.end());
            }
        }

        left = NULL;
        right = NULL;
        updateWeights();
    }

    void split(Tinterval * query) {
        // Here problably we will need to store the queries from left or right
        Tinterval left_interval, right_interval;
        interval.split(left_interval, right_interval);
        left = new Node(left_interval, query);
        right = new Node(right_interval, query);
        left->parent = this;
        right->parent = this;

        if (withQueries) {
            left->queries.insert(queries.begin(), queries.end());
            right->queries.insert(queries.begin(), queries.end());
        }

        updateWeights();
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
            }
            // } else {
            leafs.insert(leafs.end(), left->leafs.begin(), left->leafs.end());
            // }
        }
        if (right != NULL) {
            if (right->is_leaf()) {
                leafs.push_back(right);
            }
            // } else {
            leafs.insert(leafs.end(), right->leafs.begin(), right->leafs.end());
            // }
        }
        // if (right == NULL && left == NULL) {
        //     leafs.push_back(this);
        // }
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
