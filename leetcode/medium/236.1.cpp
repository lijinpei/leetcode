#include <iostream>

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class Solution {
public:
  TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
    if (!root) {
      return nullptr;
    }
    if (p == root || q == root) {
      return root;
    }
    auto * left = lowestCommonAncestor(root->left, p, q);
    auto * right = lowestCommonAncestor(root->right, p, q);
    if (left && right) {
      return root;
    }
    return left ? left : right;
  }
};

