#include <iostream>
#include <string>
#include <vector>

class Solution {
public:
  int longestValidParentheses(const std::string & s) {
    std::vector<std::pair<bool, size_t>> stack(s.size());
    size_t tos = 0, ans = 0, l = 0;
    for (const char c : s) {
      bool b = c == ')';
      if (b) {
        if (tos && !stack[tos - 1].first) {
          --tos;
          size_t nv = l - (tos ? stack[tos - 1].second : -1);
          ans = std::max(ans, nv);
        } else {
          stack[tos++] = std::make_pair(b, l);
        }
      } else {
          stack[tos++] = std::make_pair(b, l);
      }
      ++l;
    }
    return ans;
  }
};

int main() {
  Solution sol;
  std::cout << sol.longestValidParentheses("()(()") << std::endl;
}
