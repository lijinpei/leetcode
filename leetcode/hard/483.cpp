#include <string>
#include <cstdint>
#include <limits>

class Solution {
public:
  std::string smallestGoodBase(const std::string & n_) {
    int64_t n = std::stoll(n_);
    auto ok = [&](int64_t k) -> int64_t {
      auto nv = [&](int64_t b) -> int64_t {
        int64_t ret = 1;
        int64_t max = (std::numeric_limits<int64_t>::max() - 1) / b;
        for (int i = 2; i < k; ++i) {
          if (ret >= max) {
            return -1;
          }
          ret = ret * b + 1;
        }
        return ret;
      };
      int64_t l = 2;
      int64_t h = n;
      int64_t v;
      while (l < h) {
        int64_t m = l + (h - l) / 2;
        v = nv(m);
        if (v == n) {
          return m;
        }
        if (v < 0 || v > n) {
          h = m;
        } else {
          l = m + 1;
        }
      }
      return 0;
    };
    for (int i = 63; i >= 1; --i) {
      int64_t ret = ok(i);
      if (ret) {
        return std::to_string(ret);
      }
    }
    return "";
  }
};
