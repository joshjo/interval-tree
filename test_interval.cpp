#include "src/newtree.h"
#include "src/config.h"


using namespace std;

typedef long T;
typedef Interval<T> Tinterval;


string strInterval(Tinterval I, string name) {
    T l = I.length() - 2;
    string s = name + "  ";
    for(int i = 0; i < I.max; i += 1) {
        if (i < I.min) {
            s += ' ';
        } else {
            s += '-';
        }
    }

    return s;
}


int main() {
    T w = 6;
    T w2 = 4;

    T x1 = 8;

    int leaf_size = 100000;


    for (int i = -1; i <= (w * 2) + 1; i += 1) {
        Tinterval a(x1, x1 + w2);
        Tinterval b(x1 - w + i, x1 + i);
        cout << strInterval(a, "a") << endl;
        cout << strInterval(b, "b") << endl;
        cout << a.intersection(b) << endl;
        cout << "a < b " << (a < b) << " | a > b " << (a > b) << endl;
        cout << "b < a " << (b < a) << " | b > a " << (b > a) << endl << endl;
    }


    Tree <ConfigLazy <T> > tree(leaf_size);
    return 0;
}
