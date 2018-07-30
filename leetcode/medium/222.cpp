struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class Solution {
public:
  int countNodes(TreeNode* root) {
    if (!root) {
      return 0;
    }
    auto left_depth = [](TreeNode* r) {
      auto ret = 0;
      for (; r; r = r->left) {
        ++ret;
      }
      return ret;
    };
    auto right_depth = [](TreeNode *r) {
      auto ret = 0;
      for (; r; r = r->right) {
        ++ret;
      }
      return ret;
    };
    int l = left_depth(root);
    if (l == 1) {
      return 1;
    }
    int ans = (1 << (l - 1)) - 1;
    for (; root; --l) {
      if (l == 1) {
        ans += 1;
        break;
      }
      int r = right_depth(root->left);
      if (r + 1 == l) {
        ans += 1 << (r - 1);
        root = root->right;
        if (left_depth(root) != r) {
          break;
        }
      } else {
        root = root->left;
      }
    }
    return ans;
  }
};
