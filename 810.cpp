#include <vector>

class Solution {
public:
  bool xorGame(std::vector<int> &nums) {
    int v = 0;
    for (auto v1 : nums) {
      v ^= v1;
    }
    if (!v) {
      return true;
    }
    bool b  = false;
    for (auto v1 : nums) {
      if (v ^ v1) {
        b = true;
        break;
      }
    }
    return b && !(nums.size() & 1);
  }
};
