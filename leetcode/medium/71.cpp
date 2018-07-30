#include <iostream>
#include <string>
#include <vector>
#include <utility>

class Solution {
public:
  std::string simplifyPath(std::string path) {
    std::vector<std::pair<int, int>> stack;
    stack.reserve(path.size() / 2);
    int lp = 1;
    for (int i = 1, s = path.size(); i <= s; ++i) {
      if (i != s && path[i] != '/') {
        continue;
      }
      int l = lp;
      lp = i + 1;
      if (i == l) {
        continue;
      }
      if (i == l + 1 &&  path[l] == '.') {
        continue;
      }
      if (i == l + 2 && path[l] == '.' && path[l + 1] == '.') {
        if (!stack.empty()) {
          stack.pop_back();
        }
        continue;
      }
      stack.emplace_back(l, i);
    }
    if (stack.empty()) {
      return "/";
    }
    int l = 0;
    for (int i = 0, s = stack.size(); i < s; ++i) {
      int p1 = stack[i].first;
      int l1 = stack[i].second - p1;
      path[l] = '/';
      for (int i = 0; i < l1; ++i) {
        path[l + 1 + i] = path[p1 + i];
      }
      l += l1 + 1;
    }
    return path.substr(0, l);
  }
};

int main() {
  Solution sol;
  auto ret = sol.simplifyPath("/home//foo/");
  std::cout << ret << std::endl;
}
