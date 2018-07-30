#include <queue>
#include <vector>
#include <iostream>

struct pq_node {
  int list, val;
};

struct pq_node_comparator {
  bool operator()(const pq_node & n1, const pq_node & n2) {
    return n1.val > n2.val;
  }
};

class Solution {
public:
  std::vector<int> smallestRange(std::vector<std::vector<int>>& nums) {
    int k = nums.size();
    std::vector<int> list_pos(k, 0);
    std::vector<pq_node> pq_container(k);
    int max_val = nums[0][0];
    for (int i = 0; i < k; ++i) {
      int v = nums[i][0];
      max_val = std::max(max_val, v);
      pq_container[i] = pq_node{i, v};
    }
    std::priority_queue<pq_node, decltype(pq_container), pq_node_comparator>
        pq(pq_node_comparator(), pq_container);
    int p1 = pq.top().val, p2 = max_val, ans = p2 - p1 + 1;
    while (true) {
      int v1 = pq.top().val;
      while (pq.top().val == v1) {
        pq_node n = pq.top();
        pq.pop();
        int & np = list_pos[n.list];
        ++np;
        if (np == nums[n.list].size()) {
          goto ret;
        }
        int nv = nums[n.list][np];
        if (nv > max_val) {
          max_val = nv;
        }
        pq.push(pq_node{n.list, nv});
      }
      int np1 = pq.top().val, nv = max_val - np1 + 1;
      if (nv < ans) {
        ans = nv;
        p1 = np1;
        p2 = max_val;
      }
    }
ret:
    return {p1, p2};
  }
};

int main() {
  Solution sol;
  std::vector<std::vector<int>> input{{4,10,15,24,26},{0,9,12,20},{5,18,22,30}};
  auto ret = sol.smallestRange(input);
}
