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

    T checksum() {
        T greater = (max * (max - 1)) / 2;
        T lower = (min * (min - 1)) / 2;

        return greater - lower;
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

        if ((other.min <= min && min <= other.max) || (other.min <= max && max <= other.max) || (min <= other.min && other.min <= max) || (min <= other.max && other.max <= max)) {
            result.min = min > other.min ? min : other.min;
            result.max = max < other.max ? max : other.max;
        }

        return result;
    }

    bool intersects(const Interval & other) {
        Tinterval i = intersection(other);

        return i.length() > 0;
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

    bool operator == (const Interval & other) {
        /**
         * Override operator '=='
         * @return a boolean with the comparison between two intervals.
         */
        return (this->min == other.min) && (this->max == other.max);
    }

    friend ostream & operator << (ostream &out, const Interval & i) {
        out << '[' << i.min << ';' << i.max << ')';
        return out;
    }
};

template <class T>
class Node {
public:
    typedef Node<T> Tnode;
    typedef Interval<T> Tinterval;

    Node * left;
    Node * right;
    Node * parent;
    Tinterval interval;

    vector <Tinterval *> * lazy;

    Node() {
        left = NULL;
        right = NULL;
        parent = NULL;
    }

    Node(const Tnode & other) : Node() {
        interval = Tinterval(other.interval);
        left = other.left;
        right = other.right;
        parent = other.parent;
    }

    Node(Tinterval interval) : Node() {
        this->interval = interval;
    }

    Node(Tinterval interval, Tinterval * query) : Node(interval) {
    }

    void updateLimits() {
        bool hasChange = false;
        if ((left != NULL) && left->interval.min < interval.min) {
            hasChange = true;
            interval.min = left->interval.min;
        }
        if ((right != NULL) && interval.max < right->interval.max) {
            hasChange = true;
            interval.max = right->interval.max;
        }
        if (parent != NULL && hasChange) {
            parent->updateLimits();
        }
    }

    bool isLeaf() {
        return (left == NULL && right == NULL);
    }

    void getLeafs(Tnode * visitor, vector<Tnode *> & leafs) {
        if(visitor != NULL) {
            if (visitor->isLeaf()) {
                leafs.push_back(visitor);
            }
            getLeafs(visitor->left, leafs);
            getLeafs(visitor->right, leafs);
        }
    }

    void getLeafs(vector<Tnode *> & leafs) {
        getLeafs(this, leafs);
    }
};


template <class Tr>
class QMapBase {
public:
    typedef typename Tr::Tinterval Tinterval;
    typedef typename Tr::Tnode Tnode;

    int mergeOps;
    int transferOps;
    int insertOps;
    int maxSizeSet;
    int shareOps;

    QMapBase() {
        mergeOps = 0;
        shareOps = 0;
        transferOps = 0;
        insertOps = 0;
        maxSizeSet = 0;
    }

    virtual void insert(Tnode * & node, Tinterval * interval) {}

    virtual void transfer(Tnode * & from, Tnode * & to) {}

    virtual void share(Tnode * & a, Tnode * & b) {}

    virtual void merge(Tnode * & node) {}

    virtual long long checksum() {
        return 0;
    }

    virtual void summary() {}

    virtual void postInsert() {}
};


template <class Tr>
class QMapExtra: public QMapBase <Tr> {
public:
    typedef typename Tr::Tinterval Tinterval;
    typedef typename Tr::Tnode Tnode;

    void insert(Tnode * & node, Tinterval * interval) {}

    void transfer(Tnode * & from, Tnode * & to) {}

    void share(Tnode * & a, Tnode * & b) {}

    void merge(Tnode * & node) {}

    long long checksum() {
        return 0;
    }

    void summary() {}

    void postInsert() {}
};


template <class Tr>
class QMapLazy : public QMapBase <Tr> {
public:
    typedef typename Tr::Tinterval Tinterval;
    typedef typename Tr::Tnode Tnode;

    typedef pair<Tnode *, Tinterval *> qnPairType;
    typedef map<Tnode *, vector <Tinterval *> *> qnMapType;
    qnMapType qnMap;

    void insert(Tnode * & node, Tinterval * interval) {
        this->insertOps += 1;

        if (qnMap[node] == NULL) {
            qnMap[node] = new vector<Tinterval *>;
        }
        qnMap[node]->emplace_back(interval);
    }

    void transfer(Tnode * & from, Tnode * & to) {
        this->transferOps += 1;

        qnMap[to] = qnMap[from];
        qnMap.erase(from);
    }

    void share(Tnode * & a, Tnode * & b) {
        this->shareOps += 1;
        // Copy all the elements from A
        set<Tinterval *> tempSet;
        typename vector<Tinterval *>::iterator it;
        // Copy all the elements from B
        if (qnMap[a] != NULL) {
            for (it = qnMap[a]->begin(); it != qnMap[a]->end(); it++) {
                tempSet.insert(*it);
            }
        }
        if (qnMap[b] != NULL) {
            for (it = qnMap[b]->begin(); it != qnMap[b]->end(); it++) {
                tempSet.insert(*it);
            }
        }

        vector<Tinterval *> * tempA = new vector<Tinterval *>;
        tempA->reserve(tempSet.size());

        for (typename set<Tinterval *>::iterator it = tempSet.begin(); it != tempSet.end(); it++) {
            tempA->emplace_back(*it);
        }
        vector<Tinterval *> * tempB = new vector<Tinterval *>(tempA->begin(), tempA->end());

        qnMap.erase(a);
        qnMap.erase(b);
        qnMap[a] = tempA;
        qnMap[b] = tempB;
    }

    void merge(Tnode * & node) {
        this->mergeOps += 1;
        vector<Tinterval *> * temp = new vector<Tinterval *>;

        Tnode * a = node->left;
        Tnode * b = node->right;

        vector<Tnode *> leafs;

        if (a != NULL) {
            a->getLeafs(leafs);
        }
        if (b != NULL) {
            b->getLeafs(leafs);
        }

        for (size_t i = 0; i < leafs.size(); i+= 1) {
            Tnode * n = leafs[i];
            if (qnMap[n] != NULL) {
                for (typename vector<Tinterval *>::iterator it = qnMap[n]->begin(); it != qnMap[n]->end(); it++) {
                    temp->push_back((*it));
                }
                qnMap.erase(n);
            }
        }

        if (temp->size() > 0) {
            qnMap[node] = temp;
        }
    }

    long long checksum() {
        long long val = 0;
        for (typename qnMapType::iterator it = qnMap.begin(); it != qnMap.end(); it++) {
            for (size_t i = 0; i < it->second->size(); i++) {
                Tinterval intersection = it->first->interval.intersection(*(it->second->at(i)));
                val += intersection.checksum();
            }
        }

        return val;
    }

    void summary() {
        long indexed = 0;
        cout << "size: " << qnMap.size() << endl;
        for (typename qnMapType::iterator it = qnMap.begin(); it != qnMap.end(); it++) {
            indexed += it->second->size();
            // cout << it->first->interval << " " << it->second->size() << endl;
            // for (size_t i = 0; i < it->second->size(); i++) {
            //     cout << "\t" << *(it->second->at(i)) << endl;
            // }
        }

        cout << "indexed     : " << indexed << endl;
        cout << "insert ops  : " << this->insertOps << endl;
        cout << "max size zet: " << this->maxSizeSet << endl;
        cout << "transfer ops: " << this->transferOps << endl;
        cout << "share ops   : " << this->shareOps << endl;
        cout << "merge ops   : " << this->mergeOps << endl;
    }

    void postInsert() {}
};

template <class Tr>
class QMapEager : public QMapBase <Tr> {
public:
    typedef typename Tr::Tinterval Tinterval;
    typedef typename Tr::Tnode Tnode;

    typedef pair<Tinterval *, Tinterval> qPair;
    typedef map<Tnode *, vector <qPair> *> qMapType;

    qMapType qMap;

    void updateIntersections (Tnode * & node) {
        if (qMap[node] != NULL) {
            for (typename vector <qPair>::iterator it = qMap[node]->begin(); it != qMap[node]->end();) {
                Tinterval intersection = it->first->intersection(node->interval);
                if (intersection.length()) {
                    it->second = intersection;
                    it++;
                } else {
                    qMap[node]->erase(it);
                }
            }
        }
    }

    void insert(Tnode * & node, Tinterval * interval) {
        this->insertOps += 1;

        if (qMap[node] == NULL) {
            qMap[node] = new vector<qPair>;
        }
        Tinterval intersection = interval->intersection(node->interval);
        qMap[node]->emplace_back(make_pair(interval, intersection));
    }

    void transfer(Tnode * & from, Tnode * & to) {
        this->transferOps += 1;

        qMap[to] = qMap[from];
        this->updateIntersections(to);
        qMap.erase(from);
    }

    void share(Tnode * & a, Tnode * & b) {
        this->shareOps += 1;
        // Copy all the elements from A
        set<qPair> tempSet;
        typename vector<qPair>::iterator it;
        // Copy all the elements from B
        if (qMap[a] != NULL) {
            for (it = qMap[a]->begin(); it != qMap[a]->end(); it++) {
                tempSet.insert(*it);
            }
        }
        if (qMap[b] != NULL) {
            for (it = qMap[b]->begin(); it != qMap[b]->end(); it++) {
                tempSet.insert(*it);
            }
        }

        vector<qPair> * tempA = new vector<qPair>;
        tempA->reserve(tempSet.size());

        for (typename set<qPair>::iterator it = tempSet.begin(); it != tempSet.end(); it++) {
            tempA->emplace_back(*it);
        }
        vector<qPair> * tempB = new vector<qPair>(tempA->begin(), tempA->end());

        qMap.erase(a);
        qMap.erase(b);
        qMap[a] = tempA;
        qMap[b] = tempB;

        updateIntersections(a);
        updateIntersections(b);
    }

    void merge(Tnode * & node) {
        this->mergeOps += 1;
        vector<qPair> * temp = new vector<qPair>;

        Tnode * a = node->left;
        Tnode * b = node->right;

        vector<Tnode *> leafs;

        if (a != NULL) {
            a->getLeafs(leafs);
        }
        if (b != NULL) {
            b->getLeafs(leafs);
        }

        for (size_t i = 0; i < leafs.size(); i+= 1) {
            Tnode * n = leafs[i];
            if (qMap[n] != NULL) {
                for (typename vector<qPair>::iterator it = qMap[n]->begin(); it != qMap[n]->end(); it++) {
                    temp->push_back((*it));
                }
                qMap.erase(n);
            }
        }

        if (temp->size() > 0) {
            qMap[node] = temp;
            updateIntersections(node);
        }
    }

    long long checksum() {
        long long val = 0;
        for (typename qMapType::iterator it = qMap.begin(); it != qMap.end(); it++) {
            for (size_t i = 0; i < it->second->size(); i++) {
                // Tinterval intersection = it->first->interval.intersection(*(it->second->at(i)));
                // val += intersection.checksum(it->second->at(i)->second.checksum());
                val += it->second->at(i).second.checksum();
            }
        }

        return val;
    }

    void summary() {
        long indexed = 0;
        cout << "size: " << qMap.size() << endl;
        for (typename qMapType::iterator it = qMap.begin(); it != qMap.end(); it++) {
            indexed += it->second->size();
            // cout << it->first->interval << " " << it->second->size() << endl;
            // for (size_t i = 0; i < it->second->size(); i++) {
            //     cout << "\t" << *(it->second->at(i)) << endl;
            // }
        }

        cout << "indexed     : " << indexed << endl;
        cout << "insert ops  : " << this->insertOps << endl;
        cout << "max size zet: " << this->maxSizeSet << endl;
        cout << "transfer ops: " << this->transferOps << endl;
        cout << "share ops   : " << this->shareOps << endl;
        cout << "merge ops   : " << this->mergeOps << endl;
    }

    void postInsert() {}
};


template <class C>
class Traits {
public:
    typedef C T;
    typedef Node<T> Tnode;
    typedef Interval<T> Tinterval;
};


template <class Tr>
class Tree {
public:
    typedef typename Tr::T T;
    typedef typename Tr::Tinterval Tinterval;
    typedef typename Tr::Tnode Tnode;

    Tnode * root;
    T M;

    QMapBase<Tr> * qMap;

    Tree(T M, QMapBase<Tr> * qMap) {
        root = NULL;
        this->M = M;
        this->qMap = qMap;
    }

    void search(Tinterval & interval, vector<Tinterval> & Q, Tnode * & node) {
        node = root;
        while(node != NULL && !node->isLeaf())  {
            Tinterval leftIntersection, rightIntersection;
            Tnode * sibling;
            bool isRight = 0;

            if (node->left != NULL) {
                leftIntersection = interval.intersection(node->left->interval);
            }
            if (node->right != NULL) {
                rightIntersection = interval.intersection(node->right->interval);
            }
            // Its important to check first if the child nodes has intersections
            if (leftIntersection.length() > 0) {
                node = node->left;
                sibling = node->right;
            } else if (rightIntersection.length() > 0) {
                node = node->right;
                sibling = node->left;
                isRight = 1;
            } else if (interval < node->interval) {
                node = node->left;
                sibling = node->right;
            } else {
                node = node->right;
                sibling = node->left;
                isRight = 1;
            }
            if (isRight && leftIntersection.length() > 0) {
                Q.push_back(Tinterval(interval.min, leftIntersection.max));
                interval.min = leftIntersection.max;
            } else if (!isRight && rightIntersection.length() > 0) {
                Q.push_back(Tinterval(rightIntersection.min, interval.max));
                interval.max = rightIntersection.min;
            }
        }
    }

    void insert(Tinterval & interval) {
        vector <Tinterval> Q;
        get_intervals(interval, Q);

        for (int i = 0; i < Q.size(); i += 1) {
            Tnode * S = NULL; // Points to the parent of N.
            Tinterval I(Q[i]);
            search(I, Q, S);
            if (S == NULL) {
                root = new Tnode(I);
                qMap->insert(root, &interval);
            } else {
                Tinterval J = I + S->interval;
                if (S->interval.min <= J.min && J.max <= S->interval.max) {
                    // Update new queries
                    qMap->insert(S, &interval);
                } else {
                    Tnode * T = new Tnode(*S);
                    Tnode * N = new Tnode(I);
                    S->interval = Tinterval(J);

                    qMap->transfer(S, T);
                    qMap->insert(N, &interval);

                    if (T->interval < N->interval) {
                        S->left = T;
                        S->right = N;
                    } else {
                        S->left = N;
                        S->right = T;
                    }
                    T->parent = S;
                    N->parent = S;
                    update(S);

                    if (S->parent != NULL) {
                        S->parent->updateLimits();
                    }
                }
            }
        }
    }

    void update(Tnode * & node) {
        if (!node->isLeaf() && (node->left->interval.max == node->right->interval.min || node->right->interval.intersects(node->left->interval))) {
            if (node->interval.length() <= M) {
                update_merge(node);
            } else if(node->left->isLeaf() && node->right->isLeaf()) {
                udate_resize(node);
            }
        }
    }

    void update_merge(Tnode * & node) {
        if (node != NULL && node->interval.length() <= M) {
            if (node->left->interval.min < node->interval.min) {
                node->interval.min = node->left->interval.min;
            }
            if (node->right->interval.max > node->interval.max) {
                node->interval.max = node->right->interval.max;
            }
            qMap->merge(node);
            node->left = NULL;
            node->right = NULL;

            // Todo: Consider this recursive call
            update_merge(node->parent);
        }
    }

    void udate_resize(Tnode * & node) {
        T m = node->interval.midpoint();
        node->left->interval.max = m;
        node->right->interval.min = m;
        qMap->share(node->left, node->right);
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
