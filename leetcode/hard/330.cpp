#include <iostream>
#include <vector>

class Solution {
public:
  int minPatches(std::vector<int> &nums, int n) {
    int s = nums.size(), v = 0, p = 0, ans = 0;
    while (v >= 0 && n > v) {
      if (p < s && nums[p] <= v + 1) {
        v += nums[p++];
      } else {
        ++ans;
        v += v + 1;
      }
    }
    return ans;
  }
};

/*

class Solution {
public:
  int minPatches(std::vector<int> &nums, int n) {
    int s = nums.size(), p = 0, ans = 0;
    long long v = 0;
    while (n > v) {
      if (p < s && nums[p] <= v + 1) {
        v += nums[p++];
      } else {
        ++ans;
        v += v + 1;
      }
    }
    return ans;
  }
};
 */

int main() {
  Solution sol;
  std::vector<int> input{};
  auto ret = sol.minPatches(input, 7);
  std::cout << ret << std::endl;
}
