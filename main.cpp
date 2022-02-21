#include <iostream>
#include "trees.h"

int main()
{
    tree<int> t;
    t.insert(500, 10);
    t.insert(750, 10);
    t.insert(700, 10);
    t.insert(800, 10);
    t.insert(250, 10);
    t.insert(300, 10);
    t.insert(200, 10);
    t.insert(755, 10);
    t.insert(705, 10);
    t.insert(805, 10);
    t.insert(255, 10);
    t.insert(305, 10);
    t.insert(205, 10);
    t.insert(150, 10);

    t.remove(500);
    t.print();
    //t.print_into_file("D:\\tree.txt");

    return 0;
}
