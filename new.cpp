#include "src/newtree.h"
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


int main() {
    srand (100);

    // // vector <Tinterval> intervals = thesis_intervals();
    // vector <Tinterval> intervals;

    // intervals.push_back(Tinterval(150, 170));
    // intervals.push_back(Tinterval(620, 630));
    // intervals.push_back(Tinterval(100, 110));
    // intervals.push_back(Tinterval(680, 690));
    // intervals.push_back(Tinterval(100, 850));
    // int M = 1000;
    // Tree <ConfigLazy <T> > t(M);


    // for (int i = 0; i < intervals.size(); i += 1) {
    //     t.insert(intervals[i]);
    //     // cout << t.graphviz(to_string(i))<< endl;
    // }
    // // t.getQN();
    // cout << t.graphviz()<< endl;
    // t.qnMap.summary();


    int M = 100000;
    int max_key_value = 1000000;
    int range_size = 100000;
    int queries = 1000000;

    vector <Tinterval> intervals = create_queries(queries, max_key_value, range_size);

    Tree <ConfigLazy <T> > t(M);

    for (int i = 0; i < queries; i += 1) {
        // if (i == 13) {
        //     t.insert(intervals[i]);
        // } else {
        //     t.insert(intervals[i]);
        // }
        t.insert(intervals[i]);
        // if (i >= 12) {
        //     // cout << "i" << intervals[i] << endl;
        //     cout << t.graphviz(to_string(i))<< endl;
        // }
    }

    cout << t.graphviz() << endl;

    t.qnMap.summary();

    return 0;
}
