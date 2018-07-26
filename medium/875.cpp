#include <vector>

class Solution {
public:
  int minEatingSpeed(std::vector<int>& piles, int H) {
    int s = piles.size();
    int max = piles[0];
    for (int i = 1; i < s; ++i) {
      if (piles[i] > max) {
        max = piles[i];
      }
    }
    int min = 1;
    auto ok = [&](int v) {
      int n = 0;
      for (auto p : piles) {
         n += (p - 1) / v + 1;
         if (n > H) {
           return false;
         }
      }
      return true;
    };
    while (max > min) {
      int m = (max + min) / 2;
      if (ok(m)) {
        max = m;
      } else {
        min = m + 1;
      }
    }
    return max;
  }
};
