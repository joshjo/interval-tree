#include <stdio.h>
#include <iostream>
#include <utility>

#include "src/tree.h"

using namespace std;


int main() {
    Tree <int> tree;

    tree.insert_element(15);
    tree.insert_element(10);
    tree.insert_element(3);
    tree.insert_element(20);
    tree.insert_element(14);

    tree.print();
    return 0;
}
