#include <unordered_map>
#include <vector>

struct UndirectedGraphNode {
  int label;
  std::vector<UndirectedGraphNode *> neighbors;
  UndirectedGraphNode(int x) : label(x){};
};

class Solution {
  std::unordered_map<UndirectedGraphNode *, UndirectedGraphNode *> map;
  void cloneGraph_impl(UndirectedGraphNode *node, UndirectedGraphNode *&v) {
    v = new UndirectedGraphNode(node->label);
    v->neighbors.resize(node->neighbors.size());
    for (int i = 0, s = node->neighbors.size(); i < s; ++i) {
      auto *v0 = node->neighbors[i];
      auto *&v1 = map[v0];
      if (!v1) {
        cloneGraph_impl(v0, v1);
      }
      v->neighbors[i] = v1;
    }
  }

public:
  UndirectedGraphNode *cloneGraph(UndirectedGraphNode *node) {
    if (!node) {
      return node;
    }
    auto *&v = map[node];
    cloneGraph_impl(node, v);
    return v;
  }
};
