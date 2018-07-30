#include <utility>
#include <iostream>
#include <sstream>
#include <queue>
#include <algorithm>
#include <cstddef> // to bring in definition for NULL

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};
class Solution {
public:
  void recoverTree(TreeNode *root) {
    TreeNode* last_p = root, *last_error = nullptr, *last_error1;
    while (last_p->left) {
      last_p = last_p->left;
    }
    auto visit = [&]() {
      if (root->val < last_p->val) {
        if (last_error) {
          std::swap(last_error->val, root->val);
          last_error = nullptr;
        } else {
          last_error = last_p;
          last_error1 = root;
        }
      }
      last_p = root;
    };
    while (root) {
      TreeNode* prev = root->left;
      if (!prev) {
        visit();
        root = root->right;
      } else {
        while (prev->right && prev->right != root) {
          prev = prev->right;
        }
        if (prev->right) {
          visit();
          prev->right = nullptr;
          root = root->right;
        } else {
          prev->right = root;
          root = root->left;
        }
      }
    }
    if (last_error) {
      std::swap(last_error->val, last_error1->val);
    }
  }
};
