#include <vector>
#include <unordered_map>
#include <limits>
#include <cstdint>

class Solution {
public:
  bool isRectangleCover(std::vector<std::vector<int>>& rectangles) {
    std::unordered_map<uint64_t, uint8_t> count;
    int x_min = std::numeric_limits<int>::max(), x_max = std::numeric_limits<int>::min();
    int y_min = x_min, y_max = x_max;
    int odd_count = 0;
    auto C = [&](uint32_t x, uint32_t y) -> uint8_t& {
      return count[uint64_t(x) << 32 | y];
    };
    auto record = [&](int x, int y) {
      x_min = std::min(x_min, x);
      x_max = std::max(x_max, x);
      y_min = std::min(y_min, y);
      y_max = std::max(y_max, y);
      auto & v = C(x, y);
      if (v == 4) {
        return true;
      }
      if (1 & v) {
        --odd_count;
      } else {
        ++odd_count;
      }
      ++v;
      return false;
    };
    int total_area = 0;
    for (auto &r : rectangles) {
      if (record(r[0], r[1]) || record(r[2], r[3]) || record(r[0], r[3]) ||
          record(r[2], r[1])) {
        return false;
      }
      total_area += (r[2] - r[0]) * (r[3] - r[1]);
    }
    return odd_count == 4 &&
           (1 & C(x_min, y_min) & C(x_min, y_max) & C(x_max, y_min) &
            C(x_max, y_max)) &&
           (total_area == (x_max - x_min) * (y_max - y_min));
  }
};
