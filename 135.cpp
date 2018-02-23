#include <vector>
#include <iostream>

class Solution {
public:
  int candy(const std::vector<int>& ratings) {
    int s = ratings.size();
    auto find_descending = [&](int p) {
      int r = ratings[p];
      for (p = p + 1; p < s && ratings[p] < r; ++p) {
        r = ratings[p];
      }
      return p - 1;
    };
    auto find_ascending = [&](int p) {
      int r = ratings[p];
      for (p = p + 1; p < s && ratings[p] > r; ++p) {
        r = ratings[p];
      }
      return p - 1;
    };
    auto sum = [](int n) {
      return (1 + n) * n / 2;
    };
    if (s == 1) {
      return 1;
    }
    int ans = 0, p = 0;
    while (p < s) {
      int p1 = find_ascending(p);
      int p2 = find_descending(p1);
      ans += std::max(p1 - p, p2 - p1) + 1;
      ans += sum(p1 - p) + sum(p2 - p1);
      if (p2 + 1 == s) {
        break;
      }
      if (ratings[p2 + 1] > ratings[p2]) {
        --ans;
        p = p2;
      } else {
        int r = ratings[p2];
        for (p = p2 + 1; p < s && ratings[p] == r; ++p) {
          ++ans;
        }
        --ans;
        --p;
      }
    }
    return ans;
  }
};

