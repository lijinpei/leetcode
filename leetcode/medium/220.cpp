#include <algorithm>
#include <cstdint>
#include <set>
#include <vector>

class Solution {
public:
  bool containsNearbyAlmostDuplicate(std::vector<int> &nums, int k, int t) {
    if (k <= 0 || t < 0) {
      return false;
    }
    int l = nums.size();
    std::multiset<int> bt;
    std::vector<std::multiset<int>::iterator> bt_itors(k);
    int i, j = std::min(k, l);
    bt_itors[0] = bt.insert(nums[0]);
    for (i = 1; i < j; ++i) {
      int64_t v = nums[i];
      auto itor = bt.insert(v), itor1 = itor, itor2 = itor;
      --itor1;
      ++itor2;
      if (itor1 != bt.end() && (v - *itor1 <= t)) {
        return true;
      }
      if (itor2 != bt.end() && (*itor2 - v <= t)) {
        return true;
      }
      bt_itors[i] = itor;
    }
    int p = j;
    for (; i < l; ++i, ++p) {
      if (p == k) {
        p = 0;
      }
      int64_t v = nums[i];
      auto itor = bt.insert(v), itor1 = itor, itor2 = itor;
      --itor1;
      ++itor2;
      if (itor1 != bt.end() && (v - *itor1 <= t)) {
        return true;
      }
      if (itor2 != bt.end() && (*itor2 - v <= t)) {
        return true;
      }
      bt.erase(bt_itors[p]);
      bt_itors[p] = itor;
    }
    return false;
  }
};

