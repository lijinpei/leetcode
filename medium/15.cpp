#include <iostream>
#include <vector>
#include <algorithm>

class Solution {
public:
  std::vector<std::vector<int>> threeSum(std::vector<int> &nums) {
    if (nums.size() < 3) {
      return {};
    }
    std::sort(nums.begin(), nums.end());
    //nums.resize(std::distance(nums.begin(), std::unique(nums.begin(), nums.end())));
    /*
    for (auto v : nums) {
      std::cout << v << ' ';
    }
    std::cout << std::endl;
    */
    int li = nums[0] - 1;
    std::vector<std::vector<int>> ret;
    int n = nums.size();
    for (int i = 0; i < n; ++i) {
      int si = nums[i];
      if (si == li) {
        continue;
      } else {
        li = si;
      }
      int k = n - 1;
      int lj = nums[i + 1] - 1;
      for (int j = i + 1; j < n; ++j) {
        int sj = nums[j];
        if (sj == lj) {
          continue;
        } else {
          lj = sj;
        }
        int s = si + sj;
        while (k > j && s + nums[k] > 0) {
          --k;
        }
        if (k <= j) {
          break;
        }
        if (s + nums[k] == 0) {
          ret.push_back({nums[i], nums[j], nums[k]});
        }
      }
    }
    return ret;
  }
};

int main() {
  Solution sol;
  std::vector<int> input{-4,-2,-2,-2,0,1,2,2,2,3,3,4,4,6,6};
  auto ret = sol.threeSum(input);
  for (auto & v1 : ret) {
    for (auto v : v1) {
      std::cout << v << ' ';
    }
    std::cout << std::endl;
  }
}
