#include <iostream>
#include <vector>
#include <utility>

class Solution {
public:
  bool find132pattern(const std::vector<int> &nums) {
    int n = nums.size();
    if (!n) {
      return false;
    }
    std::vector<std::pair<int, int>> stack(n / 2);
    int tos = 0;
    int min = nums[0];
    for (int i = 1; i < n; ++i) {
      int v = nums[i];
      if (v <= min) {
        min = v;
      } else {
        while (tos) {
          int v1 = stack[tos - 1].first;
          int v2 = stack[tos - 1].second;
          if (v >= v2) {
            --tos;
            continue;
          } else if (v > v1) {
            return true;
          } else {
            break;
          }
        }
        stack[tos++] = {min, v};
      }
    }
    return false;
  }
};

int main() {
  Solution sol;
  std::vector<int> input{3, 1, 4, 2};
  std::cout << sol.find132pattern(input);
}
