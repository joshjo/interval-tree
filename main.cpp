#include <stdio.h>
#include <iostream>

#include "src/tree.h"

using namespace std;


int main() {
    // printf("Hello World\n");
    Tree <int> tree;
    tree.insert(8);
    tree.insert(3);
    tree.insert(5);
    tree.insert(10);
    // tree.print();
    // printf("root value: %d", tree.root->value);
    return 0;
}