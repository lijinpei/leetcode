struct TreeNode {
  int val;
  TreeNode *left;
  TreeNode *right;
  TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class Solution {
  int sumNumbers(TreeNode* root, int p) {
    TreeNode *lc = root->left, *rc = root->right;
    int v = p * 10 + root->val;
    if (!lc && !rc) {
      return v;
    }
    int ret = 0;
    if (lc) {
      ret = sumNumbers(lc, v);
    }
    if (rc) {
      ret += sumNumbers(rc, v);
    }
    return ret;
  }
public:
  int sumNumbers(TreeNode *root) {
    if (!root) {
      return 0;
    }
    return sumNumbers(root, 0);
  }
};
