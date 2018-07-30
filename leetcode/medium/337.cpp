#include <algorithm>
#include <utility>

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
  static std::pair<int, int> search(TreeNode* root) {
    std::pair<int, int> pl(0, 0), pr(0, 0);
    if (root->left) {
      pl = search(root->left);
    }
    if (root->right) {
      pr = search(root->right);
    }
    return {std::max(pl.first, pl.second) + std::max(pr.first, pr.second), root->val + pl.first + pr.first};
  }
public:
  int rob(TreeNode* root) {
    if (!root) {
      return 0;
    }
    auto res = search(root);
    return std::max(res.first, res.second);
  }
};
