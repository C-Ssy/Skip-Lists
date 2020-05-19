#ifndef SKIPLIST_CPP_SKIPLIST_HPP
#define SKIPLIST_CPP_SKIPLIST_HPP

#include <algorithm>
#include <random>
#include <iostream>


class Node
{
private:
    // the data of a node
    int key;
    //A level i node carries i forward pointers indexed through 0 to i.
    unsigned int level;
    // store all pointers
    Node **forward;

    friend class SkipList;

public:
    Node(int key, unsigned int level);

    ~Node();
};

struct NodeWithUpdate
{
    Node *current = nullptr;
    Node **update = nullptr;
    ~NodeWithUpdate();
};

class SkipList
{
private:

    // Maximum level for this skip list
    unsigned int maxLevel;
    // current level of skip list
    unsigned int currentLevel;
    // pointer to header node
    Node *header;
    //
    float p;

    [[nodiscard]] unsigned int RandomLevel() const;

public:
    SkipList(int maxLevel, float p);

    bool InsertKey(int key);

    bool FindKey(int key);

    bool DeleteKey(int key);

    void PrintSkipList();
};


#endif //SKIPLIST_CPP_SKIPLIST_HPP
