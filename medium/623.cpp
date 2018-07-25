struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class Solution {
  static TreeNode* addOneRowImpl(TreeNode* root, int v, int d) {
    if (d == 2) {
      auto* lp = new TreeNode(v);
      lp->left = root->left;
      root->left = lp;
      auto* rp = new TreeNode(v);
      rp->right = root->right;
      root->right = rp;
      return root;
    }
    if (root->left) {
      addOneRow(root->left, v, d - 1);
    }
    if (root->right) {
      addOneRow(root->right, v, d - 1);
    }
    return root;
  }
public:
  static TreeNode* addOneRow(TreeNode* root, int v, int d) {
    if (d == 1) {
      auto * ret = new TreeNode(v);
      ret->left = root;
      return ret;
    }
    return addOneRowImpl(root, v, d);
  }
};
