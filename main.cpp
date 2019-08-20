#include "src/tree.h"

using namespace std;


int main() {
    Interval<int> I1(205, 295);
    Interval<int> I2(180, 210);
    // Interval<int> I3(60, 120);
    // Interval<int> I1(10, 50);
    // Interval<int> I2(40, 90);
    // Interval<int> I3(10, 40);
    // Interval<int> I4(0, 100);

    // cout << I1.intersects(I2) << endl;
    // cout << (I1 >= I2) << endl;


    // cout << I2.get_location(I3) << endl;
    // cout << ">= " << (I1 >= I2) << endl;
    Tree <int> tree;
    tree.insert_interval(I1);
    tree.insert_interval(I2);
    // tree.insert_interval(I3);
    // tree.insert_interval(I4);

    tree.print();



    // cout << "======================" << endl;

    // tree.insert_interval(make_pair(3, 10));

    // tree.print();
    return 0;
}
