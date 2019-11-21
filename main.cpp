#include <chrono>
#include <ctime>

#include "src/tree.h"

using namespace std;

typedef Interval<int> Tinterval;


int main(int argc, char** argv) {
    srand (time(NULL));

    int key_domain_size = 10000000;
    int leaf_size = 1000000;
    int Q = 1500000;

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

    for (int i = 0; i < query_number; i += 1) {
        int S1 = rand() % key_domain_size;
        int R1 = rand() % Q;
        Interval<int> I(S1, S1 + R1);
        // cout << I << endl;
        intervals.push_back(I);
    }

    auto start_time = std::chrono::system_clock::now();

    Tree <TraitsBase> tree(leaf_size);
    for (int i = 0; i < intervals.size(); i += 1) {
        tree.insert_interval(intervals[i], false);
    }
    auto end_time = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds = end_time - start_time;
    double iter_time = elapsed_seconds.count();

    for (int i = 0; i < tree.root->leafs.size(); i += 1) {
        cout << tree.root->leafs[i]->interval << " -> " << tree.root->leafs[i]->queries.size() << endl;
    }

    // cout << iter_time << endl;
    // vector<Interval<int> > leafs;
    // tree.getLeafs(leafs);
    // cout << tree.root->leafs.size() << "/" << leafs.size() << " " << iter_time << endl;

    return 0;
}

