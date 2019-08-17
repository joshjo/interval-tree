#include "src/tree.h"

using namespace std;


int main() {
    // Interval<int> I1(120, 110);
    // Interval<int> I2(115, 150);
    // Interval<int> I3(60, 120);
    Interval<int> I1(110, 150);
    Interval<int> I2(40, 120);
    // Interval<int> I3(5, 5);

    // cout << I1 << endl;

    // cout << B.is_interval() << endl;

    // Node<int> N(I1);

    // Node <int> N1(make_pair(15, 20));
    // Node <int> N2(make_pair(10, 50));
    // cout << N1.distance(N2) << endl;
    // max(3, 4);

    Tree <int> tree;
    tree.insert_interval(I1);
    tree.insert_interval(I2);
    // tree.insert_interval(I3);

    tree.print();

    // tree.insert_element(15);
    // tree.insert_element(10);
    // tree.insert_element(3);
    // tree.insert_element(20);
    // tree.insert_element(14);
    // tree.print();

    // cout << "======================" << endl;

    // tree.insert_interval(make_pair(3, 10));

    // tree.print();
    return 0;
}
