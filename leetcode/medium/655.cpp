#include <vector>
#include <string>
#include <algorithm>

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class Solution {
  static int depth(TreeNode* root) {
    int l = root->left ? depth(root->left) : 0;
    int r = root->right ? depth(root->right) : 0;
    return std::max(l, r) + 1;
  }
  static void printTree(TreeNode* root, int r, int c, int d, std::vector<std::vector<std::string>> & screen) {
    screen[r][c] = std::to_string(root->val);
    int d2 = d >> 1;
    if (root->left) {
      printTree(root->left, r + 1, c - d, d2, screen);
    }
    if (root->right) {
      printTree(root->right, r + 1, c + d, d2, screen);
    }
  }
public:
  std::vector<std::vector<std::string>> printTree(TreeNode* root) {
    int m = depth(root);
    int n = (1 << m) - 1;
    std::vector<std::vector<std::string>> ret(m, std::vector<std::string>(n));
    printTree(root, 0, n / 2, (n + 1) / 4, ret);
    return std::move(ret);
  }
};
