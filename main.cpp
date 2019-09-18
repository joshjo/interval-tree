#include "src/tree.h"

using namespace std;


int main() {
    srand (time(NULL));
    int S = 1000;
    int R = 150;
    Tree <int> tree(1000);
    vector<Interval<int> > intervals;
    // for (int i = 0; i < 5; i += 1) {
    //     int S1 = rand() % S;
    //     int R1 = rand() % R;
    //     Interval<int> I(S1, S1 + R1);
    //     cout << I << endl;
    //     intervals.push_back(I);
    //     // tree.insert_interval(I);
    //     // cout << tree.graphviz() << endl;
    // }

    intervals.push_back(Interval<int>(591, 640));
    intervals.push_back(Interval<int>(824, 965));
    intervals.push_back(Interval<int>(385, 512));
    intervals.push_back(Interval<int>(74, 168));
    intervals.push_back(Interval<int>(579, 666));
    intervals.push_back(Interval<int>(550, 600));

    for (int i = 0; i < intervals.size(); i += 1) {
        // Interval<int> interval = intervals[i];
        // cout << "i: " << i << endl;
        // cout << ".";
        tree.insert_interval(intervals[i]);
        // cout << intervals[i] << endl;
        cout << tree.graphviz(to_string(i)) << endl;
    }
    // tree.insert_interval(Interval<int>(280, 379));
    // cout << "digraph G {\n";
    // cout << tree.graphviz() << endl;
    // cout << "}\n";
    // cout << endl;
    // cout << tree.graphviz() << endl;
    // tree.print();

    return 0;
}

