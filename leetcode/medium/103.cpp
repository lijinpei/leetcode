#include <vector>
#include <algorithm>

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
  std::vector<std::vector<int>> ret;
  void search(TreeNode* root, int d) {
    if (root->left) {
      search(root->left, d + 1);
    }
    if (root->right) {
      search(root->right, d + 1);
    }
    if (int(ret.size()) <= d) {
      ret.resize(d + 1);
    }
    ret[d].push_back(root->val);
  }
public:
  std::vector<std::vector<int>> zigzagLevelOrder(TreeNode* root) {
    ret.clear();
    if (root) {
      search(root, 0);
    }
    for (int i = 1, s = ret.size(); i < s; i += 2) {
      std::reverse(ret[i].begin(), ret[i].end());
    }
    return std::move(ret);
  }
};
