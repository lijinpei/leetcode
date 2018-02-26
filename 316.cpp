#include <string>
#include <vector>
#include <array>
#include <iostream>

class Solution {
public:
  std::string removeDuplicateLetters(const std::string & str) {
    size_t s = str.size();
    const int C_NUM = 26;
    std::array<bool, C_NUM> in_stack{false};
    std::array<int, C_NUM> left_num{0};
    std::string stack(s, ' ');
    int tos = -1;
    for (const auto & c : str) {
      ++left_num[c - 'a'];
    }
    for (const auto & c : str) {
      int p = c - 'a';
      --left_num[p];
      if (in_stack[p]) {
        continue;
      }
      while (tos >= 0) {
        int p1 = stack[tos] - 'a';
        if (left_num[p1] && p1 >= p) {
          --tos;
          in_stack[p1] = false;
        } else {
          break;
        }
      }
      in_stack[p] = true;
      stack[++tos] = c;
    }
    stack.resize(tos + 1);
    return stack;
  }
};

int main() {
  std::string input("aaa");
  Solution sol;
  auto ret = sol.removeDuplicateLetters(input);
  std::cout << ret << std::endl;
}
