#include <chrono>
#include <ctime>

#include "src/tree.h"
#include "src/leaftree.h"

using namespace std;


int main(int argc, char** argv) {
    srand (time(NULL));

    int key_domain_size = 1000000;
    int leaf_size = 100000;
    int Q = 150000;

    // int key_domain_size = 1000;
    // int leaf_size = 100;
    // int Q = 150;

    int query_number;
    double tree_time = 0;
    int iters = 5;

    if (argc != 2) {
        cout << "Please enter an initial size" << endl;
        return 1;
    }

    sscanf(argv[1], "%d", &query_number);

    for (int z = 0; z < iters; z++) {
        vector<Interval<int> > queries;
        LeafTree<int> leaftree;

        for (int i = 0; i < query_number; i += 1) {
            int S1 = rand() % key_domain_size;
            int R1 = rand() % Q;
            Interval<int> I(S1, S1 + R1);
            // cout << I << endl;
            queries.push_back(I);
            // tree.insert_interval(I);
        }

        // cout << "++++++++++++++++++++++++++" << endl;
        auto start_time = std::chrono::system_clock::now();

        Tree <int> tree(leaf_size);
        for (int i = 0; i < queries.size(); i += 1) {
            // cout << "i: " << i << endl;
            tree.insert_interval(queries[i]);
            // cout << tree.graphviz(to_string(i)) << endl;
        }
        // vector<Interval<int> > leafs;
        // tree.getLeafs(leafs);

        auto end_time = std::chrono::system_clock::now();
        std::chrono::duration<double> elapsed_seconds = end_time - start_time;
        double local_time = elapsed_seconds.count();
        tree_time += local_time;

        // cout << tree.graphviz("") << endl;
        cout << tree.extra_operations << " - " << tree.extra_insertions << endl;
        cout << "-> " << local_time << endl;

        // cout << "------------------------" << endl;

        // tree.print_intervals();

        // cout << endl << leafs.size() << " - " << tree.leafs.size() << endl;
        // cout << leafs.size() << " -- " << tree.leafs.size() << endl;
        // cout << elapsed_seconds.count() << endl;


    }

    cout << endl << " ---------------------- " << endl;
    cout << tree_time << " - " << iters << endl;
    cout << "Avg: " << (tree_time / iters) << endl;


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

