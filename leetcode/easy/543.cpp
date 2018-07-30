#include <algorithm>
#include <utility>

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
  static std::pair<int, int> search(TreeNode* root) {
    std::pair<int, int> pl{0, 0}, pr{0, 0};
    if (root->left) {
      pl = search(root->left);
    }
    if (root->right) {
      pr = search(root->right);
    }
    return {std::max(std::max(pl.first, pr.first), pl.second + pr.second + 1), std::max(pl.second, pr.second) + 1};
  }
public:
  int diameterOfBinaryTree(TreeNode* root) {
    if (!root) {
      return 0;
    }
    return search(root).first - 1;
  }
};
