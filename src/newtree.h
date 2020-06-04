#ifndef NEWTREE_H
#define NEWTREE_H

#include "includes.h"

using namespace std;

template <class T>
class Interval {
public:
    typedef Interval<T> Tinterval;
    T min, max;
    Interval() {
        min = 0;
        max = 0;
    }

    Interval(T a, T b) {
        if (a > b) {
            swap(a, b);
        }
        this->min = a;
        this->max = b;
    }

    Interval(const Interval & other) {
        min = other.min;
        max = other.max;
    }

    T length() const {
        /**
         * @return the length of the interval.
         */

        return max - min;
    }


    T midpoint() const {
        /**
         * @return the midpoint of the interval.
         */
        T d = length();

        return (d / 2) + min;
    }

    Tinterval intersection(const Interval & other) {
        Tinterval result(0, 0);
        if ((other.min <= min && min <= other.max) || (other.min <= max && max <= other.max)) {
            result.min = min > other.min ? min : other.min;
            result.max = max < other.max ? max : other.max;
        }

        return result;
    }

    string to_graphviz(string iter = "") {
        if (iter == "") {
            string str = "\"" + to_string() + "\"";
            return str;
        }
        string str = "\"[" + iter + "]" + to_string() + "\"";
        return str;
    }

    string to_string() {
        string str = "[" + std::to_string(min) + "," + std::to_string(max) + ")";

        return str;
    }

    Tinterval operator + (const Tinterval & other) const {
        T a = min < other.min ? min : other.min;
        T b = max > other.max ? max : other.max;

        Tinterval I(a, b);

        return I;
    }

    bool operator < (const Tinterval & other) const {
        /**
         * Override operator '<'
         * @return a boolean with the comparison between two intervals.
         */
        if (other.min <= max) {
            T m = this->midpoint();
            T n = other.midpoint();

            return m < n;
        }
        return (max < other.min);
    }

    bool operator > (const Interval & other) const {
        /**
         * Override operator '<'
         * @return a boolean with the comparison between two intervals.
         */
        if (other.max >= min) {
            T m = this->midpoint();
            T n = other.midpoint();

            return m > n;
        }
        return (min > other.max);
    }

    friend ostream & operator << (ostream &out, const Interval & i) {
        out << '[' << i.min << ';' << i.max << ')';
        return out;
    }
};

template <class Tr>
class Node {
public:
    typedef typename Tr::T T;
    typedef Node<Tr> Tnode;
    typedef Interval<T> Tinterval;

    Node * left;
    Node * right;
    Tinterval interval;

    Node() {
        left = NULL;
        right = NULL;
    }

    Node(Tinterval interval) : Node() {
        this->interval = interval;
    }

    Node(const Tnode & other) {
        interval = Tinterval(other.interval);
        left = other.left;
        right = other.right;
    }

    bool isLeaf() {
        return (left == NULL && right == NULL);
    }
};


template <class Tr>
class Tree {
public:
    typedef typename Tr::T T;
    typedef Node<Tr> Tnode;
    typedef Interval<T> Tinterval;
    Tnode * root;
    T M;

    Tree(T M) {
        root = NULL;
        this->M = M;
    }

    void insert(Tinterval & interval) {
        vector <Tinterval> Q;
        get_intervals(interval, Q);

        for (int i = 0; i < Q.size(); i += 1) {
            Tnode * S = NULL; // Points to the parent of N.
            Tnode * P = NULL;
            Tinterval I(Q[i]);
            search(I, Q, S, P);
            if (S == NULL) {
                root = new Tnode(I);
            } else {
                Tinterval J = I + S->interval;
                Tnode * T = new Tnode(*S);
                Tnode * N = new Tnode(I);
                S->interval = Tinterval(J);

                if (T->interval < N->interval) {
                    S->left = T;
                    S->right = N;
                } else {
                    S->left = N;
                    S->right = T;
                }
                update(S);
            }
        }
    }

    void search(Tinterval & interval, vector<Tinterval> & Q, Tnode * & node, Tnode * & parent) {
        node = root;
        parent = node;

        while(node != NULL && !node->isLeaf())  {
            Tnode * sibling = NULL;
            parent = node;
            if (interval < node->interval) {
                sibling = node->right;
                node = node->left;
                if (sibling != NULL) {
                    Tinterval intersection = interval.intersection(sibling->interval);
                    if (intersection.length() > 0) {
                        Q.push_back(intersection);
                        interval.max = intersection.min;
                    }
                }
            } else {
                sibling = node->left;
                node = node->right;

                if (sibling != NULL) {
                    Tinterval intersection = interval.intersection(sibling->interval);
                    if (intersection.length() > 0) {
                        Q.push_back(intersection);
                        interval.min = intersection.max;
                    }
                }
            }
        }
    }

    void update(Tnode * & parent) {
        if (!parent->isLeaf() && parent->right->interval.min <= parent->left->interval.max) {
            if (parent->interval.length() <= M) {
                parent->left = NULL;
                parent->right = NULL;
            } else {
                T m = parent->interval.midpoint();
                parent->left->interval.max = m;
                parent->right->interval.min = m;
            }
        }
    }

    string graphviz(string iter=""){
        // string str = "digraph G {\n";
        string tree = "";
        graphviz(root, tree, iter);
        // str += tree + "}";
        return tree;
    }

private:
    void insert_interval(Tinterval & I) {
    }

    void get_intervals(const Tinterval interval, vector<Tinterval> & arr) {
        if (interval.length() <= M) {
            Tinterval tmp(interval.min, interval.max);
            arr.push_back(tmp);
        } else {
            T x = interval.min;
            while ((interval.max - x) > M) {
                Tinterval tmp (x, x + M);
                arr.push_back(tmp);
                x += M;
            }
            Tinterval tmp (x, interval.max);
            arr.push_back(tmp);
        }
    }

    void graphviz(Tnode *node, string & tree, string iter="") {
        if (node != NULL) {
            if (node->left == NULL && node->right == NULL) {
                tree += node->interval.to_graphviz(iter);
            }
            if (node->left != NULL) {
                tree += node->interval.to_graphviz(iter) + " -> " + node->left->interval.to_graphviz(iter) + " ";
            }
            if (node->right != NULL) {
                tree += node->interval.to_graphviz(iter) + " -> " + node->right->interval.to_graphviz(iter) + " ";
            }
            if (node->left == NULL && node->right == NULL) {
                tree += node->interval.to_graphviz(iter) + " [shape=box color=blue fillcolor=blue fontcolor=white style=filled]";
            }
            graphviz(node->left, tree, iter);
            graphviz(node->right, tree, iter);
        }
    }

};


#endif // NEWTREE_H
