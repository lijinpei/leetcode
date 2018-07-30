#include <iostream>
#include <cstdint>
#include <limits>

class Solution {
public:
  int reachNumber(int target) {
    auto bsearch = [](uint32_t t) {
      uint32_t l = 1;
      uint32_t h = std::numeric_limits<uint16_t>::max();
      while (l != h) {
        //std::cout << l << ' ' << h << std::endl;
        uint32_t m = (l + h) / 2;
        uint32_t v = m * (m + 1);
        if (v == t) {
          return m;
        }
        if (v > t) {
          h = m;
        } else {
          l = m + 1;
        }
      }
      return l;
    };
    if (!target) {
      return 0;
    }
    uint32_t t;
    if (target < 0) {
      t = -target;
    } else {
      t = target;
    }
    uint32_t n = bsearch(2 * t);
    uint32_t v = n * (n + 1) / 2;
    uint32_t d = v - t;
    if (!(d & 1)) {
      return n;
    } else {
      if (n & 1) {
        return n + 2;
      } else {
        return n + 1;
      }
    }
  }
};

int main() {
  Solution sol;
  std::cout << sol.reachNumber(1);
}
