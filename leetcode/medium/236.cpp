#include <iostream>

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class Solution {
  TreeNode *p1, *p2;
  void calc(TreeNode* r, TreeNode* p) {
    if (r->left) {
      calc(r->left, r);
    }
    if (r->right) {
      calc(r->right, r);
    }
    if (p1 == p2) {
      return;
    }
    if (p1 == r) {
      p1 = p;
    }
    if (p2 == r) {
      p2 = p;
    }
  }
public:
  TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
    p1 = p;
    p2 = q;
    calc(root, nullptr);
    return p1;
  }
};

