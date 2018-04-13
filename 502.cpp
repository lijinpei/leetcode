#include <cassert>
#include <numeric>
#include <queue>
#include <vector>
#include <functional>

class Solution {
public:
  int findMaximizedCapital(int k, int W, std::vector<int> &Profits,
                           std::vector<int> &Capital) {
    int n = Profits.size();
    assert(size_t(n) == Capital.size());
    std::vector<int> cp_pq_storage(n);
    std::iota(cp_pq_storage.begin(), cp_pq_storage.end(), 0);
    auto cp_compare = [&](int n1, int n2) {
      return Capital[n1] > Capital[n2];
    };
    std::priority_queue<int, std::vector<int>, decltype(cp_compare)> cp_pq(
        cp_compare, cp_pq_storage);
    std::priority_queue<int, std::vector<int>> p_pq;
    while (k--) {
      while (!cp_pq.empty()) {
        int i = cp_pq.top();
        if (Capital[i] <= W) {
          p_pq.push(Profits[i]);
          cp_pq.pop();
        } else {
          break;
        }
      }
      if (!p_pq.empty()) {
        int i = p_pq.top();
        W += i;
        p_pq.pop();
      } else {
        break;
      }
    }
    return W;
  }
};

int main() {
  Solution sol;
}
