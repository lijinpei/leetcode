#include <queue>
#include <vector>

class Solution {
public:
  int minRefuelStops(int target, int dis,
                     std::vector<std::vector<int>> &stations) {
    int p = 0, n = stations.size();
    int ref = 0;
    std::priority_queue<int> pq;
    while (dis < target) {
      while (p < n && stations[p][0] <= dis) {
        pq.push(stations[p++][1]);
      }
      if (pq.empty()) {
        return -1;
      }
      ++ref;
      dis += pq.top();
      pq.pop();
    }
    return ref;
  }
};
