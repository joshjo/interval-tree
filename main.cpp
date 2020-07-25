#include "src/newtree.h"

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


vector<Tinterval> thesis_intervals() {
    vector<Tinterval> intervals;

    intervals.push_back(Tinterval(750, 830));
    intervals.push_back(Tinterval(830, 860));
    intervals.push_back(Tinterval(520, 600));
    intervals.push_back(Tinterval(540, 550));
    intervals.push_back(Tinterval(530, 620));
    intervals.push_back(Tinterval(310, 360));
    intervals.push_back(Tinterval(300, 330));
    intervals.push_back(Tinterval(50, 120));
    intervals.push_back(Tinterval(90, 140));
    intervals.push_back(Tinterval(970, 980));
    intervals.push_back(Tinterval(950, 970));
    intervals.push_back(Tinterval(630, 1000));
    intervals.push_back(Tinterval(150, 640));

    return intervals;
}

vector<Tinterval> paper_intervals() {
    vector<Tinterval> intervals;

    intervals.push_back(Tinterval(100, 670));
    intervals.push_back(Tinterval(230, 450));
    intervals.push_back(Tinterval(120, 340));
    intervals.push_back(Tinterval(430, 760));
    intervals.push_back(Tinterval(800, 920));
    return intervals;
}

vector <Tinterval> error_intervals() {
    vector<Tinterval> intervals;

    intervals.push_back(Tinterval(586601, 597902));
    intervals.push_back(Tinterval(307623, 387479));
    intervals.push_back(Tinterval(228781, 258051));
    intervals.push_back(Tinterval(720328, 730508));
    intervals.push_back(Tinterval(430097, 475844));
    intervals.push_back(Tinterval(99818, 137998));
    intervals.push_back(Tinterval(753628, 817571));
    intervals.push_back(Tinterval(591055, 651267));
    intervals.push_back(Tinterval(14969, 105382));
    intervals.push_back(Tinterval(626194, 710101));
    intervals.push_back(Tinterval(645973, 681121));
    intervals.push_back(Tinterval(714529, 729913));
    intervals.push_back(Tinterval(174950, 220592));
    intervals.push_back(Tinterval(577470, 619483));
    intervals.push_back(Tinterval(527152, 545114));
    intervals.push_back(Tinterval(773596, 785860));
    intervals.push_back(Tinterval(452271, 508845));
    intervals.push_back(Tinterval(348913, 411580));
    intervals.push_back(Tinterval(681780, 726753));
    intervals.push_back(Tinterval(253546, 348136));
    intervals.push_back(Tinterval(459248, 498236));
    intervals.push_back(Tinterval(284677, 355542));

    return intervals;
}

template <class Tr>
bool checksum_validate(vector <Tinterval> & queries, Tree <Tr> & t) {
    long long checksum = 0;

    for (size_t i = 0; i < queries.size(); i++) {
        checksum += queries[i].checksum();
    }

    cout << "orginal checksum: " << checksum << endl;
    cout << "tree    checksum: " << t.qMap->checksum() << endl;

    return true;
}

long long checksum_original(vector <Tinterval> & queries) {
    long long checksum = 0;

    for (size_t i = 0; i < queries.size(); i++) {
        checksum += queries[i].checksum();
    }

    return checksum;
}


int main() {
    srand (100);

    int M = 94590;
    int max_key_value = 1000000;
    int range_size = 100000;
    int queries = 100000;

    // int M = 250000;
    // int max_key_value = 1000000;
    // int range_size = 10000;
    // int queries = 100000;

    // int M = 10000;
    // int max_key_value = 1000000;
    // int range_size = 10;
    // int queries = 110705;

    // int M = 2;
    // int max_key_value = 1000;
    // int range_size = 15;
    // int queries = 15;

    // vector <Tinterval> intervals = create_queries(queries, max_key_value, range_size);
    vector <Tinterval> intervals = error_intervals();
    // intervals.push_back(Tinterval(700, 740));
    // intervals.push_back(Tinterval(369, 409));
    // intervals.push_back(Tinterval(370, 375));

    // cout << intervals[intervals.size() - 1] << endl;
    // cout << "*** ADDITIONAL STRATEGY ***" << endl;
    // auto start_time = std::chrono::system_clock::now();
    // QMapExtra <Traits <T>> * qExtra = new QMapExtra <Traits <T>>();
    // Tree <Traits <T> > tExtra(M, qExtra);

    // for (int i = 0; i < queries; i += 1) {
    //     tExtra.insert(intervals[i]);
    // }

    // auto end_time = std::chrono::system_clock::now();
    // chrono::duration<double> elapsed_seconds = end_time - start_time;
    // double total_time = elapsed_seconds.count() - tExtra.qMap->elapsedTime();

    // LeafTree<Traits <T>> leaftree;
    // vector<Node<T> *> leafs;
    // tExtra.root->getLeafs(leafs);
    // random_shuffle(leafs.begin(), leafs.end());

    // for (int i = 0; i < leafs.size(); i++) {
    //     leaftree.insert(leafs[i]->interval);
    // }
    // for (int i = 0; i < queries; i += 1) {
    //     leaftree.assign(&intervals[i]);
    // }
    // tExtra.qMap->indexed = leaftree.numIndexedQueries();
    // tExtra.qMap->summary();

    // cout << "tree checksum:     " << leaftree.checksum() << endl;
    // cout << "original checksum: " << checksum_original(intervals) << endl;
    // cout << "additional total time: " << total_time << endl << endl;

    cout << "*** EAGER STRATEGY ***" << endl;
    auto start_time_eager = std::chrono::system_clock::now();
    QMapEager <Traits <T>> * qEager = new QMapEager <Traits <T>>();
    Tree <Traits <T> > tEager(M, qEager);
    for (int i = 0; i < intervals.size(); i += 1) {
        if (i == 19) {
            tEager.insert(intervals[i]);
        } else {
            tEager.insert(intervals[i]);
        }
        // if (i > 17) {
        //     cout << tEager.graphviz(to_string(i)) << endl;
        // }
    }

    auto end_time_eager = std::chrono::system_clock::now();
    chrono::duration<double> elapsed_seconds_eager = end_time_eager - start_time_eager;
    double total_time_eager = elapsed_seconds_eager.count();
    tEager.qMap->summary();
    checksum_validate(intervals, tEager);

    // tEager.qMap->printAllQueries();
    cout << tEager.graphviz() << endl;
    cout << "eager total time: " << total_time_eager << endl << endl;

    // cout << "*** LAZY STRATEGY ***" << endl;
    // auto start_time_lazy = std::chrono::system_clock::now();
    // QMapLazy <Traits <T>> * qLazy = new QMapLazy <Traits <T>>();
    // Tree <Traits <T> > tLazy(M, qLazy);
    // for (int i = 0; i < intervals.size(); i += 1) {
    //     tLazy.insert(intervals[i]);
    // }
    // auto end_time_lazy = std::chrono::system_clock::now();
    // chrono::duration<double> elapsed_seconds_lazy = end_time_lazy - start_time_lazy;
    // double total_time_lazy = elapsed_seconds_lazy.count();
    // tLazy.qMap->summary();
    // checksum_validate(intervals, tLazy);
    // cout << "lazy total time: " << total_time_lazy << endl << endl;

    return 0;
}
