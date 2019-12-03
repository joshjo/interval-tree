#include <chrono>
#include <ctime>


#include "src/leaftree.h"
#include "src/tree.h"
#include "src/config.h"

typedef long T;
typedef Interval<T> Tinterval;

using namespace std;


int main () {
    srand (100);

    int key_domain_size = 10000000;
    int leaf_size = 1000000;
    int query_number = 1000000;

    vector<Tinterval > queries;
    LeafTree<T> leaftree;
    Tree <ConfigExtra<T> > tree(leaf_size);
    vector<Tinterval* > leafs;

    T max_random = key_domain_size - leaf_size;
    // Create random queries
    for (int i = 0; i < query_number; i += 1) {
        T S1 = rand() % max_random;
        Tinterval I(S1, S1 + leaf_size);
        queries.push_back(I);
        // cout << I << endl;
    }

    // Insert queries to tree
    for (int i = 0; i < queries.size(); i += 1) {
        tree.insert_interval(queries[i]);
    }

    // // cout << tree.graphviz() << endl << endl;

    tree.getLeafs(leafs);

    random_shuffle(leafs.begin(), leafs.end());

    for (int i = 0; i < leafs.size(); i += 1) {
        leaftree.insert(*(leafs[i]));
    }

    for (int i = 0; i < queries.size(); i += 1) {
        leaftree.assign(&queries[i]);
    }

    vector <LeafNode<T> *> nodes = leaftree.nodes();

    // for (int i = 0; i < nodes.size(); i++) {
    //     cout << nodes[i]->interval << endl;
    //     for(int j = 0; j < nodes[i]->hashmap.size(); j++) {
    //         Tinterval * query = nodes[i]->hashmap[j].first;
    //         Tinterval interval = nodes[i]->hashmap[j].second;
    //         cout << "\t" << (*query) << " -> " << interval << endl;
    //     }
    // }

    // cout << nodes.size() << endl;


    // cout << leaftree.graphviz() << endl;


    // // cout << leaftree.graphviz() << endl;

    // cout << leaftree.graphviz() << endl;

    // int min = tree.root->leafs[0]->interval.left;
    // int max = tree.root->leafs[tree.root->leafs.size() - 1]->interval.right;

    // cout << tree.graphviz() << endl;


    // Interval<int> Q1(650, 700);
    // // Interval<int> Q1(700, 720);


    // auto start_time = std::chrono::system_clock::now();

    // auto end_time = std::chrono::system_clock::now();
    // std::chrono::duration<double> elapsed_seconds = end_time - start_time;

    // cout << t.graphviz() << endl;


    // cout << elapsed_seconds.count() << endl;
    // tree.print();
    // string * result;
    // int size = t.find(Q1, result);
    // // cout << "size " << size << endl;

    // for (int i = 0; i < size; i++) {
    //     cout << result[i] << endl;
    // }

    return 0;
}
