#include <stdio.h>
#include <iostream>
#include <utility>

#include "src/tree.h"

using namespace std;


int main() {
    Tree <int> tree;

    tree.insert(make_pair(15, 20));
    tree.insert(make_pair(10, 30));
    tree.insert(make_pair(5, 20));
    tree.insert(make_pair(17, 19));
    tree.insert(make_pair(12, 15));
    tree.insert(make_pair(30, 40));

    tree.print();
    return 0;
}
