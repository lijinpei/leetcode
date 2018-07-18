#include <algorithm>
#include <utility>
#include <vector>

struct TreeNode {
  int val;
  TreeNode *left;
  TreeNode *right;
  TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class Solution {
  static int depth(TreeNode *root) {
    return std::max(root->left ? depth(root->left) : 0,
                    root->right ? depth(root->right) : 0) +
           1;
  }
  void search(TreeNode* r, int d, int p) {
    if (lm[d] < 0) {
      lm[d] = p;
    } else {
      lm[d] = std::min(lm[d], p);
    }
    if (rm[d] < 0) {
      rm[d] = p;
    } else {
      rm[d] = std::max(rm[d], p);
    }
    if (r->left) {
      search(r->left, d + 1, p + p);
    }
    if (r->right) {
      search(r->right, d + 1, p + p + 1);
    }
  }

  std::vector<int> lm, rm;

public:
  int widthOfBinaryTree(TreeNode *root) {
    if (!root) {
      return 0;
    }
    int d = depth(root);
    lm.resize(d, -1);
    rm.resize(d, -1);
    search(root, 0, 0);
    int ans = 0;
    for (int i = 0; i < d; ++i) {
      int nv = rm[i] - lm[i];
      ans = std::max(nv, ans);
    }
    return ans + 1;
  }
};
