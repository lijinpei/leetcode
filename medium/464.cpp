#include <iostream>
#include <cstdint>
#include <unordered_map>
#include <bitset>
#include <cassert>

enum State {
  Unknown,
  MustWin, 
  MustFail,
  Mixed
};

const int B = 20;
const int BM = (1 << B) - 1;

class Solution {
  uint32_t n, m;
  std::unordered_map<uint32_t, State> state;
  State calc(uint32_t st) {
    uint32_t s1 = st >> B;
    uint32_t s2 = st & BM;
    assert(s1 < m);
    if (!s2) {
      return Mixed;
    }
    bool can_win = false;
    for (uint32_t i = 0; i < n && s2; ++i) {
      uint32_t mask = (uint32_t(1) << i);
      if (!(s2 & mask)) {
        continue;
      }
      if (s1 + i + 1 >= m) {
        return MustWin;
      }
      uint32_t ns = ((s1 + i + 1) << B) | (s2 & ~mask);
      auto & ns_st = state[ns];
      if (ns_st == Unknown) {
        ns_st = calc(ns);
      }
      if (ns_st == MustFail) {
        return MustWin;
      }
      if (ns_st == Mixed) {
        can_win = true;
      }
    }
    return can_win ? Mixed : MustFail;
  }
public:
  bool canIWin(int maxChoosableInteger, int desiredTotal) {
    n = maxChoosableInteger;
    m = desiredTotal;
    if (m <= n) {
      return true;
    }
    auto ret = calc((1 << n) - 1);
    /*
    for (auto kv : state) {
      std::cout << std::bitset<4>((kv.first & BM)) << ' ' << kv.second << '\n';
    }
    */
    //std::cout << ret << std::endl;
    return ret == MustWin;
  }
};

int main() {
  Solution sol;
  sol.canIWin(5, 50);
}
