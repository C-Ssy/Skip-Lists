#include "SkipList.hpp"

Node::Node(int key, int value, unsigned int level)
{
    this->key = key;
    this->value = value;
    this->level = level;
    this->forward = new Node *[level + 1];
    memset(forward, 0, sizeof(Node *) * (level + 1));
    // std::fill(forward[0], forward[0] + (level + 1)*1, nullptr);
}

Node::~Node()
{
    // delete forward
    delete[] forward;
}

SkipList::SkipList(int maxLevel, float p)
{
    this->maxLevel = maxLevel;
    this->p = p;
    currentLevel = 0;
    header = new Node(-1, 0, maxLevel);
}

unsigned int SkipList::RandomLevel() const
{
    // 产生 0 - 1 的随机浮点数
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_real_distribution<float> dist(0.0, 1.0);


    float r = dist(mt);
    unsigned int level;
    for (level = 0; r < p && level < maxLevel; ++level)
    {
        r = dist(mt);
    }

    return level;
}

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

    // 找到唯一有可能的节点
    currentNode = currentNode->forward[0];

    // 如果节点不存在或节点的 key 值不对
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

bool SkipList::FindKey(int key)
{
    Node *currentNode = header;
    for (unsigned int i = currentLevel; i != 0xFFFFFFFF; --i)
    {
        // 下一个节点的值小于待寻找的key，则继续前进
        while (currentNode->forward[i] and currentNode->forward[i]->key < key)
        {
            currentNode = currentNode->forward[i];
        }
    }

    // final 为唯一有可能的节点
    currentNode = currentNode->forward[0];

    return currentNode and currentNode->key == key;
}

bool SkipList::DeleteKey(int key)
{
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

    // 如果目前的节点就是目标节点
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