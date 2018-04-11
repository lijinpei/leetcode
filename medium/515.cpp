#include <vector>

class Solution {
  static int treeDepth(TreeNode* root) {
    int d = 0;
    if (root->left) {
      d = std::max(d, treeDepth(root->left));
    }
    if (root->right) {
      d = std::max(d, treeDepth(root->right));
    }
    return d + 1;
  }
  static void largestValues_impl(TreeNode* root, int d, std::vector<int> & ret) {
    ret[d] = std::max(ret[d], root->val);
    if (root->left) {
      largestValues_impl(root->left, d + 1, ret);
    }
    if (root->right) {
      largestValues_impl(root->right, d + 1, ret);
    }
  }
public:
  std::vector<int> largestValues(TreeNode* root) {
    if (!root) {
      return {};
    }
    int d = treeDepth(root);
    std::vector<int> ret(d, std::numeric_limits<int>::min());
    largestValues_impl(root, 0, ret);
    return ret;
  }
};
