#include <iostream>

class Solution {
public:
  int findKthNumber(int M, int N, int k) {
    int l = 1, h = M * N;
    while (l < h) {
      int m = l + (h - l) / 2;
      int r1, p1, s1, v1, v2;
      if (m > N) {
        r1 = m / N;
        p1 = N;
        s1 = r1 * N;
      } else {
        r1 = 1;
        p1 = m;
        s1 = m;
      }
      v1 = r1 * p1;
      v2 = v1;
      while (v1 && r1 < M) {
        ++r1;
        v1 += p1;
        while (v1 > m) {
          --p1;
          v1 -= r1;
        }
        s1 += p1;
        if (v1 > v2) {
          v2 = v1;
        }
      }
      if (s1 == k) {
        return v2;
      } else if (s1 > k) {
        h = m;
      } else {
        l = m + 1;
      }
    }
    return l;
  }
};

int main() {
  Solution sol;
  std::cout << sol.findKthNumber(1, 3, 2) << std::endl;
}
