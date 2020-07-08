#include <chrono>
#include <ctime>

#include "src/tree.h"
#include "src/config.h"

using namespace std;

typedef long T;
typedef Interval<T> Tinterval;

vector<Tinterval> create_queries(int queries, int key_domain_size, int range_size) {
    vector<Tinterval> result;

    T max_random = key_domain_size - range_size;
    for (int i = 0; i < queries; i += 1) {
        T rnd = rand() % max_random;
        result.push_back(Tinterval(rnd, rnd + range_size));
    }
    return result;
}


int main(int argc, char** argv) {
    srand (100);

<<<<<<< HEAD
    int M = 100000;
    int max_key_value = 1000000;
=======
    auto start_time = std::chrono::system_clock::now();
    int M = 100000;
    int max_key_value = 1000000;
    int queries = 1000000;
>>>>>>> d5eb1e57b4485180bea20b0be6bfe247e506924b
    int range_size = 100000;
    int queries = 1000000;

    vector<Tinterval > intervals = create_queries(queries, max_key_value, range_size);

<<<<<<< HEAD
    auto start_time = std::chrono::system_clock::now();

    Tree <ConfigLazy <T> > tree(M);
=======
    Tree <ConfigExtra <T> > tree(M);
>>>>>>> d5eb1e57b4485180bea20b0be6bfe247e506924b
    for (int i = 0; i < intervals.size(); i += 1) {
        tree.insert_interval(intervals[i]);
        // bool dbg = false;
        // if (i == 15) {
        //     tree.insert_interval(intervals[i], dbg);
        //     // cout << tree.graphviz(to_string(i)) << endl;
        // } else {
        //     tree.insert_interval(intervals[i], dbg);
        // }
        // if (i >= 15) {
        //     cout << tree.graphviz(to_string(i)) << endl;
        // }
    }
    auto end_time = std::chrono::system_clock::now();
    chrono::duration<double> elapsed_seconds = end_time - start_time;
    double iter_time = elapsed_seconds.count();

    cout << tree.graphviz()<< endl;
    auto end_time = std::chrono::system_clock::now();
    chrono::duration<double> elapsed_seconds = end_time - start_time;
    double iter_time = elapsed_seconds.count();

    cout << "iter_time: " << iter_time << endl;

    // vector<Tinterval *> leafs;
    // tree.getLeafs(leafs);

    // cout << leafs.size() << endl;
    // T * data = tree.getLeafsData();
    // cout << data[0] << " " << data[1] << " " << data[2] << endl;
    cout << "iter time: " << iter_time << endl;
    // cout << tree.graphviz() << endl;


    // T max_random = key_domain_size - leaf_size;
    // for (int i = 0; i < query_number; i += 1) {
    //     int S1 = rand() % max_random;
    //     Tinterval I(S1, S1 + leaf_size);
    //     cout << I << endl;
    //     intervals.push_back(I);
    // }

    // cout << " ---- " << endl;

//     auto start_time = std::chrono::system_clock::now();

//     auto end_time = std::chrono::system_clock::now();
//     chrono::duration<double> elapsed_seconds = end_time - start_time;
//     double iter_time = elapsed_seconds.count();

//     cout << tree.graphviz() << endl;

//     // cout << iter_time << endl;
//     // cout << tree.counter << " -- " << tree.insertions << endl;
//     for (int i = 0; i < tree.root->leafs->size(); i += 1) {
//         Tinterval interval = tree.root->leafs->at(i)->interval;
//         cout << tree.root->leafs->at(i)->interval << "[" << tree.root->leafs->at(i)->queries->size() << "]" << endl;
//         // for (vector<Tinterval *>::iterator it = tree.root->leafs->at(i)->queries->begin(); it != tree.root->leafs->at(i)->queries->end(); it++) {
//             // cout << "\tq" << *(*it) << endl;
// // //         //     for (vector<pair<Tinterval *, Tinterval>>::iterator it2 = tree.root->leafs->at(i)->queries_map->begin(); it2 != tree.root->leafs->at(i)->queries_map->end(); it2++) {
// // //         //         if (it != it2 && it->first == it2->first) {
// // //         //             cout << "\tq" << *(it->first) << " <- " << it->second << endl;
// // //         //             cout << "\tq" << *(it2->first) << " <- " << it2->second << endl << endl;
// // //         //         }
// // //         //     }
// // //         //     // if (it->first->right >= 444301) {
// // //         //     //     cout << "\tq" << *(it->first) << " <- " << it->second << endl;
// // //         //     // }
// // //         //     // cout << "\tq" << *(it->first) << " <- " << it->second << endl;
//         // }
// //     //     // for (vector<pair<Tinterval *, Tinterval>>::iterator it = tree.root->leafs->at(i)->queries_map->begin(); it != tree.root->leafs->at(i)->queries_map->end(); it++) {
// //     //     //     cout << "\tq" << *(it->first) << " <- " << it->second << endl;
// //     //     // }
// //     //     // cout << "  -----" << endl;
// //     //     // for (set<Tinterval *>::iterator it = tree.root->leafs->at(i)->queries->begin(); it != tree.root->leafs->at(i)->queries->end(); it++) {
// //     //     //     cout << "\tq" << *(*it) << endl;
// //     //     // }
//     }

    // vector<Tinterval *> leafs;
    // tree.getLeafs(leafs);
    // cout << tree.root->leafs->size() << "/" << leafs.size() << " " << iter_time << endl;
    // cout << tree.graphviz() << endl;

    return 0;
}

