#include "src/tree.h"

using namespace std;


int main() {
    Interval<int> N(50, 100);
    Interval<int> T(100, 200);

    cout << N.on_left_of(T) << endl;
    // cout << (T <= N) << endl;

    // Interval<int> I1(110, 120);
    // Interval<int> I2(190, 210);
    // Interval<int> I3(150, 160);
    // Interval<int> I4(200, 290);
    // Interval<int> I5(100, 200);
    // Interval<int> I6(190, 190);

    // Tree <int> tree;
    // tree.insert_interval(I1);
    // // tree.insert_interval(I2);
    // // tree.insert_interval(I3);
    // // tree.insert_interval(I4);
    // // tree.insert_interval(I5);

    // cout << endl;
    // tree.print();

    return 0;
}

