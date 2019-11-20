#include <chrono>
#include <ctime>

#include "src/tree.h"

using namespace std;


int main(int argc, char** argv) {
    srand (time(NULL));

    int key_domain_size = 10000000;
    int leaf_size = 1000000;
    int Q = 1500000;

    // int key_domain_size = 1000;
    // int leaf_size = 100;
    // int Q = 150;

    int query_number;
    double times = 0;
    int iters = 10;

    if (argc != 2) {
        cout << "Please enter an initial size" << endl;
        return 1;
    }

    sscanf(argv[1], "%d", &query_number);

    for (int z = 0; z < iters; z++) {
        vector<Interval<int> > intervals;
        // intervals.push_back(Interval<int> (49, 161));
        // intervals.push_back(Interval<int> (648, 747));

        for (int i = 0; i < query_number; i += 1) {
            int S1 = rand() % key_domain_size;
            int R1 = rand() % Q;
            Interval<int> I(S1, S1 + R1);
            // cout << I << endl;
            intervals.push_back(I);
            // tree.insert_interval(I);
        }

        // cout << "++++++++++++++++++++++++++" << endl;
        auto start_time = std::chrono::system_clock::now();

        Tree <TraitsBase> tree(leaf_size);
        for (int i = 0; i < intervals.size(); i += 1) {
            tree.insert_interval(intervals[i], false);

            // cout << tree.graphviz(to_string(i)) << endl;
            // cout << "--> " << tree.root->left->leafs.size() << tree.root->right->leafs.size() << endl;
            // cout << tree.root->leafs.size() << "/" << leafs.size() << endl;
            // cout << tree.graphviz(to_string(i)) << endl;
        }
        auto end_time = std::chrono::system_clock::now();
        std::chrono::duration<double> elapsed_seconds = end_time - start_time;
        double iter_time = elapsed_seconds.count();
        times += iter_time;

        // cout << iter_time << endl;
        vector<Interval<int> > leafs;
        tree.getLeafs(leafs);

        // for(int i = 0; i < tree.root->leafs.size(); i++) {
        //     cout << tree.root->leafs[i]->interval << endl;
        // }

        // tree.print_intervals();
        cout << tree.root->leafs.size() << "/" << leafs.size() << " " << iter_time << endl;
    }
    // cout << "Avg: " << (times / iters) << endl;


    // tree.getLeafs(leafs);

    // cout << "leafs size: " << leafs.size() << endl;



    // for (int i = 0; i < intervals.size(); i += 1) {
        // Interval<int> interval = intervals[i];
        // cout << "i: " << i << endl;
        // cout << ".";
        // tree.insert_interval(intervals[i]);
        // cout << intervals[i] << endl;
        // cout << tree.graphviz(to_string(i)) << endl;
    // }
    // tree.insert_interval(Interval<int>(280, 379));
    // cout << "digraph G {\n";
    // cout << tree.graphviz() << endl;
    // cout << "}\n";
    // tree.getLeafs(leafs);

    // cout << leafs.size() << endl;
    // cout << endl;
    // cout << tree.graphviz() << endl;
    // tree.print();

    return 0;
}

