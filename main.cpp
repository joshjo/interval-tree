#include <chrono>
#include <ctime>

#include "src/node.h"
#include "src/tree.h"

using namespace std;

typedef Interval<int> Tinterval;


int main(int argc, char** argv) {
    srand (100);

    int key_domain_size = 1000000;
    int leaf_size = 100000;
    int Q = 150000;

    // int key_domain_size = 1000;
    // int leaf_size = 100;
    // int Q = 150;

    int query_number;
    if (argc != 2) {
        cout << "Please enter an initial size" << endl;
        return 1;
    }
    sscanf(argv[1], "%d", &query_number);

    vector<Tinterval > intervals;
    // intervals.push_back(Tinterval(30, 50));
    // intervals.push_back(Tinterval(60, 80));
    // intervals.push_back(Tinterval(20, 90));

    for (int i = 0; i < query_number; i += 1) {
        int S1 = rand() % key_domain_size;
        // int R1 = rand() % Q;
        Interval<int> I(S1, S1 + leaf_size);
        // cout << I << endl;
        intervals.push_back(I);
    }

    auto start_time = std::chrono::system_clock::now();

    Tree <TraitsBase> tree(leaf_size);
    for (int i = 0; i < intervals.size(); i += 1) {
        tree.insert_interval(intervals[i], false);
        tree.graphviz(to_string(i));
    }
    auto end_time = std::chrono::system_clock::now();
    chrono::duration<double> elapsed_seconds = end_time - start_time;
    double iter_time = elapsed_seconds.count();

    cout << iter_time << endl;
    cout << tree.counter << " -- " << tree.insertions << endl;

    for (int i = 0; i < tree.root->leafs.size(); i += 1) {
        cout << tree.root->leafs[i]->interval << " -> " << tree.root->leafs[i]->queries.size() << endl;
        // for (set<Tinterval *>::iterator it = tree.root->leafs[i]->queries.begin(); it != tree.root->leafs[i]->queries.end(); it++) {
        //     cout << "\t" << *(*it) << endl;
        // }
    }

    // cout << tree.graphviz() << endl;
    // vector<Interval<int> > leafs;
    // tree.getLeafs(leafs);
    // cout << tree.root->leafs.size() << "/" << leafs.size() << " " << iter_time << endl;

    return 0;
}

