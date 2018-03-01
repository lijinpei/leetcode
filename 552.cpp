#include <iostream>
#include <cstdint>

const uint32_t C = 1000000007;
template <int N>
uint32_t f(uint32_t v) {
  if (v >= C * (N - 1)) {
    return v - C * (N - 1);
  } else {
    return f<N - 1>(v);
  }
}

template <>
uint32_t f<1>(uint32_t v) {
  return v;
}

class Solution {
public:
  int checkRecord(int n) {
    if (!n) {
      return 0;
    }
    uint32_t A = 1, P0 = 1, P1 = 0, NL0 = 1, NL1 = 0, NLL0 = 0, NLL1 = 0;
    auto calc = [&](uint32_t A_, uint32_t P0_, uint32_t P1_, uint32_t NL0_, uint32_t NL1_, uint32_t NLL0_, uint32_t NLL1_) {
      A = f<3>(P0_ + NL0_ + NLL0_);
      P0 = f<3>(P0_ + NL0_ + NLL0_);
      P1 = f<4>(A_ + P1_ + NL1_ + NLL1_);
      NL0 = P0_;
      NL1 = f<2>(A_ + P1_);
      NLL0 = NL0_;
      NLL1 = NL1_;
    };
    for (int i = 1; i < n; ++i) {
      calc(A, P0, P1, NL0, NL1, NLL0, NLL1);
    }
    return f<4>(f<4>(A + P0 + P1 + NL0) + NL1 + NLL0 + NLL1);
  }
};

int main() {
  Solution sol;
  for (int i = 0; i <= 100; ++i) {
    std::cout << sol.checkRecord(i) << ' ' << sol.checkRecord1(i) << std::endl;
  }
}
