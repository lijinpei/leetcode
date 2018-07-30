#include <map>
#include <iostream>

struct Node {
  Node *next, *prev;
  std::map<int, void*>::iterator pos;
  int val;
  Node(Node* n, Node* p, int v) : next(n), prev(p), val(v) {}
  Node() : Node(nullptr, nullptr, -1) {}
};

class LRUCache {
  int cap, size;
  Node head;
  std::map<int, void*> keys;
  void promote(Node * n) {
    n->next->prev = n->prev;
    n->prev->next = n->next;
    --size;
    addFront(n);
  }
  Node* invalidate_oldest() {
    --size;
    head.prev->prev->next = &head;
    Node* n = head.prev;
    head.prev = n->prev;
    keys.erase(n->pos);
    return n;
  }
  Node* addFront(Node * n) {
    ++size;
    n->next = head.next;
    n->prev = &head;
    head.next->prev = n;
    head.next = n;
    return n;
  }
public:
    LRUCache(int capacity) : cap(capacity), size(0), head(&head, &head, -1) {}
    
    int get(int k) {
      auto itor = keys.find(k);
      if (itor != keys.end()) {
        Node * node = reinterpret_cast<Node*>(itor->second);
        promote(node);
        return node->val;
      } else {
        return -1;
      }
    }
    
    void put(int key, int value) {
      auto itor = keys.find(key);
      Node* node;
      if (itor != keys.end()) {
        node = reinterpret_cast<Node*>(itor->second);
        node->val = value;
        promote(node);
        return;
      }
      if (size == cap) {
        node = invalidate_oldest();
        addFront(node);
      } else {
        node = addFront(new Node);
      }
      itor = keys.insert(std::make_pair(key, node)).first;
      node->pos = itor;
      node->val = value;
    }
};

/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache obj = new LRUCache(capacity);
 * int param_1 = obj.get(key);
 * obj.put(key,value);
 */

int main() {
  LRUCache cache(2);
  cache.put(1, 1);
  cache.put(2, 2);
  std::cout << cache.get(1) << std::endl;       // returns 1
  cache.put(3, 3);    // evicts key 2
  std::cout << cache.get(2) << std::endl;       // returns 1
  cache.put(4, 4);    // evicts key 1
  std::cout << cache.get(1) << std::endl;       // returns 1
  std::cout << cache.get(3) << std::endl;       // returns 1
  std::cout << cache.get(4) << std::endl;       // returns 1
}

