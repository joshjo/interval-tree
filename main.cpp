#include "src/tree.h"

using namespace std;


int main() {
    // Interval<int> I1(110, 210);
    Interval<int> I1(110, 120);
    Interval<int> I2(190, 210);
    Interval<int> I3(150, 160);
    Interval<int> I4(200, 290);
    Interval<int> I5(100, 200);
    // vector<Interval<int> > arr;
    // I.slice(100, arr);

    // cout << arr.size() << endl;

    // for (auto& it : arr) {
    //     cout << it << endl;
    // }


    // Interval<int> a;
    // Interval<int> b;

    // I1.split(a, b);
    // cout << a << endl;
    // cout << b << endl;
    // Interval<int> I3(60, 120);
    // Interval<int> I1(10, 50);
    // Interval<int> I2(40, 90);
    // Interval<int> I3(10, 40);
    // Interval<int> I4(0, 100);

    // cout << I1.intersects(I2) << endl;
    // cout << (I1 <= I4) << endl;


    // cout << I2.get_location(I3) << endl;
    // cout << ">= " << (I1 >= I2) << endl;
    Tree <int> tree;
    tree.insert_interval(I1);
    tree.insert_interval(I2);
    tree.insert_interval(I3);
    tree.insert_interval(I4);
    tree.insert_interval(I5);
    cout << endl;
    tree.print();



    // cout << "======================" << endl;

    // tree.insert_interval(make_pair(3, 10));

    // tree.print();
    return 0;
}
