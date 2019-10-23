#include <chrono>
#include <ctime>


#include "src/leaftree.h"
#include "src/tree.h"


using namespace std;


int main () {
    int key_domain_size = 1000;
    int leaf_size = 100;
    int Q = 150;
    int query_number = 10;

    vector<Interval<int> > queries;
    LeafTree<int> leaftree;
    Tree<int> tree;
    vector<Interval<int> > leafs;


    // Create random queries
    for (int i = 0; i < query_number; i += 1) {
        int S1 = rand() % key_domain_size;
        int R1 = rand() % Q;
        Interval<int> I(S1, S1 + R1);
        queries.push_back(I);
        cout << I << endl;
    }

    // Insert queries to tree
    for (int i = 0; i < queries.size(); i += 1) {
        tree.insert_interval(queries[i]);
    }

    // cout << tree.graphviz() << endl << endl;


    for (int i = 0; i < tree.root->leafs.size(); i += 1) {
        leafs.push_back(tree.root->leafs[i]->interval);
    }

    random_shuffle(leafs.begin(), leafs.end());

    for (int i = 0; i < leafs.size(); i += 1) {
        leaftree.insert(leafs[i]);
    }

    for (int i = 0; i < queries.size(); i += 1) {
        leaftree.assign(&queries[i]);
    }

    vector <LeafNode<int> *> nodes = leaftree.nodes();

    for (int i = 0; i < nodes.size(); i++) {

    }

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
