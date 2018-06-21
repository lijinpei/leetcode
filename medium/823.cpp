#include <map>
#include <vector>
#include <algorithm>
#include <cstdint>

class Solution {
  static constexpr int MOD = 1000000007;
public:
  int numFactoredBinaryTrees(std::vector<int> &A) {
    std::map<int, int> num;
    std::sort(A.begin(), A.end());
    int ans = 0;
    for (int i = 0, s = A.size(); i < s; ++i) {
      int a = A[i];
      int & n = num[a];
      for (int j = 0; j < i; ++j) {
        int aj = A[j];
        int aj1 = a / aj, aj2 = a % aj;
        if (aj1 < aj) {
          break;
        }
        if (aj2) {
          continue;
        }
        if (aj == aj1) {
          int64_t n1 = num[aj];
          n = (n + n1 * n1) % MOD;
          break;
        }
        int64_t n1 = num[aj];
        auto ret = num.find(aj1);
        if (ret != num.end()) {
          n = (n + 2 * n1 * ret->second) % MOD;
        }
      }
      n = (n + 1) % MOD;
      ans = (ans + n) % MOD;
    }
    return ans;
  }
};
