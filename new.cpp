#include "src/newtree.h"
#include "src/config.h"


using namespace std;

typedef long T;
typedef Interval<T> Tinterval;


int main() {
    Tinterval a(800, 830);
    Tinterval b(700, 750);
    Tinterval c(740, 810);
    Tinterval d(600, 750);
    int M = 100;

    // Tinterval c(a);
    // c.min = 40;

    // cout << a << endl;
    // cout << c << endl;

    Tree <ConfigLazy <T> > t(M);

    t.insert(a);
    t.insert(b);
    t.insert(c);
    t.insert(d);

    cout << t.graphviz() << endl;

    return 0;
}
