#include <chrono>
#include <ctime>

#include "src/tree.h"

using namespace std;


int main(int argc, char** argv) {

    // int * a = new int(123);
    // int * b = new int(342);

    // set<int *> queries;

    // queries.insert(a);
    // queries.insert(b);
    // queries.insert(a);

    // set<int *> newQueries;
    // newQueries.insert(queries.begin(), queries.end());

    // cout << newQueries.size() << endl;

    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            if (j == 5) {
                break;
            }
            cout << i << " - " << j << endl;
        }
    }

    return 0;
}
