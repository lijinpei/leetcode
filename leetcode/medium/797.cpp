#include <vector>

class Solution {
  using GraphT = std::vector<std::vector<int>>;
  int n;
  std::vector<int> stack;
  std::vector<std::vector<int>> ret;
  void findPath(int node, int num, GraphT &g) {
    stack[num] = node;
    if (node == n - 1) {
      ret.emplace_back(stack.begin(), stack.begin() + num + 1);
      return;
    }
    for (int i = 0, s = g[node].size(); i < s; ++i) {
      findPath(g[node][i], num + 1, g);
    }
  }
public:
  std::vector<std::vector<int>> allPathsSourceTarget(GraphT& graph) {
    stack.resize(n = graph.size());
    ret.clear();
    findPath(0, 0, graph);
    return ret;
  }
};
