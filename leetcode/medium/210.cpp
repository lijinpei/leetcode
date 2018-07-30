#include <iostream>
#include <utility>
#include <vector>

class Solution {
public:
  std::vector<int> findOrder(int N,
                             const std::vector<std::pair<int, int>> &prerequisites) {
    int M = prerequisites.size();
    std::vector<int> edge_num(N), edge_start(N);
    std::vector<int> edge(M);
    for (const auto & kv : prerequisites) {
      ++edge_num[kv.first];
    }
    { int sum = 0;
      for (int i = 0; i < N; ++i) {
        sum += edge_num[i];
        edge_start[i] = sum;
      }
    }
    for (const auto & kv : prerequisites) {
      edge[--edge_start[kv.first]] = kv.second;
    }
    std::vector<std::pair<int, int>> stack(N);
    std::vector<bool> in_stack(N);
    std::vector<int> dfs_num(N);
    std::vector<int> ret(N);
    int dfs = 0;;
    int tos;
    auto push = [&](int n) {
      if (in_stack[n]) {
        return false;
      }
      if (dfs_num[n]) {
        return true;
      }
      in_stack[n] = true;
      ++tos;
      stack[tos] = {n, 0};
      return true;
    };
    for (int i = 0; i < N; ++i) {
      if (!dfs_num[i]) {
        tos = -1;
        push(i);
        while (tos >= 0) {
          //std::cout << tos << std::endl;
          int v = stack[tos].first;
          int& n = stack[tos].second;
          if (n == edge_num[v]) {
            ret[dfs++] = v;
            dfs_num[v] = dfs;
            in_stack[v] = false;
            --tos;
          } else {
            int ch = edge[edge_start[v] + n++];
            if (!push(ch)) {
              return {};
            }
          }
        }
      }
    }
    return ret;
  }
};

int main() {
  Solution sol;
  auto ret = sol.findOrder(2, {std::make_pair(0, 1)});
  for (auto i : ret) {
    std::cout << i << ' ';
  }
  std::cout << std::endl;
}
