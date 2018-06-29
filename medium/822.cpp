#include <vector>
#include <unordered_set>
#include <queue>

class Solution {
public:
  int flipgame(std::vector<int> &fronts, std::vector<int> &backs) {
    std::unordered_set<int> set;
    std::priority_queue<int, std::vector<int>, std::greater<int>> pq;
    int n = fronts.size();
    for (int i = 0; i < n; ++i) {
      int f = fronts[i], b = backs[i];
      if (f == b) {
        set.insert(f);
      } else {
        pq.push(f);
        pq.push(b);
      }
    }
    while (!pq.empty()) {
      int v = pq.top();
      pq.pop();
      if (set.find(v) == set.end()) {
        return v;
      }
    }
    return 0;
  }
};
