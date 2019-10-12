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
    }

    void update_weights() {
        if (this->parent != NULL && this->max > parent->max) {
            parent->max = this->max;
            parent->update_weights();
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

    T assign(Tinterval * query) {
        Tinterval interval(*query);
        Tnode ** visitor = &(this->root);
        while ((*visitor) != NULL) {
            if ((*visitor)->interval.left > interval.right) {
                visitor = &((*visitor)->left);
            } else if ((*visitor)->interval.right <= interval.left) {
                visitor = &((*visitor)->right);
            } else {
                if ((*visitor)->interval.right < interval.right) {
                    // for (T i = interval.left; i < (*visitor)->interval.right; i++) {
                    //     result[index + i - interval.left] = (*visitor)->hashmap[i - (*visitor)->interval.left];
                    // }
                    // index += (*visitor)->interval.right - interval.left;
                    Interval tmp = Tinterval(interval.left, (*visitor)->interval.right);
                    (*visitor)->hashmap.push_back(make_pair(query, tmp))
                    interval = Tinterval((*visitor)->interval.right, interval.right);
                    visitor = &(this->root);
                } else {
                    (*visitor)->hashmap.push_back(make_pair(query, interval));
                    // for (T i = interval.left; i < interval.right; i++) {
                    //     result[index + i - interval.left] = (*visitor)->hashmap[i - (*visitor)->interval.left];
                    // }
                    break;
                }
            }
        }
    }

    // T find (Tinterval interval, string * & result) {
    //     T size = interval.right - interval.left;
    //     result = new string[interval.right - interval.left];
    //     Tnode ** visitor = &(this->root);
    //     int index = 0;
    //     while ((*visitor) != NULL) {
    //         if ((*visitor)->interval.left > interval.right) {
    //             visitor = &((*visitor)->left);
    //         } else if ((*visitor)->interval.right <= interval.left) {
    //             visitor = &((*visitor)->right);
    //         } else {
    //             if ((*visitor)->interval.right < interval.right) {
    //                 for (T i = interval.left; i < (*visitor)->interval.right; i++) {
    //                     result[index + i - interval.left] = (*visitor)->hashmap[i - (*visitor)->interval.left];
    //                 }
    //                 index += (*visitor)->interval.right - interval.left;
    //                 interval = Tinterval((*visitor)->interval.right, interval.right);
    //                 visitor = &(this->root);
    //             } else {
    //                 for (T i = interval.left; i < interval.right; i++) {
    //                     result[index + i - interval.left] = (*visitor)->hashmap[i - (*visitor)->interval.left];
    //                 }
    //                 break;
    //             }
    //         }
    //     }
    //     return size;
    // }


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

    bool insert(Tinterval key) {
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


    string graphviz(string iter="1"){
        // string str = "digraph G {\n";
        string tree = "";
        graphviz(root, tree, iter);
        // str += tree + "}";
        return tree;
    }

};

#endif // LEAFT_TREE_H
