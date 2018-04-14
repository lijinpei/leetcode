/* this is an O(kn) solution.
 * TODO: learn the O(n + klog(n)) solution
 *https://leetcode.com/problems/best-time-to-buy-and-sell-stock-iv/discuss/54118
 */
#include <limits>
#include <vector>

class Solution {
public:
  int maxProfit(int k, std::vector<int> &prices) {
    int n = prices.size();
//seem like this special case is the key point
//https://leetcode.com/problems/best-time-to-buy-and-sell-stock-iv/discuss/54121
    if (2 * k >= n) {
      int ret = 0;
      for (int i = 1; i < n; ++i) {
        ret += std::max(prices[i] - prices[i - 1], 0);
      }
      return ret;
    }
    std::vector<int> b(k + 1, std::numeric_limits<int>::min());
    std::vector<int> s(k + 1, 0);
    for (auto v : prices) {
      for (int i = k; i > 0; --i) {
        s[i] = std::max(s[i], b[i] + v);
        b[i] = std::max(b[i], s[i - 1] - v);
      }
    }
    return s[k];
  }
};
