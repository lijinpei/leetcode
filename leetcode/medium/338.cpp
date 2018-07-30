#include <vector>
class Solution {
public:
  std::vector<int> countBits(int num) {
    ++num;
    std::vector<int> ret(num);
    int i = 1, j = 2;
    if (j <= num) {
      do {
        for (int k = 0; k < i; ++k) {
          ret[k + i] = ret[k] + 1;
        }
        i = j;
        j *= 2;
      } while (i < j && j <= num);
    }
    for (int k = 0, k1 = num - i; k < k1; ++k) {
      ret[k + i] = ret[k] + 1;
    }
    return ret;
  }
};
