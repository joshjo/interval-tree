#ifndef AITREE_H
#define AITREE_H

#include "includes.h"

using namespace std;

template <class T>
class AINode {
public:
    typedef Interval<T> Tinterval;
    typedef AINode<T> Tnode;
    Tnode * left;
    Tnode * right;
    Tnode * parent;
    T max;

    Tinterval interval;

    AINode(Tinterval interval) {
        this->interval = interval;
        left = NULL;
        right = NULL;
        parent = NULL;
        max = interval.max;
    }

    void update_weights() {
        if (this->parent != NULL && this->max > parent->max) {
            parent->max = this->max;
            parent->update_weights();
        }
    }

    string to_graphviz(string iter = "") {
        string str = "\"[" + to_string(max) + "]" + interval.to_string() + "\"";
        return str;
    }
};

template <class T>
class AITree {
public:
    typedef Interval<T> Tinterval;
    typedef AINode<T> Tnode;
    Tnode * root;

    AITree() {
        root = NULL;
    }

    Tnode ** search(Tinterval interval, Tnode * & parent = NULL) {
        Tnode ** visitor = &(this->root);
        while ((*visitor) != NULL) {
            parent = *visitor;
            if (interval == (*visitor)->interval) {
                break;
            } else if (interval.min < (*visitor)->interval.min) {
                visitor = &((*visitor)->left);
            } else {
                visitor = &((*visitor)->right);
            }
        }

        return visitor;
    }

    bool insert(Tinterval & newInterval) {
        Tnode * parent = NULL;
        Tnode ** searchNode = this->search(newInterval, parent);
        if ((*searchNode) != NULL) {
            return false;
        }
        (*searchNode) = new Tnode(newInterval);
        (*searchNode)->parent = parent;
        (*searchNode)->update_weights();

        return true;
    }

    void find(T key) {
        // Tnode * visitor = this->root;
        vector <Tinterval * > result;
        priority_queue<Tnode *> q;
        q.push(root);

        while (!q.empty()) {
            Tnode * top = q.top();
            q.pop();
            if (top->interval.intersects(key)) {
                result.push_back(&(top->interval));
            }
            if (top->left != NULL && key < top->left->max) {
                q.push(top->left);
            }
            if (top->right != NULL && key < top->right->max) {
                q.push(top->right);
            }
        }

        cout << "intervals: " << endl;
        for (int i = 0; i < result.size(); i++) {
            cout << *(result[i]) << endl;
        }

    }

    void graphviz(Tnode *node, string & tree, string iter="") {
        if (node != NULL) {
            if (node->parent == NULL && node->left == NULL && node->right == NULL) {
                tree += node->to_graphviz(iter);
            }
            if (node->left != NULL) {
                tree += node->to_graphviz(iter) + " -> " + node->left->to_graphviz(iter) + " ";
            }
            if (node->right != NULL) {
                tree += node->to_graphviz(iter) + " -> " + node->right->to_graphviz(iter) + " ";
            }

            graphviz(node->left, tree, iter);
            graphviz(node->right, tree, iter);
        }
    }

    string graphviz(string iter=""){
        // string str = "digraph G {\n";
        string tree = "";
        graphviz(root, tree, iter);
        // str += tree + "}";
        return tree;
    }

};


#endif // AITREE_H
