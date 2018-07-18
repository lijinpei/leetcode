#include <vector>

class Solution {
public:
  std::vector<int> asteroidCollision(std::vector<int> &asteroids) {
    enum {
      OldExplode,
      NewExplode,
      BothExplode,
      BothLive
    };
    int n = asteroids.size();
    std::vector<int> ret(n);
    ret.resize(0);
    auto meet = [](int oa, int na) {
      if (na < 0) {
        if (oa < 0) {
          return BothLive;
        }
        int nv = na + oa;
        if (!nv) {
          return BothExplode;
        } else if (nv > 0) {
          return NewExplode;
        } else {
          return OldExplode;
        }
      } else {
        return BothLive;
      }
    };
    for (auto a : asteroids) {
      while (true) {
        if (ret.empty()) {
          ret.push_back(a);
          break;
        }
        auto r = meet(ret.back(), a);
        if (r == OldExplode) {
          ret.pop_back();
          continue;
        }
        if (r == NewExplode) {
          break;
        }
        if (r == BothExplode) {
          ret.pop_back();
          break;
        }
        if (r == BothLive) {
          ret.push_back(a);
          break;
        }
      }
    }
    return ret;
  }
};
