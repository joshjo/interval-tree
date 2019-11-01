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
    // vector <Tinterval> queries;
    vector <pair<Tinterval *, Tinterval> > queries;

    Node() {
        left = NULL;
        right = NULL;
        parent = NULL;
    }

    Node(Tinterval interval) {
        this->interval = interval;
        parent = NULL;
        left = NULL;
        right = NULL;
    }

    Node(Tinterval interval, Tinterval * query) {
        this->interval = interval;
        parent = NULL;
        left = NULL;
        right = NULL;
        queries.push_back(make_pair(query, interval));
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

    void split() {
        Tinterval left_interval, right_interval;
        interval.split(left_interval, right_interval);
        left = new Node(left_interval);
        left->queries = this->queries;
        right = new Node(right_interval);
        left->parent = this;
        right->parent = this;
    }

    void split_half(Tinterval new_interval, Tinterval * query) {
        Tinterval left_interval, right_interval;
        interval.expand(new_interval);
        interval.split(left_interval, right_interval);
        left = new Node(left_interval);
        right = new Node(right_interval);

        left->parent = this;
        right->parent = this;

        if(left_interval.intersects(*query)) {
            Tinterval intersection = left_interval.intersection(*query);
            left->queries.push_back(make_pair(query, intersection));
        }
        if(right_interval.intersects(*query)) {
            Tinterval intersection = right_interval.intersection(*query);
            right->queries.push_back(make_pair(query, intersection));
        }

        /*
        Updating queries intervals from parent to new nodes;
        */
        for (int i = 0; i < this->queries.size(); i += 1) {
            pair <Tinterval *, Tinterval> pair_left(this->queries[i]);
            pair <Tinterval *, Tinterval> pair_right(this->queries[i]);

            if (left_interval.intersects(pair_left.second)) {
                pair_left.second = left_interval.intersection(pair_left.second);
                left->queries.push_back(pair_left);
            }
            if (right_interval.intersects(pair_right.second)) {
                pair_right.second = right_interval.intersection(pair_right.second);
                right->queries.push_back(pair_right);
            }
        }
        update_weights();
    }

    void split_left(Tinterval new_interval, Tinterval * query) {
        Tnode * leftNode = new Tnode(new_interval);
        Tnode * rightNode = new Tnode(interval);
        interval.expand(new_interval);
        leftNode->parent = this;
        rightNode->parent = this;

        rightNode->queries = queries;
        leftNode->queries.push_back(make_pair(query, new_interval));

        left = leftNode;
        right = rightNode;
        update_weights();
    }

    void split_right(Tinterval new_interval, Tinterval * query) {
        Tnode * leftNode = new Tnode(interval);
        Tnode * rightNode = new Tnode(new_interval);
        interval.expand(new_interval);
        leftNode->parent = this;
        rightNode->parent = this;

        leftNode->queries = queries;
        rightNode->queries.push_back(make_pair(query, new_interval));

        left = leftNode;
        right = rightNode;

        update_weights();
    }

    void expand(Tinterval new_interval, Tinterval * query) {
        interval = new_interval;
        queries.clear();


        if(parent == NULL) {
            leafs.push_back(this);
        } else {
            parent->update_weights();
        }

        for (int i = 0; i < leafs.size(); i += 1) {
            queries.insert(queries.end(), leafs[i]->queries.begin(), leafs[i]->queries.end());
        }
        queries.push_back(make_pair(query, query->intersection(new_interval)));

        left = NULL;
        right = NULL;
    }

    bool is_leaf() {
        return ((left == NULL) && (right == NULL));
    }

    void update_weights(bool debug=false) {
        leafs.clear();

        if (left != NULL) {
            if (left->is_leaf()) {
                leafs.push_back(left);
            }
            else {
                leafs.insert(leafs.end(), left->leafs.begin(), left->leafs.end());
            }
        }
        if (right != NULL) {
            if (right->is_leaf()) {
                leafs.push_back(right);
            }
            else {
                leafs.insert(leafs.end(), right->leafs.begin(), right->leafs.end());
            }
        }

        if (this->parent != NULL) {
            if (this->interval.left < parent->interval.left) {
                parent->interval.left = this->interval.left;
            }
            if (this->interval.right > parent->interval.right) {
                parent->interval.right = this->interval.right;
            }
            parent->update_weights();
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
