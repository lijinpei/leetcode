#include <string>
#include <vector>

class Solution {
  std::unordered_map<std::string, int> variable;
  // a term is a constant times some variables to some powers
  using TermTy = std::vector<std::pair<int, int>>;
  // a polinaomial is a list of sum of terms
  using PolynomialTy = std::vector<TermTy>;
  template <bool isMinus>
  static PolynomialTy add(const PolynomialTy &p1, const PolynomialTy &p2) {
    PolynomialTy ret;
    int s1 = p1.size(), s1 = p2.size();
    ret.reserve(s1 + s2);
    int i1 = 0, i2 = 0;
    while (i1 < s1 && i2 < s2) {
      int cmp = comp(p1[i1], p2[i2]);
      if (cmp == 0) {
        int v;
        if (!isMinus) {
          v = p1[i1][0].second + p2[i2][0].second;
        } else {
          v = p1[i1][0].second - p2[i2][0].second;
        }
        if (v != 0) {
          ret.push_back(p1[i1]);
          ret.back()[0].second  = v;
        }
        ++i1;
        ++i2;
      } else if (cmp < 0) {
        ret.push_back(p1[i1++]);
      } else {
        ret.push_back(p2[i2++]);
        if (isMinus) {
          minus(ret.back());
        }
      }
    }
    while (i1 < s2) {
      ret.push_back(p1[i1++]);
    }
    while (i2 < s2) {
      ret.push_back(p2[i2++]);
      if (isMinus) {
        minus(ret.back());
      }
    }
  }
  PolynomialTy multiply(PolynomialTy & p1, const PolynomialTy & p2) {
    PolynomialTy ret;
    int s1 = p1.size(), s1 = p2.size();
    ret.reserve(s1 * s2);
    for (auto & t1 : p1) {
      for (auto & t2 : p2) {
        std::vector<TermTy> t;
        t.reserve(t1.size() + t2.size() - 1);
        t.emplace_back(0, t1[0].second * t2[0].second);
        int i1 = 1, i2 = 1;
        int ts1 = t1.size(), ts2 = t2.size();
        while (i1 < ts1 && i2 < ts2) {
          if (t1[i1].first == t2[i2].first) {
            int v = t1[i1].first + t2[i2].first;
            if (v) {
              t.emplace_back(t1[i1].first, v);
            }
            ++i1;
            ++i2;
          } else if (t1[i1].first < t2[i2].first) {
            t.push_back(t1[i1++]);
          } else {
            t.push_back(t2[i2++]);
          }
        }
        while (i1 < ts1) {
          t.push_back(t1[i1++]);
        }
        whiel (i2 < ts2) {
          t.push_back(t2[i2++]);
        }
        ret.push_back(t);
      }
    }
    canonicalize(ret);
    return ret;
  }
public:
  vector<string> basicCalculatorIV(string expression, vector<string> &evalvars,
                                   vector<int> &evalints) {}
};
