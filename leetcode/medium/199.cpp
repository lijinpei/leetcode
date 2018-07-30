#include <vector>

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class Solution {
  class Impl {
    TreeNode* root;
    std::vector<int> ret;
    void search(TreeNode* root, int d) {
      if (root->left) {
        search(root->left, d + 1);
      }
      if (root->right) {
        search(root->right, d + 1);
      }
      if (d >= int(ret.size())) {
        ret.resize(d + 1);
      }
      ret[d] = root->val;
    }
  public:
    Impl(TreeNode* root) : root(root) {
    }
    std::vector<int> calc() {
      if (root) {
        search(root, 0);
      }
      return std::move(ret);
    }
  };
public:
  std::vector<int> rightSideView(TreeNode* root) {
    return Impl(root).calc();
  }
};
