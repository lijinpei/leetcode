#include <iostream>
#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>

class Solution {
public:
  int networkDelayTime(std::vector<std::vector<int>> &times, int N, int K) {
    auto times_comp = [](std::vector<int> & time1, std::vector<int> & time2) {
      return time1[0] < time2[0];
    };
    std::sort(times.begin(), times.end(), times_comp);
    std::vector<int> edge_start(N + 1), edge_num(N + 1),
        distance(N + 1, std::numeric_limits<int>::max());
    {
      int lp = times[0][0], ls = 0, ln = 1;
      for (int i = 1, s = times.size(); i < s; ++i) {
        if (times[i][0] == lp) {
          ++ln;
        } else {
          edge_num[lp] = ln;
          edge_start[lp] = ls;
          lp = times[i][0];
          ls += ln;
          ln = 1;
        }
      }
      edge_num[lp] = ln;
      edge_start[lp] = ls;
    }
    //for (auto & e : times) {
      //for (auto v : e) {
        //std::cout << v << ' ';
      //}
      //std::cout << std::endl;
    //}
    //for (auto v : edge_num) {
      //std::cout << v << ' ';
    //}
    //std::cout << std::endl;
    std::vector<int> in_pq(N + 1, -1), pq(N);
    int pq_size = 0;
    auto pq_swap = [&](int n1, int n2) {
      std::swap(in_pq[pq[n1]], in_pq[pq[n2]]);
      std::swap(pq[n1], pq[n2]);
    };
    auto father = [](int n1) {
      return (n1 - 1) / 2;
    };
    auto pq_up = [&](int n1) {
      while (n1) {
        int fa = father(n1);
        if (distance[pq[n1]] < distance[pq[fa]]) {
          pq_swap(n1, fa);
          n1 = fa;
        } else {
          break;
        }
      }
    };
    auto pq_down = [&](int n1) {
      while (true) {
        bool lc_large = false;
        int lc = 2 * n1 + 1;
        if (lc < pq_size && distance[pq[lc]] < distance[pq[n1]]) {
          lc_large = true;
        }
        if (lc_large) {
          int rc = lc + 1;
          if (rc < pq_size && distance[pq[rc]] < distance[pq[lc]]) {
            pq_swap(n1, rc);
            n1 = rc;
          } else {
            pq_swap(n1, lc);
            n1 = lc;
          }
        } else {
          int rc = lc + 1;
          if (rc < pq_size && distance[pq[rc]] < distance[pq[n1]]) {
            pq_swap(n1, rc);
            n1 = rc;
          } else {
            return;
          }
        }
      }
    };
    auto pq_add = [&](int n) {
      pq[pq_size] = n;
      in_pq[n] = pq_size;
      ++pq_size;
      pq_up(pq_size - 1);
    };
    auto pq_dump = [&]() {
      std::cout << "pq\n";
      for (int i = 0; i < pq_size; ++i) {
        std::cout << pq[i] << ' ';
      }
      std::cout << std::endl;
      std::cout << "in_pq\n";
      for (int i = 1; i <= N ; ++i) {
        std::cout << in_pq[i] << ' ';
      }
      std::cout << std::endl;
    };
    auto pq_pop = [&]() {
      int ret = pq[0];
      pq_swap(0, pq_size - 1);
      --pq_size;
      pq_down(0);
      return ret;
    };
    distance[K] = 0;
    pq_add(K);
    int ans_n = 0, ans_v;
    while (pq_size && ans_n < N) {
      int n = pq_pop();
      int v = distance[n];
      ++ans_n;
      ans_v = v;
      for (int i = edge_start[n], e = i + edge_num[n]; i < e; ++i) {
        int m = times[i][1];
        int w = times[i][2];
        int nv = w + v;
        if (distance[m] > nv) {
          distance[m] = nv;
          if (in_pq[m] < 0) {
            pq_add(m);
          } else {
            pq_up(in_pq[m]);
          }
        }
      }
    }
    return ans_n == N ? ans_v : -1;
  }
};
