#include <iostream>
/*
class Solution {
public:
  int countDigitOne(int n) {
    if (n <= 0) {
      return 0;
    }
    int ans = 0, i = 1, v = 1;
    n &= ~1;
    while (n) {
      v <<= 1;
      if (n & v) {
        ans += i * v;
        n &= ~v;
      }
      ++i;
    }
    return ans;
  }
};
*/

class Solution {
public:
  int countDigitOne(int n) {
    if (n <= 0) {
      return 0;
    }
    int v1 = n % 10, ans = v1 >= 1 ? 1 : 0, v = v1, i = 1, k = 1;
    n /= 10;
    while(n) {
      v1 = n % 10;
      n /= 10;
      if (v1 == 1) {
        ans += v + 1;
      }
      if (v1 > 1) {
        ans += 10 * k;
      }
      ans += i * k * v1;
      ++i;
      k *= 10;
      v += k * v1;
    }
    return ans;
  }
};

int main() {
  Solution sol;
  while (true) {
    int i;
    std::cin >> i;
    std::cout << sol.countDigitOne(i) << std::endl;
  }
}
