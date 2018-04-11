#include <vector>
#include <set>

class Solution {
public:
  std::vector<double> medianSlidingWindow(std::vector<int> &nums, int k) {
    int n = nums.size();
    if (!n || !k || k > n) {
      return {};
    }
    std::vector<double> ret(n - k + 1);
    if (k == 1) {
      for (int i = 0; i < n; ++i) {
        ret[i] = nums[i];
      }
      return ret;
    }
    ret.clear();
    std::multiset<int> S;
    S.insert(nums[0]);
    std::multiset<int>::iterator m = S.begin();
    std::vector<std::multiset<int>::iterator> record(k);
    int mv = *m;
    record[0] = m;
    for (int i = 1; i < k; ++i) {
      int v = nums[i];
      record[i] = S.insert(v);
      if ((i & 1) &&  (v < mv)) {
        --m;
        mv = *m;
      }
      if (!(i & 1) && (v >= mv)) {
        ++m;
        mv = *m;
      }
    }
    auto get_ret = [&]() {
      if (k & 1) {
        ret.push_back(mv);
      } else {
        auto m1 = m;
        ++m1;
        ret.push_back((double(mv) + double(*m1)) * 0.5);
      }
    };
    get_ret();
    int k0 = 0;
    for (int i = k; i < n; ++i) {
      auto itor = record[k0];
      int nv = *itor;
      if (k & 1) {
        if (itor == m) {
          --m;
          mv = *m;
          S.erase(itor);
        } else if (nv > mv) {
          S.erase(itor);
          --m;
          mv = *m;
        } else {
          S.erase(itor);
        }
      } else {
        if (itor == m) {
          ++m;
          mv = *m;
          S.erase(itor);
        } else if (nv <= mv) {
          S.erase(itor);
          ++m;
          mv = *m;
        } else {
          S.erase(itor);
        }
      }
      nv = nums[i];
      record[k0] = S.insert(nv);
      if (k & 1) {
        if (nv >= mv) {
          ++m;
          mv = *m;
        }
      } else {
        if (nv < mv) {
          --m;
          mv = *m;
        }
      }
      get_ret();
      ++k0;
      if (k0 == k) {
        k0 = 0;
      }
    }
    return ret;
  }
};

