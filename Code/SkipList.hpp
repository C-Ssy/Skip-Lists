#ifndef SKIPLIST_CPP_SKIPLIST_HPP
#define SKIPLIST_CPP_SKIPLIST_HPP

#include <algorithm>
#include <random>
#include <iostream>

class Node
{
private:
    // the key of a node
    int key;
    // the data of the node
    int value;
    //A level i node carries i forward pointers indexed through 0 to i.
    unsigned int level;
    // store all pointers
    Node **forward;

    friend class SkipList;

public:
    Node(int key, int value, unsigned int level);

    ~Node();
};

class SkipList
{
private:

    // Maximum level for this skip list
    unsigned int maxLevel = 32;
    // current level of skip list
    unsigned int currentLevel = 0;
    // pointer to header node
    Node *header = nullptr;
    // probability
    float p = 0.25;

    [[nodiscard]] unsigned int RandomLevel() const;

public:
    explicit SkipList(int maxLevel = 32, float p = 0.25);

    bool InsertKey(int key, int value);

    bool FindKey(int key);

    bool DeleteKey(int key);

    void PrintSkipList();
};


#endif //SKIPLIST_CPP_SKIPLIST_HPP
