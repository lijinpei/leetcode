#include <vector>

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
  class Impl {
    TreeNode* root;
    std::vector<int> width;
    std::vector<std::vector<int>> ret;
    void getDepth(TreeNode* p, int d) {
      if (p->left) {
        getDepth(p->left, d + 1);
      }
      if (p->right) {
        getDepth(p->right, d + 1);
      }
      if (d >= width.size()) {
        width.resize(d + 1);
      }
      ++width[d];
    }
    void visit(TreeNode* p, int d) {
      ret[d].push_back(p->val);
      if (p->left) {
        visit(p->left, d + 1);
      }
      if (p->right) {
        visit(p->right, d + 1);
      }
    }
  public:
    Impl(TreeNode* root) : root(root) {}
    decltype(ret) calc() {
      getDepth(root, 0);
      int d = width.size();
      ret.resize(d);
      for (int i = 0; i < d; ++i) {
        ret[i].reserve(width[i]);
      }
      visit(root, 0);
      return std::move(ret);
    }
  };
public:
  std::vector<std::vector<int>> levelOrder(TreeNode* root) {
    if (!root) {
      return {};
    }
    return Impl(root).calc();
  }
};
