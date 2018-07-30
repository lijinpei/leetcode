#include <iostream>
#include <vector>

class Solution {
public:
  bool circularArrayLoop(std::vector<int> &nums) {
    int n = nums.size();
    bool direction;
    for (int i = 0; i < n; ++i) {
      if (!nums[i]) {
        continue;
      }
      direction = nums[i] > 0;
      int m = i;
      int ln = 0;
      while (true) {
        int mv = nums[m];
        if (mv == 0 || direction ^(mv > 0)) {
          break;
        }
        int m1 = m + nums[m];
        while (m1 < 0) {
          m1 += n;
        }
        while (m1 >= n) {
          m1 -= n;
        }
        if (m == m1) {
          break;
        } else {
          ++ln;
          if (ln >= n) {
            return true;
          }
        }
        m = m1;
      }
      // not a loop, now mark them zero
      int m1 = i;
      while (m1 != m) {
        int m2 = m1 + nums[m1];
        nums[m1] = 0;
        while (m2 < 0) {
          m2 += n;
        }
        while (m2 >= n) {
          m2 -= n;
        }
        m1 = m2;
      }
    }
    return false;
  }
};

int main() {
  Solution sol;
  std::vector<int> input{-1, 2};
  sol.circularArrayLoop(input);
}
