#include <chrono>
#include <ctime>

#include "src/tree.h"
#include "src/config.h"

using namespace std;

typedef long T;
typedef Interval<T> Tinterval;


int main(int argc, char** argv) {
    // srand (time(NULL));
    srand (100);

    int key_domain_size = 1000000;
    int leaf_size = 100000;

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
        vector<Tinterval > intervals;
        // intervals.push_back(Interval<int> (49, 161));
        // intervals.push_back(Interval<int> (648, 747));

        for (int i = 0; i < query_number; i += 1) {
            T S1 = rand() % key_domain_size;
            Tinterval I(S1, S1 + leaf_size);
            // cout << I << endl;
            intervals.push_back(I);
        }

        auto start_time = std::chrono::system_clock::now();

        Tree <ConfigEager <T> > tree(leaf_size);
        for (int i = 0; i < intervals.size(); i += 1) {
            tree.insert_interval(intervals[i], false);
        }
        auto end_time = std::chrono::system_clock::now();
        std::chrono::duration<double> elapsed_seconds = end_time - start_time;
        double iter_time = elapsed_seconds.count();
        times += iter_time;

        // cout << iter_time << endl;
        vector<Tinterval *> leafs;
        tree.getLeafs(leafs);

        if (tree.root->leafs != NULL) {
            cout << tree.root->leafs->size();
        } else {
            cout << "-";
        }
        cout << "/" << leafs.size() << " " << iter_time << " - " << tree.update_time << endl;

        // for (int i = 0; i < tree.root->leafs->size(); i += 1) {
            // cout << tree.root->leafs->at(i)->interval << endl;
            // cout << tree.root->leafs->at(i)->queries_map->size() << " | " << tree.root->leafs->at(i)->queries->size() << endl;
            // for (int j = 0; j < tree.root->leafs->at(i)->queries_map->size(); j += 1) {
            //     cout << "\t" << *(tree.root->leafs->at(i)->queries_map->at(j).first) << " -> " << tree.root->leafs->at(i)->queries_map->at(j).second << endl;
            // }
            // cout << endl;
            // cout << tree.root->leafs->at(i)->queries->size() << endl;
        // }
        // cout << tree.root->leafs.size() << "/" << leafs.size() << " " << iter_time << endl;
    }


    return 0;
}

