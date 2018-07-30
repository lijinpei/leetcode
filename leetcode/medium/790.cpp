class Solution {
public:
    int numTilings(int N) {
      int a0 = 1, a1 = 1, a2 = 2;
      if (N == 0) {
        return a0;
      }
      if (N == 1) {
        return a1;
      }
      if (N == 2) {
        return a2;
      }
      auto A = [](int v) {
        int vm = 1000000007;
        if (v >= vm) {
          return v - vm;
        }
        return v;
      };
      for (int i = 2; i < N; ++i) {
        int a3 = A(A(a2 + a2) + a0);
        a0 = a1;
        a1 = a2;
        a2 = a3;
      }
      return a2;
    }
};
