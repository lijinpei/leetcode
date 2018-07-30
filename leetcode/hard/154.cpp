#include <iostream>
#include <vector>
#include <functional>
#include <algorithm>

class Solution {
public:
  int findMin(std::vector<int> &nums) {
    int s = nums.size();
    int v1 = nums[0];
    int p = s - 1;
    for (; p > 0; --p) {
      if (nums[p] < v1) {
        break;
      }
    }
    if (!p) {
      return v1;
    }
    return *std::upper_bound(nums.begin(), nums.begin() + p + 1, v1, std::greater<int>());
  }
};

int main() {
  Solution sol;
  std::vector<int> input{3, 1};
  auto ret = sol.findMin(input);
  std::cout << ret << std::endl;
}
