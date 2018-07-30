/*
 * Morris preorder traversal
 */
#include <vector>

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
public:
  std::vector<int> preorderTraversal(TreeNode *root) {
    std::vector<int> ret;
    while (root) {
      TreeNode* prev = root->left;
      if (!prev) {
        ret.push_back(root->val);
        root = root->right;
      } else {
        while (prev->right && prev->right != root) {
          prev = prev->right;
        }
        if (prev->right) {
          prev->right = nullptr;
          root = root->right;
        } else {
          ret.push_back(root->val);
          prev->right = root;
          root = root->left;
        }
      }
    }
    return ret;
  }
};
