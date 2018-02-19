#include <iostream>
#include <string>
#include <vector>

class Solution {
public:
  int longestValidParentheses(const std::string & str) {
    int ret = 0, s = str.size();
    int left = 0, right = 0;
    for (int i = 0; i < s; ++i) {
      if (str[i] == ')') {
        ++right;
      } else {
        ++left;
      }
      if (left == right) {
        ret = std::max(ret, left + right);
      }
      if (right > left) {
        left = right = 0;
      }
    }
    left = right = 0;
    for (int i = s - 1; i >= 0; --i) {
      if (str[i] == ')') {
        ++right;
      } else {
        ++left;
      }
      if (left == right) {
        ret = std::max(ret, left + right);
      }
      if (left > right) {
        left = right = 0;
      }
    }
    return ret;
  }
};

int main() {
  Solution sol;
  std::cout << sol.longestValidParentheses("()(()") << std::endl;
}
