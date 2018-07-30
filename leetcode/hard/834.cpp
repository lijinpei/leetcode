#include <iostream>
#include <vector>

void output_vector(const std::vector<int> &vec) {
  for (auto v : vec) {
    std::cerr << v << ' ';
  }
  std::cerr << std::endl;
}

class Solution {
  class Impl {
    using VecRef = const std::vector<int> &;
    int N;
    VecRef edge, edge_num, edge_start;
    std::vector<int> dis_sum, ch_num;
    struct Node {
      int v, n;
      int fa;
    };
    template <typename T1, typename T2, typename T3>
    void dfs(T1 &&pre_cb, T2 &&post_cb, T3 &&post_single_cb) {
      std::vector<Node> stack(N);
      int tos = 0;
      stack[0] = {0, 0, -1};
      while (tos >= 0) {
        int v = stack[tos].v;
        int fa = stack[tos].fa;
        int &n = stack[tos].n;
        if (n == edge_num[v]) {
          post_single_cb(v);
          if (fa != -1) {
            post_cb(v, fa);
          }
          --tos;
          continue;
        }
        int ch = edge[edge_start[v] + n++];
        if (ch == fa) {
          continue;
        }
        pre_cb(ch, v);
        ++tos;
        stack[tos].v = ch;
        stack[tos].n = 0;
        stack[tos].fa = v;
      }
    }

  public:
    Impl(int N, VecRef edge, VecRef edge_num, VecRef edge_start)
        : N(N), edge(edge), edge_num(edge_num), edge_start(edge_start),
          dis_sum(N), ch_num(N) {}
    std::vector<int> solve() {
      auto pre_cb1 = [&](int, int) {};
      auto post_cb1 = [&](int ch, int fa) {
        ch_num[fa] += ch_num[ch];
        dis_sum[fa] += ch_num[ch] + dis_sum[ch];
      };
      auto post_single_cb1 = [&](int fa) { ++ch_num[fa]; };
      dfs(pre_cb1, post_cb1, post_single_cb1);
      auto pre_cb2 = [&](int ch, int fa) {
        dis_sum[ch] = dis_sum[fa] + N - 2 * ch_num[ch];
      };
      auto post_cb2 = [&](int, int) {};
      auto post_single_cb2 = [&](int) {};
      dfs(pre_cb2, post_cb2, post_single_cb2);
      return dis_sum;
    }
    ~Impl() {}
  };

public:
  std::vector<int> sumOfDistancesInTree(int N,
                                        std::vector<std::vector<int>> &edges_) {
    std::vector<int> edge(2 * (N - 1));
    std::vector<int> edge_num(N), edge_start(N);
    for (const auto &e : edges_) {
      ++edge_num[e[0]];
      ++edge_num[e[1]];
    }
    {
      int start = 0;
      for (int i = 0; i < N; ++i) {
        start += edge_num[i];
        edge_start[i] = start;
      }
    }
    for (const auto &e : edges_) {
      int e0 = e[0], e1 = e[1];
      edge[--edge_start[e0]] = e1;
      edge[--edge_start[e1]] = e0;
    }
    return Impl(N, edge, edge_num, edge_start).solve();
  }
};

int main() {
  Solution sol;
  std::vector<int> v1 = {0, 1};
  std::vector<int> v2 = {0, 2};
  std::vector<int> v3 = {2, 3};
  std::vector<int> v4 = {2, 4};
  std::vector<int> v5 = {2, 5};
  std::vector<std::vector<int>> input;
  input.push_back(v1);
  input.push_back(v2);
  input.push_back(v3);
  input.push_back(v4);
  input.push_back(v5);
  sol.sumOfDistancesInTree(6, input);
}
