#include <vector>
#include <numeric>

class Solution {
  std::vector<int> sol;
  std::vector<std::vector<int>> ret;
  void search(std::vector<int> & nums, int p, int v1) {
    int sn = nums.size();
    if (sol.size() >= 2) {
      ret.push_back(sol);
    }
    int s = sol.size();
    for (int i = p; i < sn; ++i) {
      int v = nums[i];
      if (v <= v1) {
        continue;
      }
      bool before = false;
      for (int j = p; j < i; ++j) {
        if (nums[j] == v) {
          before = true;
          break;
        }
      }
      if (before) {
        continue;
      }
      for (int j = i; j < sn; ++j) {
        if (nums[j] == v) {
          sol.push_back(v);
          search(nums, j + 1, v);
        }
      }
      sol.resize(s);
    }
  }
public:
  std::vector<std::vector<int>> findSubsequences(std::vector<int>& nums) {
    search(nums, 0, -101);
    return ret;
  }
};

int main() {
  std::vector<int> input(15);
  std::iota(input.begin(), input.end(), 1);
  for (int i = 0; i < 100; ++i) {
    Solution sol;
    sol.findSubsequences(input);
  }
}
