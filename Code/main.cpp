#include <iostream>
#include "SkipList.hpp"

int main()
{
    SkipList sl(8, 0.5);
    sl.InsertKey(2, 5);
    sl.InsertKey(4, 7);
    sl.InsertKey(1, 3);
    sl.PrintSkipList();
    std::cout << sl.FindKey(4) << sl.DeleteKey(4) << sl.FindKey(4);

    return 0;
}
