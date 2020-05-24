#include <iostream>
#include "SkipList.hpp"
#include <fstream>

int main()
{
    // 新建一个 SkipList 实例，选择合适的 max level 和 p
    SkipList sl(8, 0.5);

    // Read a test file
    std::ifstream test_file("test.txt");
    int key, value;
    while (test_file >> key >> value)
    {
        sl.InsertKey(key, value);
    }
    test_file.close();

    // print the skip list
    sl.PrintSkipList();
    return 0;
}
