#include "src/leaftree.h"



using namespace std;


int main () {
    Interval<int> I1(600, 700);
    Interval<int> I2(200, 300);
    Interval<int> I3(400, 480);
    Interval<int> I4(500, 590);
    Interval<int> I5(700, 800);


    Interval<int> Q1(650, 700);
    // Interval<int> Q1(700, 720);

    LeafTree<int> t;


    t.insert(I1);
    t.insert(I2);
    t.insert(I3);
    t.insert(I4);
    t.insert(I5);


    // t.print();
    string * result;
    int size = t.find(Q1, result);
    // cout << "size " << size << endl;

    for (int i = 0; i < size; i++) {
        cout << result[i] << endl;
    }

    return 0;
}
