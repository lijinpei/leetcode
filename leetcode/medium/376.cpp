#include <vector>

class Solution {
public:
    int wiggleMaxLength(std::vector<int>& nums) {
      int s = nums.size();
      if (s <= 1) {
        return s;
      }
      int p = 0, ans = 1;
      auto find_decrease = [&]() {
        bool ret = false;
        int v0 = nums[p++];
        while (p < s) {
          int v1 = nums[p];
          if (v1 == v0) {
            ++p;
          } else if (v1 < v0) {
            v0 = v1;
            ret = true;
            ++p;
          } else {
            --p;
            return ret;
          }
        }
        return ret;
      };
      auto find_increase = [&]() {
        bool ret = false;
        int v0 = nums[p++];
        while (p < s) {
          int v1 = nums[p];
          if (v1 == v0) {
            ++p;
          } else if (v1 > v0) {
            v0 = v1;
            ret = true;
            ++p;
          } else {
            --p;
            return ret;
          }
        }
        return ret;
      };
      while (p + 1 < s) {
        if (find_increase()) {
          ++ans;
        }
        if (p + 1 == s) {
          break;
        }
        if (find_decrease()) {
          ++ans;
        }
      }
      return ans;
    }
};
