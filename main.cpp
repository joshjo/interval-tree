#include "src/tree.h"

using namespace std;


int main() {
    srand (time(NULL));
    int Range = 200000;
    int R = 20;
    Tree <int> tree(500);
    for (int i = 0; i < 100; i += 1) {
        int S1 = rand() % Range;
        int R1 = rand() % R;
        Interval<int> I(S1, S1 + R1);
        // cout << I << endl;
        tree.insert_interval(I);
    }

    // cout << tree.graphviz() << endl;
    cout << tree.numberLeafs() << endl;

    // vector<Interval<int> > intervals;
    // intervals.push_back(Interval<int>(10, 15));
    // intervals.push_back(Interval<int>(25, 30));
    // intervals.push_back(Interval<int>(45, 50));
    // intervals.push_back(Interval<int>(60, 65));
    // intervals.push_back(Interval<int>(10, 50));
    // intervals.push_back(Interval<int>(5, 90));
    // // intervals.push_back(Interval<int>(60, 65));
    // // intervals.push_back(Interval<int>(30, 45));

    // // intervals.push_back(Interval<int>(46, 57));
    // // intervals.push_back(Interval<int>(284, 424));
    // // intervals.push_back(Interval<int>(914, 1002));
    // // intervals.push_back(Interval<int>(23, 160));
    // // intervals.push_back(Interval<int>(280, 379));

    // // intervals.push_back(Interval<int>(684, 833));
    // // intervals.push_back(Interval<int>(760, 827));
    // // intervals.push_back(Interval<int>(403, 512));
    // // intervals.push_back(Interval<int>(945, 1031));
    // // intervals.push_back(Interval<int>(597, 725));


    // // Tree <int> tree;
    // // cout << "digraph G {\n";

    // for (int i = 0; i < intervals.size(); i += 1) {
    //     // Interval<int> interval = intervals[i];
    //     // cout << "i: " << i << endl;
    //     tree.insert_interval_intern(intervals[i]);
    //     // cout << intervals[i] << endl;
    //     // if (i >= 2) {
    //     //     cout << tree.graphviz(to_string(i)) << endl;
    //     // }
    // }
    // // tree.insert_interval(Interval<int>(280, 379));
    // // cout << tree.graphviz("4") << endl;
    // // cout << "}\n";
    // // tree.insert_interval(I3);
    // // tree.insert_interval(I4);
    // // tree.insert_interval(I5);
    // // tree.insert_interval(I6);
    // // tree.insert_interval(I7);
    // // tree.insert_interval(I8);
    // // tree.insert_interval(I9);
    // // tree.insert_interval(I0);

    // cout << endl;
    // cout << tree.graphviz() << endl;
    // tree.print();

    // tree.getLeafs();

    return 0;
}

