#include <algorithm>
#include <queue>
#include <vector>

class Solution {
public:
  int maxProfitAssignment(std::vector<int> &difficulty,
                          std::vector<int> &profit, std::vector<int> &worker) {
    int s = difficulty.size();
    using Pty = std::pair<int, int>;
    std::vector<Pty> tasks(s);
    for (int i = 0; i < s; ++i) {
      tasks[i] = std::make_pair(difficulty[i], profit[i]);
    }
    auto comp_diff = [](const Pty &p1, const Pty &p2) {
      return p1.first < p2.first;
    }; /*
     auto comp_prof = [](const Pty & p1, const Pty & p2) {
       return p1.second < p2.second;
     };
     */
    std::sort(tasks.begin(), tasks.end(), comp_diff);
    std::sort(worker.begin(), worker.end());
    /*
    std::vector<Pty> pq_storage(s);
    pq_storage.resize(0);
    std::priority_queue<Pty, decltype(pq_storage), decltype(comp_prof)> pq(
        comp_prof, pq_storage);
    int np = 0, ans = 0;
    for (int i = 0, ws = worker.size(); i < ws; ++i) {
      int ab = worker[i];
      while (np < s && tasks[np].first < ab) {
        pq.push(tasks[np++]);
      }
      if (!pq.empty()) {
        ans += pq.top().second;
        pq.pop();
      }
    }
    */
    int np = 0, ans = 0, mp = 0;
    for (int i = 0, ws = worker.size(); i < ws; ++i) {
      int ab = worker[i];
      while (np < s && tasks[np].first <= ab) {
        if (mp < tasks[np].second) {
          mp = tasks[np].second;
        }
        ++np;
      }
      ans += mp;
    }
    return ans;
  }
};
