#include <chrono>
#include <ctime>

#include "src/tree.h"
#include "src/leaftree.h"

using namespace std;


class A {
public:
    void noop() {
        int a = 2;
        b = 100;
    }

    int b;
};


void noop() {
    int a = 1;
}


int main(int argc, char** argv) {
    // srand (time(NULL));

    int key_domain_size = 100000;
    int leaf_size = 10000;
    int Q = 15000;
    int query_number = 100;

    vector<Interval<int> > queries;
    LeafTree<int> leaftree;

    for (int i = 0; i < query_number; i += 1) {
        int S1 = rand() % key_domain_size;
        int R1 = rand() % Q;
        Interval<int> I(S1, S1 + R1);
        // cout << i << ": " << I << endl;
        queries.push_back(I);
        // tree.insert_interval(I);
    }
    // queries.push_back(Interval<int>(100, 150));
    // queries.push_back(Interval<int>(180, 190));
    // queries.push_back(Interval<int>(100, 200));

    Tree <int> tree(leaf_size);
    for (int i = 0; i < queries.size(); i += 1) {
        // cout << "q" << i + 1 << ": " << queries[i] << endl;
        tree.insert_interval(queries[i], false);
        // cout << tree.graphviz(to_string(i)) << endl;
    }

    // cout << tree.graphviz() << endl;

    // cout << tree.root->leafs.size() << endl;

    // for (int i = 0; i < tree.root->leafs.size(); i += 1) {
    //     Tree<int>::Tnode * node = tree.root->leafs[i];
    //     cout << "node:   " << node->interval << endl;
    //     for (int j = 0; j < node->queries.size(); j += 1) {
    //         cout << "\t" << *(node->queries[j].first) << " - " << node->queries[j].second << endl;
    //     }
    //     cout << "queries: " << node->queries.size() << endl;
    // }


    // for (int i = 0; i < queries[])
    // cout << tree.graphviz() << endl;

    // cout << *(tree.root->queries[0].first) << " - " << tree.root->queries[0].second << endl;
    // cout << tree.root->queries.size() << endl;

    return 0;
}
