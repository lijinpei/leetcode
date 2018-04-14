#include <vector>
#include <algorithm>

/*
 * https://leetcode.com/problems/best-time-to-buy-and-sell-stock-iii/discuss/39611/
 * explanation:
 * consider 4 cases:
 * we have buy one stock, but haven't sell it: b1
 * we have buy one, and sell it: s1
 * buy one, sell one, then buy one: b2
 * buy one, sell it, then buy another and sell it
 * count buy as minus, sell as plus
 * another tricky point is the initialization:
 * b2/b1 = 0, this means,
 * 1. b1 can be zero, so b1 is in fact one or zero transaction, b2 is at most
 * two transaction. and if we don't have enough stock to sell/buy, we can get
 * zero profits
 * 2. s1/s2 can be zero, because zero is valid stock price, they should be
 * extreme low value, so that once we have normal values, they are leave out.
 */

class Solution {
public:
  int maxProfit(std::vector<int> &prices) {
    int b1 = std::numeric_limits<int>::min(), s1 = 0, b2 = b1, s2 = 0;
    for (auto p : prices) {
      b1 = std::max(b1, -p);
      s1 = std::max(s1, p + b1);
      b2 = std::max(b2, s1 - p);
      s2 = std::max(s2, p + b2);
    }
    return s2;
  }
};
