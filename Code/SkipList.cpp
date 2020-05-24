#include "SkipList.hpp"

/**
 *
 * @param key: the key of the Node
 * @param value: the value of the Node
 * @param level: the level of the Node
 */
Node::Node(int key, int value, unsigned int level)
{
    this->key = key;
    this->value = value;
    this->level = level;
    this->forward = new Node *[level + 1];
    // Initialize forward
    for (int i = 0; i < level + 1; ++i)
    {
        forward[i] = nullptr;
    }
}

/**
 *
 */
Node::~Node()
{
    // Delete forward
    delete[] forward;
}

/**
 *
 * @param maxLevel: the max level of a skip list
 * @param p: the probability
 */
SkipList::SkipList(int maxLevel, float p)
{
    this->maxLevel = maxLevel;
    this->p = p;
    currentLevel = 0; // there is no current level
    header = new Node(-1, 0, maxLevel);
}

/**
 *
 * @return a generated random level
 */
unsigned int SkipList::RandomLevel() const
{
    // generate a float in [0, 1)
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_real_distribution<float> dist(0.0, 1.0);

    float r = dist(mt);
    unsigned int level;
    // When r < p and level < maxLevel, generate a new random float in [0,1)
    for (level = 0; r < p && level < maxLevel; ++level)
    {
        r = dist(mt);
    }

    return level;
}

/**
 *
 * @param key: the key we want to insert
 * @param value: the value we want to insert or update
 */
void SkipList::InsertKey(int key, int value)
{
    Node *currentNode = header;
    Node **update = new Node *[maxLevel + 1];
    for (unsigned int i = currentLevel; i != 0xFFFFFFFF; --i)
    {
        while (currentNode->forward[i] != nullptr &&
               currentNode->forward[i]->key < key)
        {
            currentNode = currentNode->forward[i];
        }
        update[i] = currentNode;
    }

    // Find the only possible Node
    currentNode = currentNode->forward[0];

    // is the only possible Node is null, or its key is not correct
    if (currentNode == nullptr or currentNode->key != key)
    {
        unsigned int randomLevel = RandomLevel();
        if (randomLevel > currentLevel)
        {
            for (unsigned int i = currentLevel + 1; i < randomLevel + 1; i++)
            {
                update[i] = header;
            }
            // Update the list current level
            currentLevel = randomLevel;
        }
        Node *newNode = new Node(key, value, randomLevel);

        // insert node by rearranging pointers
        for (unsigned int i = 0; i <= randomLevel; i++)
        {
            newNode->forward[i] = update[i]->forward[i];
            update[i]->forward[i] = newNode;
        }
        delete[]update;
        return;
    }
    currentNode->value = value;
}

/**
 *
 * @param key: the key we want to find
 * @return whether there is such a Node
 */
bool SkipList::FindKey(int key)
{
    Node *currentNode = header;
    for (unsigned int i = currentLevel; i != 0xFFFFFFFF; --i)
    {
        // If next Node's key < current Node, keep moving forward
        while (currentNode->forward[i] and currentNode->forward[i]->key < key)
        {
            currentNode = currentNode->forward[i];
        }
    }

    // Find the only possible Node
    currentNode = currentNode->forward[0];
    // return whether the Node is correct
    return currentNode and currentNode->key == key;
}

/**
 *
 * @param key: the key we want to delete
 * @return whether there is such a Node
 */
bool SkipList::DeleteKey(int key)
{
    // The same process as InsertKey
    Node *currentNode = header;
    Node **update = new Node *[currentLevel + 1];
    for (unsigned int i = currentLevel; i != 0xFFFFFFFF; --i)
    {
        while (currentNode->forward[i] != nullptr &&
               currentNode->forward[i]->key < key)
        {
            currentNode = currentNode->forward[i];
        }
        update[i] = currentNode;
    }
    currentNode = currentNode->forward[0];

    // If the Node is the Node that we want to delete
    if (currentNode != nullptr and currentNode->key == key)
    {
        for (unsigned int i = 0; i <= currentLevel; ++i)
        {
            if (update[i]->forward[i] != currentNode)
            {
                break;
            }
            update[i]->forward[i] = currentNode->forward[i];
        }
        delete currentNode;
        delete[]update;
        return true;
    }

    return false;
}

/**
 *
 */
void SkipList::PrintSkipList()
{
    for (Node *currentNode = header;
         currentNode != nullptr; currentNode = currentNode->forward[0])
    {
        std::cout << "Key is " << currentNode->key << std::endl;
        std::cout << "Value is " << currentNode->value << std::endl;
        std::cout << "Level is " << currentNode->level << std::endl;
        std::cout << "############" << std::endl;
    }
}