// https://leetcode.cn/problems/lru-cache/solutions/259678/lruhuan-cun-ji-zhi-by-leetcode-solution/
#include <iostream>
#include <unordered_map>
using namespace std;

// 双向链表+哈希表实现LRU缓存
struct DLinkedNode
{
    int key, value;
    DLinkedNode *prev;
    DLinkedNode *next;
    DLinkedNode() : key(0), value(0), prev(nullptr), next(nullptr) {}
    DLinkedNode(int _key, int _value) : key(_key), value(_value), prev(nullptr), next(nullptr) {}
};

class LRUCache
{
private:
    unordered_map<int, DLinkedNode *> cache;
    DLinkedNode *head;
    DLinkedNode *tail;
    int size;
    int capacity;

public:
    LRUCache(int _capacity) : capacity(_capacity), size(0)
    {
        // 使用伪头部和伪尾部节点
        head = new DLinkedNode();
        tail = new DLinkedNode();
        head->next = tail;
        tail->prev = head;
    }

    int get(int key)
    {
        if (!cache.count(key))
        {
            return -1;
        }
        // 如果 key 存在，先通过哈希表定位，再移到头部
        DLinkedNode *node = cache[key];
        moveToHead(node);
        return node->value;
    }

    void put(int key, int value)
    {
        if (!cache.count(key))
        {
            // 如果 key 不存在，创建一个新的节点
            DLinkedNode *node = new DLinkedNode(key, value);
            // 添加进哈希表
            cache[key] = node;
            // 添加至双向链表的头部
            addToHead(node);
            ++size;
            if (size > capacity)
            {
                // 如果超出容量，删除双向链表的尾部节点
                DLinkedNode *removed = removeTail();
                // 删除哈希表中对应的项
                cache.erase(removed->key);
                // 防止内存泄漏
                delete removed;
                --size;
            }
        }
        else
        {
            // 如果 key 存在，先通过哈希表定位，再修改 value，并移到头部
            DLinkedNode *node = cache[key];
            node->value = value;
            moveToHead(node);
        }
    }

    void addToHead(DLinkedNode *node)
    {
        node->prev = head;
        node->next = head->next;
        head->next->prev = node;
        head->next = node;
    }

    void removeNode(DLinkedNode *node)
    {
        node->prev->next = node->next;
        node->next->prev = node->prev;
    }

    void moveToHead(DLinkedNode *node)
    {
        removeNode(node);
        addToHead(node);
    }

    DLinkedNode *removeTail()
    {
        DLinkedNode *node = tail->prev;
        removeNode(node);
        return node;
    }
};

// 使用单哨兵节点
class Node
{
public:
    int key;
    int value;
    Node *prev;
    Node *next;

    Node(int k = 0, int v = 0) : key(k), value(v) {}
};

class LRUCache02
{
private:
    int capacity;
    Node *dummy; // 哨兵节点
    unordered_map<int, Node *> key_to_node;

    // 删除一个节点（抽出一本书）
    void remove(Node *x)
    {
        x->prev->next = x->next;
        x->next->prev = x->prev;
    }

    // 在链表头添加一个节点（把一本书放在最上面）
    void push_front(Node *x)
    {
        x->prev = dummy;
        x->next = dummy->next;
        x->prev->next = x;
        x->next->prev = x;
    }

    // 获取 key 对应的节点，同时把该节点移到链表头部
    Node *get_node(int key)
    {
        auto it = key_to_node.find(key);
        if (it == key_to_node.end())
        { // 没有这本书
            return nullptr;
        }
        Node *node = it->second; // 有这本书
        remove(node);            // 把这本书抽出来
        push_front(node);        // 放在最上面
        return node;
    }

public:
    LRUCache02(int capacity) : capacity(capacity), dummy(new Node())
    {
        dummy->prev = dummy;
        dummy->next = dummy;
    }

    int get(int key)
    {
        Node *node = get_node(key); // get_node 会把对应节点移到链表头部
        return node ? node->value : -1;
    }

    void put(int key, int value)
    {
        Node *node = get_node(key); // get_node 会把对应节点移到链表头部
        if (node)
        {                        // 有这本书
            node->value = value; // 更新 value
            return;
        }
        key_to_node[key] = node = new Node(key, value); // 新书
        push_front(node);                               // 放在最上面
        if (key_to_node.size() > capacity)
        { // 书太多了
            Node *back_node = dummy->prev;
            key_to_node.erase(back_node->key);
            remove(back_node); // 去掉最后一本书
            delete back_node;  // 释放内存
        }
    }
};

/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache* obj = new LRUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */

int main()
{
    LRUCache cache(2);
    cache.put(1, 1);
    cache.put(2, 2);
    cout << cache.get(1) << ' '; // 返回  1
    cache.put(3, 3);              // 该操作会使得密钥 2 作废
    cout << cache.get(2) << ' '; // 返回 -1 (未找到)
    cache.put(4, 4);              // 该操作会使得密钥 1 作废
    cout << cache.get(1) << ' '; // 返回 -1 (未找到)
    cout << cache.get(3) << ' '; // 返回  3
    cout << cache.get(4) << endl; // 返回  4

    LRUCache02 cache02(2);
    cache02.put(1, 1);
    cache02.put(2, 2);
    cout << cache02.get(1) << ' '; // 返回  1
    cache02.put(3, 3);              // 该操作会使得密钥 2 作废
    cout << cache02.get(2) << ' '; // 返回 -1 (未找到)
    cache02.put(4, 4);              // 该操作会使得密钥 1 作废
    cout << cache02.get(1) << ' '; // 返回 -1 (未找到)
    cout << cache02.get(3) << ' '; // 返回  3    
    cout << cache02.get(4) << ' '; // 返回  4

    return 0;
}