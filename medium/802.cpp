#include <vector>

class Solution {
  class SolutionImpl {
    std::vector<std::vector<int>>& graph;
    int n;
    std::vector<int> edge_count, rev_edge_count;
    std::vector<std::vector<int>> rev_graph;
  public:
    SolutionImpl(std::vector<std::vector<int>>& graph) : graph(graph), n(graph.size()), edge_count(n), rev_edge_count(n), rev_graph(n) {
      for (int i = 0; i < n; ++i) {
        edge_count[i] = graph[i].size();
        for (int j : graph[i]) {
          ++rev_edge_count[j];
        }
      }
      for (int i = 0; i < n; ++i) {
        rev_graph[i].reserve(rev_edge_count[i]);
      }
      for (int i = 0; i < n; ++i) {
        for (int j : graph[i]) {
          rev_graph[j].push_back(i);
        }
      }
    }

    void search(int p) {
      for (int p1 : rev_graph[p]) {
        --edge_count[p1];
        if (!edge_count[p1]) {
          search(p1);
        }
      }
    }

    std::vector<int> ans() {
      std::vector<int> ret(n);
      ret.resize(0);
      for (int i = 0; i < n; ++i) {
        if (!edge_count[i]) {
          ret.push_back(i);
        }
      }
      for (auto p : ret) {
        search(p);
      }
      ret.resize(0);
      for (int i = 0; i < n; ++i) {
        if (!edge_count[i]) {
          ret.push_back(i);
        }
      }
      return ret;
    }
  };
public:
  std::vector<int> eventualSafeNodes(std::vector<std::vector<int>>& graph) {
    return SolutionImpl(graph).ans();
  }
};
