struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class Solution {
  static int findBottomLeftValue_impl(TreeNode* root, int & d) {
    int d1, r1, d2, r2;
    if (root->left) {
      r1 = findBottomLeftValue_impl(root->left, d1);
      if (root->right) {
        r2 = findBottomLeftValue_impl(root->right, d2);
        if (d2 > d1) {
          d = d2 + 1;
          return r2;
        }
      }
      d = d1 + 1;
      return r1;
    } else if (root->right) {
        r2 = findBottomLeftValue_impl(root->right, d2);
        d = d2 + 1;
        return r2;
    } else {
      d = 1;
      return root->val;
    }
  }
public:
  int findBottomLeftValue(TreeNode* root) {
    int d;
    return findBottomLeftValue_impl(root, d);
  }
};
