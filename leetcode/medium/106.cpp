#include <iostream>
#include <vector>
#include <unordered_map>

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
  class BuildTreeImpl {
    std::vector<int> & inorder, &postorder;
    int n;
    std::unordered_map<int, int> inorder_rev;
    TreeNode* calc_impl(int l1, int r1, int l2, int r2) {
      int rv = postorder[r1 - 1];
      auto* ret = new TreeNode(rv);
      int r = inorder_rev[rv];
      int ln = r - l2;
      int rn = r2 - r - 1;
      ret->left = ln ? calc_impl(l1, l1 + ln, l2, l2 + ln) : nullptr;
      ret->right = rn ? calc_impl(l1 + ln, r1 - 1, r + 1, r2) : nullptr;
      return ret;
    }
  public:
    BuildTreeImpl(std::vector<int> & inorder, std::vector<int> & postorder) : inorder(inorder), postorder(postorder), n(inorder.size()) {
    }
    TreeNode* calc() {
      if (!n) {
        return nullptr;
      }
      inorder_rev.reserve(n);
      for (int i = 0; i < n; ++i) {
        inorder_rev[inorder[i]] = i;
      }
      return calc_impl(0, n, 0, n);
    }
  };
public:
  TreeNode* buildTree(std::vector<int>& inorder, std::vector<int>& postorder) {
    return BuildTreeImpl(inorder, postorder).calc();
  }
};

int main() {
  std::vector<int> input1{3,9,20,15,7};
  std::vector<int> input2{9,3,15,20,7};
  Solution sol;
  sol.buildTree(input1, input2);
}
