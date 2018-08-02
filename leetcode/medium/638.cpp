#include <vector>
#include <iostream>

class Solution {
  class SolutionImpl {
    std::vector<int> &price;
    std::vector<std::vector<int>> &special;
    std::vector<int> &needs;
    std::vector<int> dp;

    int index(const std::vector<int> & v) {
      int mul = 1;
      int ret = 0;
      for (int i = needs.size() - 1; i >= 0; --i) {
        ret += mul * v[i];
        if (needs[i]) {
          mul *= needs[i];
        }
      }
      return ret;
    }
    int calc(const std::vector<int> & v) {
      int idx = index(v);
      if (dp[idx] >= 0) {
        return dp[idx];
      }
      int ret = 0, s = needs.size();
      for (int i = 0; i < s; ++i) {
        ret += price[i] * v[i];
      }
//      std::cout << "original price: " << ret << std::endl;
      std::vector<int> v1(v.size());
      for (int i = 0, k = special.size(); i < k; ++i) {
        int j = 0;
        for (; j < s; ++j) {
          if (v[j] >= special[i][j]) {
            v1[j] = v[j] - special[i][j];
          } else {
            break;
          }
        }
        if (j == s) {
          int nv = calc(v1) + special[i][s];
          if (nv < ret) {
            ret = nv;
          }
        }
      }
      /*
      for (int i = 0; i < s; ++i) {
        std::cout << v[i] << ' ';
      }
      std::cout << " : " << ret << std::endl;
      */
      return dp[idx] = ret;
    }
  public:
    SolutionImpl(std::vector<int> &price, std::vector<std::vector<int>> &special,
                     std::vector<int> &needs) : price(price), special(special), needs(needs) {
      dp.resize(index(needs) + 1, -1);
    }
    int calc() {
      return calc(needs);
    }
  };

public:
  int shoppingOffers(std::vector<int> &price, std::vector<std::vector<int>> &special,
                     std::vector<int> &needs) {
    return SolutionImpl(price, special, needs).calc();
  }
};
