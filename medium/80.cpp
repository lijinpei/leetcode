#include <vector>

class Solution {
public:
  int removeDuplicates(std::vector<int>& nums) {
    int n = nums.size();
    if (n <= 2) {
      return n;
    }
    int lv = nums[0], lp = 0, li = 0;
    for (int i = 1 ; i < n; ++i) {
      int nv = nums[i];
      if (nv == lv) {
          for (int i1 = li; i1 <= i; ++i1) {
            nums[lp++] = nums[i1];
          }
          for (++i; i < n && nums[i] == lv; ++i) {
            continue;
          }
          if (i == n) {
            li = n;
            break;
          } else {
            lv = nums[i];
            li = i;
            continue;
          }
      } else {
        lv = nv;
      }
    }
    for (; li < n; ++li) {
      nums[lp++] = nums[li];
    }
    return lp;
  }
};
