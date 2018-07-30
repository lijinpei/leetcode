#include <utility>

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class Solution {
  std::pair<TreeNode*, TreeNode*> flattenImpl(TreeNode* root) {
    std::pair<TreeNode*, TreeNode*> ret{root, root};
    TreeNode* left = root->left, *right = root->right;
    root->left = nullptr;
    root->right = nullptr;
    if (left) {
      auto res1 = flattenImpl(left);
      ret.second->right = res1.first;
      ret.second = res1.second;
    }
    if (right) {
      auto res1 = flattenImpl(right);
      ret.second->right = res1.first;
      ret.second = res1.second;
    }
    return ret;
  }
public:
  void flatten(TreeNode* root) {
    if (!root) {
      return;
    }
    flattenImpl(root);
  }
};
