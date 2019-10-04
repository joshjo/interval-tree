#include <chrono>
#include <ctime>

#include "src/tree.h"

using namespace std;


int main(int argc, char** argv) {
    srand (time(NULL));
    // int key_domain_size = 10000000;
    // int leaf_size = 1000000;
    // int Q = 1500000;

    int key_domain_size = 1000;
    int leaf_size = 100;
    int Q = 150;


    int query_number;
    double times = 0;
    int iters = 1;

    if (argc != 2) {
        cout << "Please enter an initial size" << endl;
        return 1;
    }

    sscanf(argv[1], "%d", &query_number);

    Tree <int> tree(leaf_size);

    vector<Interval<int> > intervals;

    for (int i = 0; i < query_number; i += 1) {
        int S1 = rand() % key_domain_size;
        int R1 = rand() % Q;
        Interval<int> I(S1, S1 + R1);
        // cout << I << endl;
        intervals.push_back(I);
    }

    for (int i = 0; i < intervals.size(); i+= 1) {
        // bool debug = i == 9;
        bool debug = false;
        // cout << "i " << i << " - " << intervals[i] << endl;
        tree.insert_interval(intervals[i], debug);
        // cout << " ======== " << endl;
        // cout << tree.graphviz(to_string(i)) << endl;
    }
    // cout << tree.graphviz("x") << endl;

    return 0;
}
