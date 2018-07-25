#include <utility>

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class Solution {
  std::pair<int, int> kst(TreeNode* root, int k) {
    std::pair<int, int> res{0, 0};
    if (root->left) {
      res = kst(root->left, k);
    }
    if (res.second >= k) {
      return res;
    }
    if (res.second + 1 == k) {
      return {root->val, k};
    }
    std::pair<int, int> res1{0, 0};
    if (root->right) {
      res1 = kst(root->right, k - res.second - 1);
    }
    return {res1.first, res1.second + 1 + res.second};
  }
public:
  int kthSmallest(TreeNode* root, int k) {
    return kst(root, k).first;
  }
};
