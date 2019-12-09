#ifndef LEAFT_TREE_H
#define LEAFT_TREE_H
#include "interval.h"

#include "includes.h"


template <class T>
class LeafNode {

public:
    typedef Interval<T> Tinterval;
    typedef LeafNode<T> Tnode;
    Tnode * left;
    Tnode * right;
    Tnode * parent;
    T max;

    Tinterval interval;
    /*
        Intervals has to works as queries and range of leaf node
    */
    // The pair is composed by a pointer to the query and the current range
    // that belongs to the query.
    vector <pair<Tinterval *, Tinterval> > hashmap;

    LeafNode(Tinterval interval) {
        this->interval = interval;
        T size = interval.right - interval.left;
        left = NULL;
        right = NULL;
        parent = NULL;
    }

    void update_weights() {
        if (this->parent != NULL && this->max > parent->max) {
            parent->max = this->max;
            parent->update_weights();
        }
    }


    void printHashMap() {
        for (int i = 0; i < hashmap.size(); i += 1) {
            cout << *(hashmap[i].first) << ", ";
        }
    }

    void print() {
        printf("[%d, %d](%d)", interval.left, interval.right, max);
    }
};


template <class T>
class LeafTree {

public:
    typedef LeafNode<T> Tnode;
    typedef Interval<T> Tinterval;
    Tnode * root;

    LeafTree() {
        root = NULL;
    }

    void assign(Tinterval * query) {
        queue<Tinterval> pending;
        pending.push(*query);
        while (!pending.empty()) {
            Tnode ** visitor = &(this->root);
            Tinterval interval = pending.front();
            pending.pop();
            while ((*visitor) != NULL) {
                if (interval.left >= (*visitor)->interval.right) {
                    visitor = &((*visitor)->right);
                } else if (interval.right <= (*visitor)->interval.left) {
                    visitor = &((*visitor)->left);
                } else {
                    T left, right;
                    if (interval.left < (*visitor)->interval.left) {
                        left = (*visitor)->interval.left;
                        Tinterval tempInterval = Tinterval(interval.left, (*visitor)->interval.left);
                        pending.push(tempInterval);
                    } else {
                        left = interval.left;
                    }
                    if (interval.right > (*visitor)->interval.right) {
                        right = (*visitor)->interval.right;
                        Tinterval tempInterval = Tinterval((*visitor)->interval.right, interval.right);
                        pending.push(tempInterval);
                    } else {
                        right = interval.right;
                    }
                    (*visitor)->hashmap.push_back(make_pair(query, Tinterval(left, right)));
                    break;
                }
            }
        }


        // cout << endl;
    }

    Tnode ** search(Tinterval interval, Tnode * & parent = NULL) {
        Tnode ** visitor = &(this->root);
        while ((*visitor) != NULL) {
            parent = *visitor;
            if (interval == (*visitor)->interval) {
                break;
            } else if (interval < (*visitor)->interval) {
                visitor = &((*visitor)->left);
            } else {
                visitor = &((*visitor)->right);
            }
        }

        return visitor;
    }

    bool insert(Tinterval & key) {
        Tnode * parent = NULL;
        Tnode ** searchNode = this->search(key, parent);
        if ((*searchNode) != NULL) {
            return false;
        }
        (*searchNode) = new Tnode(key);
        (*searchNode)->parent = parent;
        (*searchNode)->update_weights();

        return true;
    }

    void print() {
        print(this->root);
        printf("\n");
    }

    void print(Tnode * visitor) {
        if (visitor != NULL) {
            visitor->print();
            printf(" -> ");
            print(visitor->left);
            print(visitor->right);
        } else {
            printf("nil | ");
        }
    }

    void graphviz(Tnode *node, string & tree, string iter="") {
        if (node != NULL) {
            if (node->parent == NULL && node->left == NULL && node->right == NULL) {
                tree += node->interval.to_graphviz(iter);
                for (int i = 0; i < node->hashmap.size(); i += 1) {
                    tree += node->interval.to_graphviz(iter); + " -> " + node->hashmap[i].first->to_graphviz(iter) + " ";
                }
            }
            if (node->left != NULL) {
                tree += node->interval.to_graphviz(iter) + " -> " + node->left->interval.to_graphviz(iter) + " ";
            }
            if (node->right != NULL) {
                tree += node->interval.to_graphviz(iter) + " -> " + node->right->interval.to_graphviz(iter) + " ";
            }

            graphviz(node->left, tree, iter);
            graphviz(node->right, tree, iter);
        }
    }

    void getLeafHash() {
        getLeafHash(root);
    }

    void getLeafHash(Tnode * visitor) {
        if (visitor != NULL) {
            cout << "==>" << visitor->interval << " - ";
            visitor->printHashMap();
            cout << endl;
            getLeafHash(visitor->left);
            getLeafHash(visitor->right);
        }
    }

    string graphviz(string iter=""){
        // string str = "digraph G {\n";
        string tree = "";
        graphviz(root, tree, iter);
        // str += tree + "}";
        return tree;
    }

    void get_nodes(Tnode * visitor, vector<Tnode *> & nodes) {
        if (visitor != NULL) {
            nodes.push_back(visitor);
            get_nodes(visitor->left, nodes);
            get_nodes(visitor->right, nodes);
        }
    }

    vector<Tnode *> nodes () {
        vector<Tnode *> result;
        get_nodes(root, result);
        return result;
    }

};

#endif // LEAFT_TREE_H
