struct TreeNode {
  int val;
  TreeNode *left;
  TreeNode *right;
  TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
public:
  static TreeNode* pruneTree(TreeNode* root) {
    if (!root) {
      return nullptr;
    }
    root->left = pruneTree(root->left);
    root->right = pruneTree(root->right);
    return root->val == 1 || root->left || root->right ? root : nullptr;
  }
};
