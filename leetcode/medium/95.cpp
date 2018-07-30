#include <vector>
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class Solution {
  static std::vector<TreeNode *> generateTrees(int l, int r) {
    if (l > r) {
      return {nullptr};
    }
    std::vector<TreeNode *> ret;
    for (int i = l; i <= r; ++i) {
      auto ret1 = generateTrees(l, i - 1);
      auto ret2 = generateTrees(i + 1, r);
      for (auto &lc : ret1) {
        for (auto &rc : ret2) {
          TreeNode *r = new TreeNode(i);
          r->left = lc;
          r->right = rc;
          ret.push_back(r);
        }
      }
    }
    return ret;
  }

public:
  std::vector<TreeNode *> generateTrees(int n) {
    return n ? generateTrees(1, n) : std::vector<TreeNode*>();
  }
};
