#include <cassert>
#include <iostream>
#include <list>
#include <string>
#include <unordered_map>
#include <utility>

class AllOne {
  std::list<std::pair<int, std::list<std::string>>> buckets;
  std::unordered_map<std::string, std::pair<decltype(buckets)::iterator,
                                            std::list<std::string>::iterator>>
      map;
  decltype(buckets)::iterator bucket1;
  void self_check() {
    return;
    std::cerr << "self check start\n";
    for (auto b : buckets) {
      std::cerr << b.first << std::endl;
      for (auto s : b.second) {
        std::cerr << s << ' ';
      }
      std::cerr << std::endl;
    }
    std::cerr << "dump buckets finish\n";
    for (auto m : map) {
      std::cerr << m.first << ' ';
    }
    std::cerr << "\nself check finish\n";
  }

public:
  /** Initialize your data structure here. */
  AllOne() {
    buckets.push_back({1, {}});
    bucket1 = buckets.begin();
  }

  /** Inserts a new key <Key> with value 1. Or increments an existing key by 1.
   */
  void inc(const std::string &key) {
    auto itor = map.find(key);
    if (itor == map.end()) {
      map[key] = {bucket1, bucket1->second.insert(bucket1->second.end(), key)};
    } else {
      auto old_itor = itor->second.first;
      itor->second.first->second.erase(itor->second.second);
      auto b1 = itor->second.first == buckets.end()
                    ? buckets.end()
                    : std::next(itor->second.first);
      if (b1 == buckets.end() || b1->first != itor->second.first->first + 1) {
        b1 = buckets.insert(b1, {itor->second.first->first + 1, {}});
      }
      itor->second.first = b1;
      itor->second.second = b1->second.insert(b1->second.end(), key);
      if (old_itor->second.empty() && old_itor != bucket1) {
        buckets.erase(old_itor);
      }
    }
  }

  /** Decrements an existing key by 1. If Key's value is 1, remove it from the
   * data structure. */
  void dec(const std::string &key) {
    auto itor = map.find(key);
    if (itor == map.end()) {
      return;
    }
    itor->second.first->second.erase(itor->second.second);
    auto old_itor = itor->second.first;
    if (itor->second.first == bucket1) {
      map.erase(itor);
      return;
    } else {
    }
    if (itor->second.first == buckets.begin() ||
        std::prev(itor->second.first)->first + 1 != itor->second.first->first) {
      itor->second.first = buckets.insert(itor->second.first,
                                          {itor->second.first->first - 1, {}});
    } else {
      itor->second.first = std::prev(itor->second.first);
    }
    itor->second.second = itor->second.first->second.insert(
        itor->second.first->second.end(), key);
    if (old_itor->second.empty() && old_itor != bucket1) {
      buckets.erase(old_itor);
    }
  }

  /** Returns one of the keys with maximal value. */
  std::string getMaxKey() {
    for (auto itor = buckets.rbegin(); itor != buckets.rend();
         itor = std::next(itor)) {
      if (!itor->second.empty()) {
        return *itor->second.begin();
      }
    }
    return "";
  }

  /** Returns one of the keys with Minimal value. */
  std::string getMinKey() {
    for (auto itor = buckets.begin(); itor != buckets.end();
         itor = std::next(itor)) {
      if (!itor->second.empty()) {
        return *itor->second.begin();
      }
    }
    return "";
  }
};

int main() {
  AllOne a1;
  for (int i = 0; i < 100; ++i) {
    a1.inc("a");
  }
  for (int i = 0; i < 10; ++i) {
    a1.inc("b");
  }
  for (int i = 0; i < 10; ++i) {
    a1.inc("c");
  }
  for (int i = 0; i < 10; ++i) {
    a1.dec("c");
  }
  std::cerr << a1.getMaxKey() << std::endl;
  std::cerr << a1.getMinKey() << std::endl;
  std::cerr << "finish\n";
}
