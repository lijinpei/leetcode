#include <queue>
#include <vector>

struct Fraction {
  int p, q, n;
  Fraction() {}
  Fraction(int p, int q, int n) : p(p), q(q), n(n) {}
};

struct FractionCompare {
   bool operator()(const Fraction & f1, const Fraction & f2) {
     return f1.p * f2.q > f1.q * f2. p;
   }
};

class Solution {
public:
  std::vector<int> kthSmallestPrimeFraction(std::vector<int> &A, int K) {
    int n = A.size() - 1;
    std::vector<Fraction> pq_storage(n);
    for (int i = 0; i < n; ++i) {
      pq_storage[i] = Fraction(1, A[i + 1], 1);
    }
    std::priority_queue<Fraction, decltype(pq_storage), FractionCompare> pq(
        FractionCompare(), pq_storage);
    while (--K) {
      auto f = pq.top();
      pq.pop();
      int np = A[f.n++];
      if (np < f.q) {
        f.p = np;
        pq.push(f);
      }
    }
    return {pq.top().p, pq.top().q};
  }
};
