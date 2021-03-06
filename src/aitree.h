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
    bool color;

    Tinterval interval;

    AINode(Tinterval interval) {
        this->interval = interval;
        left = NULL;
        right = NULL;
        parent = NULL;
        max = interval.max;
        color = RED;
    }

    void update_weights(bool debug=false) {
        if (this->parent != NULL && this->max > parent->interval.max) {
            parent->max = this->max;
            parent->update_weights(debug);
        }
    }

    string to_graphviz(string iter = "") {
        string str = "\"[" + to_string(max) + "]" + interval.to_string() + "{" + iter + "}" + "\"";
        return str;
    }

    Tnode * get_grandparent() {
        if (parent != NULL) {
            return parent->parent;
        }

        return NULL;
    }

    Tnode * get_uncle() {
        Tnode * grand = get_grandparent();
        if (grand) {
            return grand->left == parent ? grand->right : grand->left;
        }

        return NULL;
    }

    Tnode * get_sibling() {
        if (parent) {
            return parent->left == this ? parent->right : parent->left;
        }
        return NULL;
    }

    bool is_leaf() {
        return left == NULL && right == NULL;
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
        /*
            The insertion is based in wikipedia:
            https://es.wikipedia.org/wiki/%C3%81rbol_rojo-negro
        */
        Tnode * parent = NULL;
        Tnode ** searchNode = this->search(newInterval, parent);
        if ((*searchNode) != NULL) {
            return false;
        }
        (*searchNode) = new Tnode(newInterval);
        (*searchNode)->parent = parent;
        insert_case1(*searchNode);

        if (*searchNode) {
            (*searchNode)->update_weights();
        }

        return true;
    }

    void insert_case1(Tnode * n) {
        if (n->parent == NULL ) {
            n->color = BLACK;
        } else {
            insert_case2(n);
        }
    }

    void insert_case2(Tnode * n) {
        if (n->parent->color == BLACK) {
            return;
        } else {
            insert_case3(n);
        }
    }

    void insert_case3(Tnode * n) {
        Tnode * u = n->get_uncle();

        if (u != NULL && u->color == RED) {
            n->parent->color = BLACK;
            u->color = BLACK;
            Tnode * g = n->get_grandparent();
            g->color = RED;
            insert_case1(g);
        } else {
            insert_case4(n);
        }
    }

    void insert_case4(Tnode * n) {
        Tnode * g = n->get_grandparent();

        if (n == n->parent->right && n->parent == g->left) {
            left_rotation(n->parent);
            n = n->left;
        } else if (n == n->parent->left && n->parent == g->right) {
            right_rotation(n->parent);
            n = n->right;
        }
        insert_case5(n);
    }

    void insert_case5(Tnode * n) {
        Tnode * g = n->get_grandparent();

        n->parent->color = BLACK;
        g->color = RED;
        if (n == n->parent->left && n->parent == g->left) {
            right_rotation(g);
        } else {
            left_rotation(g);
        }

        Tnode * s = n->get_sibling();
        if (s != NULL) {
            if (s->is_leaf()) {
                s->max = s->interval.max;
            }
            s->update_weights();
        }

    }

    void left_rotation(Tnode * p) {
        Tnode ** aux = &root;

        if (p->parent != NULL && p->parent->right == p) {
            aux = &(p->parent->right);
        } else if (p->parent != NULL && p->parent->left == p) {
            aux = &(p->parent->left);
        }

        *aux = p->right;
        (*aux)->parent = p->parent;
        p->parent = (*aux);
        p->right = (*aux)->left;
        (*aux)->left = p;

        if (p->right != NULL) {
            p->right->parent = p;
            p->right->update_weights();
        }
    }

    void right_rotation(Tnode * p) {
        Tnode ** aux = &root;

        if (p->parent != NULL && p->parent->right == p) {
            aux = &(p->parent->right);
        } else if (p->parent != NULL && p->parent->left == p) {
            aux = &(p->parent->left);
        }

        *aux = p->left;
        (*aux)->parent = p->parent;
        p->parent = (*aux);
        p->left = (*aux)->right;
        (*aux)->right = p;

        if (p->left != NULL) {
            p->left->parent = p;
            p->left->update_weights();
        }
    }

    vector <Tinterval * > find(T key) {
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

        return result;
    }

    void graphviz(Tnode *node, string & tree, string iter="") {
        if (node != NULL) {
            tree += node->to_graphviz(iter) + "[color=" + (node->color ? "red" : "black") + "] " ;
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
