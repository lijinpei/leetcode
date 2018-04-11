#include <iostream>
#include <algorithm>

class Solution {
public:
  int integerReplacement(int n) {
    const int S = sizeof(int) * 8;
    int v = 1 << (S - 2);
    while (n < v) {
      v >>= 1;
    }
    bool last_one = true;
    int v0, v1 = 0, v2 = 1;
    while (v >>= 1) {
      int nv1 = std::min(v2, last_one ? v1 : v0) + 2;
      int nv0 = (last_one ? v1 : v0) + 1;
      last_one = n & v;
      int nv2 = last_one ? v2 + 1 : nv1;
      v0 = nv0;
      v1 = nv1;
      v2 = nv2;
      //std::cout << v << ' ' << v0 << ' ' << v1 << ' ' << v2 << std::endl;
    }
    return n & 1 ? v1 : v0;
  }
};

int main() {
  Solution sol;
  std::cout << sol.integerReplacement(7) << std::endl;
  std::cout << sol.integerReplacement(std::numeric_limits<int>::max()) << std::endl;
}
