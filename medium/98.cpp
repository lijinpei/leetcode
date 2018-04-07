#include <limits>

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};
class Solution {
  static bool isValidBST_impl(TreeNode* root, bool b1, int v1, bool b2, int v2) {
    if ((b1 && root->val <= v1) || (b2 && root->val >= v2)) {
      return false;
    }
    if (root->left && !isValidBST_impl(root->left, b1, v1, true, root->val)) {
      return false;
    }
    if (root->right && !isValidBST_impl(root->right, true, root->val, b2, v2)) {
      return false;
    }
    return true;
  }
public:
  bool isValidBST(TreeNode *root) {
    return !root || isValidBST_impl(root, false, 0, false, 0);
  }
};
