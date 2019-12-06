#include <chrono>
#include <ctime>

#include "src/tree.h"
#include "src/config.h"

using namespace std;

typedef long T;
typedef Interval<T> Tinterval;


int main(int argc, char** argv) {
    srand (100);

    // int key_domain_size = 100;
    // int leaf_size = 10;

    int key_domain_size = 1000000;
    int leaf_size = 100000;

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

    T max_random = key_domain_size - leaf_size;
    for (int i = 0; i < query_number; i += 1) {
        int S1 = rand() % max_random;
        Tinterval I(S1, S1 + leaf_size);
        // cout << I << endl;
        intervals.push_back(I);
    }

    cout << " ---- " << endl;

    auto start_time = std::chrono::system_clock::now();

    Tree <ConfigEager <T> > tree(leaf_size);
    for (int i = 0; i < intervals.size(); i += 1) {
        bool debug = (i == 29);
        tree.insert_interval(intervals[i], debug);

    }
    auto end_time = std::chrono::system_clock::now();
    chrono::duration<double> elapsed_seconds = end_time - start_time;
    double iter_time = elapsed_seconds.count();

    // cout << tree.graphviz() << endl;

    // cout << iter_time << endl;
    // cout << tree.counter << " -- " << tree.insertions << endl;
    for (int i = 0; i < tree.root->leafs->size(); i += 1) {
        Tinterval interval = tree.root->leafs->at(i)->interval;
        cout << tree.root->leafs->at(i)->interval << "[" << tree.root->leafs->at(i)->queries_map->size() << "]" << endl;
        if (interval.left == 369741) {
            for (vector<pair<Tinterval *, Tinterval>>::iterator it = tree.root->leafs->at(i)->queries_map->begin(); it != tree.root->leafs->at(i)->queries_map->end(); it++) {

                // cout << "\tq" << *(it->first) << " <- " << it->second << endl;
                for (vector<pair<Tinterval *, Tinterval>>::iterator it2 = tree.root->leafs->at(i)->queries_map->begin(); it2 != tree.root->leafs->at(i)->queries_map->end(); it2++) {
                    if (it != it2 && it->first == it2->first) {
                        cout << "\tq" << *(it->first) << " <- " << it->second << endl;
                        cout << "\tq" << *(it2->first) << " <- " << it2->second << endl << endl;
                    }
                }
                // if (it->first->right >= 444301) {
                //     cout << "\tq" << *(it->first) << " <- " << it->second << endl;
                // }
                // cout << "\tq" << *(it->first) << " <- " << it->second << endl;
            }
        }
        // for (vector<pair<Tinterval *, Tinterval>>::iterator it = tree.root->leafs->at(i)->queries_map->begin(); it != tree.root->leafs->at(i)->queries_map->end(); it++) {
        //     cout << "\tq" << *(it->first) << " <- " << it->second << endl;
        // }
        // cout << "  -----" << endl;
        // for (set<Tinterval *>::iterator it = tree.root->leafs->at(i)->queries->begin(); it != tree.root->leafs->at(i)->queries->end(); it++) {
        //     cout << "\tq" << *(*it) << endl;
        // }
    }

    vector<Tinterval *> leafs;
    tree.getLeafs(leafs);
    cout << tree.root->leafs->size() << "/" << leafs.size() << " " << iter_time << endl;
    // cout << tree.graphviz() << endl;

    return 0;
}

