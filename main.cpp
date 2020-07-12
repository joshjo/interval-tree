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

template <class Tr>
bool checksum_validate(vector <Tinterval> & queries, Tree <Tr> & t) {
    long long checksum = 0;

    for (size_t i = 0; i < queries.size(); i++) {
        checksum += queries[i].checksum();
    }

    cout << "checksum: " << checksum << endl;
    cout << "checksum: " << t.qMap->checksum() << endl;

    return true;
}


int main() {
    srand (100);

    int M = 100000;
    int max_key_value = 1000000;
    int range_size = 100000;
    int queries = 1000;

    vector <Tinterval> intervals = create_queries(queries, max_key_value, range_size);

    cout << "*** ADDITIONAL STRATEGY ***" << endl;
    auto start_time = std::chrono::system_clock::now();
    QMapExtra <Traits <T>> * qExtra = new QMapExtra <Traits <T>>();
    Tree <Traits <T> > tExtra(M, qExtra);

    for (int i = 0; i < queries; i += 1) {
        tExtra.insert(intervals[i]);
    }

    auto end_time = std::chrono::system_clock::now();
    chrono::duration<double> elapsed_seconds = end_time - start_time;
    double total_time = elapsed_seconds.count() - tExtra.qMap->elapsedTime();

    LeafTree<Traits <T>> leaftree;
    vector<Node<T> *> leafs;
    tExtra.root->getLeafs(leafs);
    random_shuffle(leafs.begin(), leafs.end());

    for (int i = 0; i < leafs.size(); i++) {
        leaftree.insert(leafs[i]->interval);
    }
    for (int i = 0; i < queries; i += 1) {
        leaftree.assign(&intervals[i]);
    }
    tExtra.qMap->indexed = leaftree.numIndexedQueries();
    tExtra.qMap->summary();
    cout << "total time: " << total_time << endl << endl;

    cout << "*** EAGER STRATEGY ***" << endl;
    start_time = std::chrono::system_clock::now();
    QMapEager <Traits <T>> * qEager = new QMapEager <Traits <T>>();
    Tree <Traits <T> > tEager(M, qEager);
    for (int i = 0; i < queries; i += 1) {
        tEager.insert(intervals[i]);
    }

    end_time = std::chrono::system_clock::now();
    elapsed_seconds = end_time - start_time;
    total_time = elapsed_seconds.count();
    tEager.qMap->summary();
    cout << "total time: " << total_time << endl << endl;

    cout << "*** LAZY STRATEGY ***" << endl;
    start_time = std::chrono::system_clock::now();
    QMapLazy <Traits <T>> * qLazy = new QMapLazy <Traits <T>>();
    Tree <Traits <T> > tLazy(M, qLazy);
    for (int i = 0; i < queries; i += 1) {
        tLazy.insert(intervals[i]);
    }
    end_time = std::chrono::system_clock::now();
    elapsed_seconds = end_time - start_time;
    total_time = elapsed_seconds.count();
    tLazy.qMap->summary();
    cout << "total time: " << total_time << endl << endl;

    return 0;
}
