#include <vector>
#include <string>
#include <list>
#include <utility>
#include <unordered_set>

class Solution {
public:
  int openLock(std::vector<std::string>& deadends, std::string target) {
    std::unordered_set<std::string> s1, s2;
    for (const auto & s : deadends) {
      s1.insert(s);
    }
    std::list<std::pair<std::string, int>> queue;
    std::string start = "0000";
    if (s1.find(target) != s1.end()) {
      return -1;
    }
    if (s1.find(start) != s1.end()) {
      return -1;
    }
    if (start == target) {
      return 0;
    }
    queue.push_back({start, 0});
    s2.insert(start);
    int sn = target.size();
    auto f1 = [](char c) -> char {
      if (c == '9') {
        return '0';
      }
      return c + 1;
    };
    auto f2 = [](char c) -> char {
      if (c == '0') {
        return '9';
      }
      return c - 1;
    };
    while (!queue.empty()) {
      std::string s = std::move(queue.front().first);
      int d = queue.front().second;
      queue.pop_front();
      for (int i = 0; i < sn; ++i) {
        char c = s[i];
        s[i] = f1(c);
        if (s == target) {
          return d + 1;
        }
        if (s1.find(s) == s1.end()) {
          if (s2.insert(s).second) {
            queue.emplace_back(s, d + 1);
          }
        }
        s[i] = f2(c);
        if (s == target) {
          return d + 1;
        }
        if (s1.find(s) == s1.end()) {
          if (s2.insert(s).second) {
            queue.emplace_back(s, d + 1);
          }
        }
        s[i] = c;
      }
    }
    return -1;
  }
};
