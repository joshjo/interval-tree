#ifndef NODE_H
#define NODE_H
#include "interval.h"

using namespace std;


template <class Tr>
class Node {
public:
    typedef typename Tr::T T;
    typedef Node<Tr> Tnode;
    typedef Interval<T> Tinterval;
    typedef typename set <Tinterval *>::iterator it;
    vector <Tnode* > * leafs;
    vector <Tinterval *> * queries;
    vector <pair<Tinterval *, Tinterval>> * queries_map;
    bool withLeafs;
    bool withQueries;
    bool mapQueries;

    Node() {
        left = NULL;
        right = NULL;
        parent = NULL;
        withLeafs = Tr::withLeafs;
        withQueries = withLeafs && Tr::withQueries;
        mapQueries = withQueries && Tr::mapQueries;
        leafs = NULL;

        if (withLeafs) {
            leafs = new vector <Tnode *>;
            leafs->push_back(this);
        } else {
            leafs = NULL;
        }
    }

    Node(Tinterval interval) : Node() {
        this->interval = interval;
    }

    Node(Tinterval interval, Tinterval * query) : Node(interval) {
        if (withQueries) {
            if (mapQueries) {
                queries_map = new vector <pair<Tinterval *, Tinterval>>;
                queries_map->push_back(make_pair(query, interval.intersection(*query)));
            } else {
                queries = new vector <Tinterval *>;
                queries->push_back(query);
            }
        }
    }

    double split(Tinterval * query) {
        auto start_time = std::chrono::system_clock::now();
        Tinterval left_interval, right_interval;
        interval.split(left_interval, right_interval);
        left = new Tnode(left_interval, query);
        right = new Tnode(right_interval, query);
        left->parent = this;
        right->parent = this;

        if (withQueries) {
            if (mapQueries) {
                for (typename vector<pair<Tinterval *, Tinterval>>::iterator it = queries_map->begin(); it != queries_map->end(); it++) {
                    Tinterval tmp(it->second);
                    if (tmp.intersects(left_interval)) {
                        left->queries_map->push_back(make_pair(move(it->first), tmp.intersection(left_interval)));
                    }
                    if (tmp.intersects(right_interval)) {
                        right->queries_map->push_back(make_pair(move(it->first), tmp.intersection(right_interval)));
                    }
                }
            } else {
                left->queries->insert(left->queries->end(), queries->begin(), queries->end());
                right->queries->insert(right->queries->end(), queries->begin(), queries->end());
            }
        }
        updateWeights();
        auto end_time = std::chrono::system_clock::now();
        chrono::duration<double> elapsed_seconds = end_time - start_time;

        return elapsed_seconds.count();
    }

    double splitLeft(Tinterval newInterval, Tinterval * query) {
        auto start_time = std::chrono::system_clock::now();
        Tnode * leftNode = new Tnode(newInterval, query);
        Tnode * rightNode = new Tnode(interval, query);
        interval.expand(newInterval);
        leftNode->parent = this;
        rightNode->parent = this;

        if (withQueries) {
            if (mapQueries) {
                rightNode->queries_map = queries_map;
            } else {
                rightNode->queries = queries;
            }
        }

        left = leftNode;
        right = rightNode;
        updateWeights();
        auto end_time = std::chrono::system_clock::now();
        chrono::duration<double> elapsed_seconds = end_time - start_time;

        return elapsed_seconds.count();
    }

    double splitRight(Tinterval newInterval, Tinterval * query) {
        auto start_time = std::chrono::system_clock::now();
        Tnode * leftNode = new Tnode(interval, query);
        Tnode * rightNode = new Tnode(newInterval, query);
        interval.expand(newInterval);
        leftNode->parent = this;
        rightNode->parent = this;

        if (withQueries) {
            if (mapQueries) {
                leftNode->queries_map = queries_map;
            } else {
                leftNode->queries = queries;
            }
        }

        left = leftNode;
        right = rightNode;
        updateWeights();
        auto end_time = std::chrono::system_clock::now();
        chrono::duration<double> elapsed_seconds = end_time - start_time;

        return elapsed_seconds.count();
    }

    double replaceDestroy(Tinterval newInterval, Tinterval * query, double & a) {
        auto start_time = std::chrono::system_clock::now();
        interval = newInterval;
        rebuildNodeQueries(query);

        left = NULL;
        right = NULL;
        updateWeights();
        auto end_time = std::chrono::system_clock::now();
        chrono::duration<double> elapsed_seconds = end_time - start_time;

        return elapsed_seconds.count();
    }

    double expandDestroy(Tinterval newInterval, Tinterval * query) {
        auto start_time = std::chrono::system_clock::now();
        interval.expand(newInterval);
        rebuildNodeQueries(query);

        left = NULL;
        right = NULL;
        updateWeights();
        auto end_time = std::chrono::system_clock::now();
        chrono::duration<double> elapsed_seconds = end_time - start_time;

        return elapsed_seconds.count();
    }

    void rebuildNodeQueries(Tinterval * query) {
        if (withQueries) {
            if (mapQueries) {
                if (!is_leaf()) {
                    queries_map = new vector <pair<Tinterval *, Tinterval>>;
                }
                queries_map->push_back(make_pair(query, query->intersection(interval)));
                set<Tinterval *> allQueries;
                for(int i = 0; i < leafs->size(); i += 1) {
                    if (leafs->at(i) != this) {
                        for(int j = 0; j < leafs->at(i)->queries_map->size(); j += 1) {
                            allQueries.insert(leafs->at(i)->queries_map->at(j).first);
                        }
                    }
                }
                for(typename set<Tinterval *>::iterator it = allQueries.begin(); it != allQueries.end(); it++) {
                    queries_map->push_back(make_pair(*it, (*it)->intersection(interval)));
                }
            } else {
                if (!is_leaf()) {
                    queries = new vector <Tinterval *>;
                }
                queries->push_back(query);
                set<Tinterval *> allQueries;
                for(int i = 0; i < leafs->size(); i += 1) {
                    if (leafs->at(i) != this) {
                        for(int j = 0; j < leafs->at(i)->queries->size(); j += 1) {
                            allQueries.insert(leafs->at(i)->queries->at(j));
                        }
                    }
                }
                for(typename set<Tinterval *>::iterator it = allQueries.begin(); it != allQueries.end(); it++) {
                    queries->push_back(*it);
                }
            }
        }
    }

    bool is_leaf() {
        return ((left == NULL) && (right == NULL));
    }

    void updateWeights() {
        if (withLeafs) {
            bool shouldUpdateLeafs = false;
            int leftNodes = this->left != NULL ? this->left->leafs->size() : 0;
            int rightNodes = this->right != NULL ? this->right->leafs->size() : 0;

            if ((leftNodes + rightNodes) != leafs->size() || leafs->size() == 0) {
                shouldUpdateLeafs = true;
            }
            if (shouldUpdateLeafs) {
                updateLeafs();
            }
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
        leafs->clear();
        if (left != NULL) {
            if (left->is_leaf()) {
                leafs->push_back(left);
            } else {
                leafs->insert(leafs->end(), left->leafs->begin(), left->leafs->end());
            }
        }
        if (right != NULL) {
            if (right->is_leaf()) {
                leafs->push_back(right);
            } else {
                leafs->insert(leafs->end(), right->leafs->begin(), right->leafs->end());
            }
        }
        if (right == NULL && left == NULL) {
            leafs->push_back(this);
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
        std::cout << interval;
    }

    Tnode * left;
    Tnode * right;
    Tnode * parent;
    Tinterval interval;
    T top;
};


#endif // NODE_H
