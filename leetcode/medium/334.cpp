#include <vector>
#include <limits>

class Solution {
public:
  bool increasingTriplet(std::vector<int> &nums) {
    int n = nums.size();
    if (n < 3) {
      return false;
    }
    int v1 = std::numeric_limits<int>::max(), v2 = v1;
    for (auto v : nums) {
      if (v > v2) {
        return true;
      }
      if (v <= v1) {
        v1 = v;
      } else if (v < v2) {
        v2 = v;
      }
    }
    return false;
  }
};
