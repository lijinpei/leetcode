#include <iostream>
#include <list>
#include <unordered_map>

class LFUCache {
  class Bucket;
  struct Node {
    int key, val;
    std::list<Bucket *>::iterator bucket;
    Node(int key, int val, std::list<Bucket *>::iterator bucket)
        : key(key), val(val), bucket(bucket) {}
  };
  struct Bucket {
    int freq;
    std::list<Node> nodes;
    Bucket(int freq) : freq(freq) {}
  };
  std::list<Bucket *> buckets;
  std::unordered_map<int, std::list<Node>::iterator> map;
  int capacity, number;

  std::list<Node>::iterator addBefore(int freq, int key, int val,
                                      std::list<Bucket *>::iterator itor) {
    if (itor == buckets.end() || (*itor)->freq != freq) {
      Bucket *new_bucket = new Bucket(freq);
      //std::cerr << "new " << new_bucket << std::endl;
      auto new_itor = buckets.insert(itor, new_bucket);
      auto &nodes = new_bucket->nodes;
      return nodes.emplace(nodes.end(), key, val, new_itor);
    } else {
      auto &nodes = (*itor)->nodes;
      return nodes.emplace(nodes.end(), key, val, itor);
    }
  }

  void promote(std::list<Node>::iterator &itor, int key, int val) {
    auto this_itor = itor->bucket;
    Bucket *this_bucket = *this_itor;
    int freq1 = this_bucket->freq + 1;
    auto next_itor = std::next(this_itor);
    if (this_bucket->nodes.size() == 1 &&
        (next_itor == buckets.end() || (*next_itor)->freq != freq1)) {
      ++(this_bucket->freq);
    } else {
      this_bucket->nodes.erase(itor);
      if (this_bucket->nodes.empty()) {
        //std::cerr << "delete " << *this_itor << std::endl;
        delete *this_itor;
        buckets.erase(this_itor);
      }
      itor = addBefore(freq1, key, val, next_itor);
    }
  }

  void makeRoom() {
    auto &nodes = (*buckets.begin())->nodes;
    int key = nodes.begin()->key;
    map.erase(key);
    nodes.erase(nodes.begin());
    if (nodes.empty()) {
      //std::cerr << "delete " << *buckets.begin() << std::endl;
      delete *buckets.begin();
      buckets.erase(buckets.begin());
    }
  }

public:
  LFUCache(int cap) : capacity(cap), number(0) { map.reserve(capacity); }

  int get(int key) {
    if (!capacity) {
      return -1;
    }
    auto itor = map.find(key);
    if (itor != map.end()) {
      int ret = itor->second->val;
      promote(itor->second, key, ret);
      return ret;
    } else {
      return -1;
    }
  }

  void put(int key, int value) {
    if (!capacity) {
      return;
    }
    auto itor = map.find(key);
    if (itor != map.end()) {
      itor->second->val = value;
      promote(itor->second, key, value);
    } else {
      if (number == capacity) {
        makeRoom();
      } else {
        ++number;
      }
      auto itor = buckets.begin();
      if (itor == buckets.end() || (*itor)->freq != 1) {
        Bucket *new_bucket = new Bucket(1);
        //std::cerr << "new " << new_bucket << std::endl;
        itor = buckets.insert(itor, new_bucket);
      }
      auto itor1 =
          (*itor)->nodes.emplace((*itor)->nodes.end(), key, value, itor);
      map[key] = itor1;
    }
  }
  ~LFUCache() {
    for (auto b : buckets) {
      delete b;
    }
  }

  void dump() {
    auto contains = [&](Node n) {
      for (auto n1 : (*n.bucket)->nodes) {
        if (n1.key == n.key) {
          return true;
        }
      }
      return false;
    };
    for (auto b : buckets) {
      std::cout << b->freq << ": ";
      for (auto n : b->nodes) {
        std::cout << n.key << ':' << n.val << ':' << contains(n) << ' ';
      }
      std::cout << std::endl;
    }
    std::cout << std::endl;
  }
};

int main() {
  LFUCache cache(2);
  cache.put(3, 1);
  cache.put(2, 1);
  cache.put(2, 2);
  std::cout << cache.get(1) << std::endl;
  cache.put(3, 3);
  std::cout << cache.get(2) << std::endl;
  std::cout << cache.get(3) << std::endl;
  cache.put(4, 4);
  std::cout << cache.get(1) << std::endl;
  std::cout << cache.get(3) << std::endl;
  cache.dump();
  std::cout << cache.get(4) << std::endl;
}
