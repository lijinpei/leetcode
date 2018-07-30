struct TreeNode {
  int val;
  TreeNode *left;
  TreeNode *right;
  TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};
static int opt = [](){
    std::ios::sync_with_stdio(false);
    cin.tie(NULL);
    return 0;
}();
class Solution {
  static bool isSymmetric(TreeNode *left, TreeNode *right) {
    if (left) {
      return right && left->val == right->val &&
             isSymmetric(left->right, right->left) &&
             isSymmetric(left->left, right->right);
    } else {
      return !right;
    }
  }

public:
  static bool isSymmetric(TreeNode *root) {
    return !root || isSymmetric(root->left, root->right);
  }
};
