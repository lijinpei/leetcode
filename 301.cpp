#include <iostream>
#include <vector>
#include <string>

class Solution {
};

int main() {
  Solution sol;
  auto ret = sol.removeInvalidParentheses("())())))");
  std::cerr << "ans:\n";
  for (const auto & v : ret) {
    std::cout << v << std::endl;
  }
}
