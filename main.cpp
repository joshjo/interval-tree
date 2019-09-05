#include "src/tree.h"

using namespace std;


int main() {
    srand (time(NULL));
    int S = 1000;
    int R = 150;
    Tree <int> tree;
    for(int i = 0; i < 20; i += 1) {
        int S1 = rand() % S;
        int R1 = rand() % R;
        Interval<int> I(S1, S1 + R1);
        cout << I << endl;
        tree.insert_interval(I);
    }

    // Interval<int> I1(110, 120);
    // Interval<int> I2(190, 210);
    // Interval<int> I3(150, 160);
    // Interval<int> I4(200, 290);
    // Interval<int> I5(100, 200);
    // Interval<int> I6(50, 60);
    // Interval<int> I7(40, 70);
    // Interval<int> I8(10, 45);
    // Interval<int> I9(90, 210);

    // Tree <int> tree;
    // tree.insert_interval(I1);
    // tree.insert_interval(I2);
    // tree.insert_interval(I3);
    // tree.insert_interval(I4);
    // tree.insert_interval(I5);
    // tree.insert_interval(I6);
    // tree.insert_interval(I7);
    // tree.insert_interval(I8);
    // tree.insert_interval(I9);

    // cout << endl;
    // tree.print();
    tree.getLeafs();

    return 0;
}

