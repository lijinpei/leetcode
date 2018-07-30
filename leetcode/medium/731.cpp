#include <map>

class MyCalendarTwo {
  std::map<int, int> map;
public:
  MyCalendarTwo() {}
  bool book(int start, int end) {
    auto ret1 = map.insert(std::make_pair(start, 1));
    if (!ret1.second) {
      ret1.first->second += 1;
    }
    auto ret2 = map.insert(std::make_pair(end, -1));
    if (!ret2.second) {
      ret2.first->second -= 1;
    }
    bool can_insert = true;
    int n = 0;
    for (auto kv : map) {
      n += kv.second;
      if (n > 2) {
        can_insert = false;
        break;
      }
    }
    if (!can_insert) {
      if (ret1.second) {
        map.erase(ret1.first);
      } else {
        ret1.first->second -= 1;
      }
      if (ret2.second) {
        map.erase(ret2.first);
      } else {
        ret2.first->second += 1;
      }
      return false;
    } else {
      return true;
    }
  }
};
