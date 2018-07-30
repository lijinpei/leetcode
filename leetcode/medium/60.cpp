#include <string>
#include <vector>

class Solution {
public:
  std::string getPermutation(int n, int k) {
    --k;
    std::vector<int> factorial(n);
    factorial[0] = 1;
    for (int i = 1; i < n; ++i) {
      factorial[i] = i * factorial[i - 1];
    }
    std::vector<bool> used(n, false);
    std::string ret(n, ' ');
    for (int i = 0; i < n; ++i) {
      int v = k / factorial[n - 1 - i];
      k = k % factorial[n - 1 - i];
      ++v;
      int j = 0;
      while (j < n && v) {
        if (!used[j]) {
          --v;
        }
        ++j;
      }
      used[j - 1] = true;
      ret[i] = '0' + j;
    }
    return ret;
  }
};
