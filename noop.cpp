#include <chrono>
#include <ctime>

#include "src/tree.h"

using namespace std;


class A {
public:
    void noop() {
        int a = 2;
        b = 100;
    }

    int b;
};


void noop() {
    int a = 1;
}


int main(int argc, char** argv) {
    Tree<TraitsBase> tree;
    // int query_number;

    // if (argc != 2) {
    //     cout << "Please enter an initial size" << endl;
    //     return 1;
    // }

    // sscanf(argv[1], "%d", &query_number);

    // auto start_time = std::chrono::system_clock::now();
    // // A a;
    // for(int i = 0; i < query_number; i += 1) {
    //     noop();
    // }
    // auto end_time = std::chrono::system_clock::now();
    // std::chrono::duration<double> elapsed_seconds = end_time - start_time;

    // cout << elapsed_seconds.count() << endl;


    return 0;
}
