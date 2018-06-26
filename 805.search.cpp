#include <vector>
#include <numeric>
#include <algorithm>

class Solution {
  static bool search(int p, int n, int s, const std::vector<int> & A) {
    if (n == 1) {
      return std::find(A.begin() + p, A.end(), s) != A.end();
    }
    for (int sz = A.size(); p + n <= sz; ++p) {
      if (A[p] * n > s) {
        return false;
      }
      if (search(p + 1, n - 1, s - A[p], A)) {
        return true;
      }
    }
    return false;
  }
public:
  bool splitArraySameAverage(std::vector<int> &A) {
    int n = A.size();
    int sum = std::accumulate(A.begin(), A.end(), 0);
    std::sort(A.begin(), A.end());
    for (int i = 1, ie = n / 2; i <= ie; ++i) {
      int v1 = (sum * i) % n;
      if (v1) {
        continue;
      }
      int v2 = (sum * i) / n;
      if (search(0, i, v2, A)) {
        return true;
      }
    }
    return false;
  }
};

