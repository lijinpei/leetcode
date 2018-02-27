/*
 * I think this code could be totally expanded at compile time, but in fact it
 * does't perform well on leetcode
 */
template <int N, int a, int b>
struct S {
  template <int M = 0>
  static int calc(int ans, int n) {
    using S1 = S<N + 1, b, a + b>;
    if (!n) {
      return ans;
    }
    if ((n & 3) == 3) {
      return S1::template calc<0>(b, n >> 1);
    } else {
      return S1::template calc<M>(ans + (n & 1 ? b : 0), n >> 1);
    }
  }
};

template <int a, int b>
struct S<32, a, b> {
  template <int M = 1>
  static int calc(int ans, int) {
    return ans + M;
  }
};

class Solution {
public:
  int findIntegers(int n) {
    return S<0, 1, 1>::calc<1>(0, n);
  }
};

int main() {
  Solution sol;
  int a = sol.findIntegers(1);
}
