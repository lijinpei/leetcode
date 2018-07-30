#include <vector>

class Solution {
public:
  int maxChunksToSorted(const std::vector<int> &arr) {
    int s = arr.size();
    std::vector<int> left_max(s);
    left_max[0] = arr[0];
    for (int i = 1; i < s; ++i) {
      left_max[i] = std::max(arr[i], left_max[i - 1]);
    }
    int right_minimum = arr[s - 1], ans = 0;
    for (int i = s - 2; i >= 0; --i) {
      if (left_max[i] <= right_minimum) {
        ++ans;
      }
      right_minimum = std::min(right_minimum, arr[i]);
    }
    ++ans;
    return ans;
  }
};
