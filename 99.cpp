#include <iostream>
#include <utility>

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

bool valid(TreeNode* p) {
  return p && p != reinterpret_cast<TreeNode*>(-1ll);
}

void rotate(TreeNode* &L, TreeNode* &R, TreeNode* &P) {
  std::swap(L, R);
  std::swap(P, R);
}

class Solution {
  int count = 0;

public:
  void recoverTree(TreeNode *root) {
    TreeNode *finish_mark = reinterpret_cast<TreeNode*>(-1ll);
    TreeNode *p = root, *pa = finish_mark;
    while (true) {
      rotate(p->left, p->right, pa);
      if (pa == finish_mark) {
        break;
      }
      if (valid(pa->left)) {
        if (!valid(pa->right) || (pa->right->val <= pa->left->val)) {
          if (!valid(pa) || (pa->val >= pa->left->val)) {
          std::cout << pa->val << std::endl;
          }
        }
      }
      if (pa) {
        std::swap(pa, p);
      }
    }
  }
};
