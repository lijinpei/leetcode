#include <utility>

class Solution {
  static std::pair<TreeNode *, int> search(TreeNode *root) {
    std::pair<TreeNode *, int> p1, p2;
    if (root->left) {
      p1 = search(root->left);
    } else {
      p1 = {nullptr, 0};
    }
    if (root->right) {
      p2 = search(root->right);
    } else {
      p2 = {nullptr, 0};
    }
    if (p1.second == p2.second) {
      return {root, p1.second + 1};
    } else if (p1.second > p2.second) {
      return {p1.first, p1.second + 1};
    } else {
      return {p2.first, p2.second + 1};
    }
  }

public:
  TreeNode *subtreeWithAllDeepest(TreeNode *root) {
    if (!root) {
      return nullptr;
    }
    return search(root).first;
  }
};
