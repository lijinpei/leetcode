#include <iostream>
#include <vector>
#include <cstdlib>

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

void visit(TreeNode* r) {
  if (!r) {
    return;
  }
  std::cerr << r->val << std::endl;
  visit(r->left);
  visit(r->right);
}

class Solution {
public:
  TreeNode* constructMaximumBinaryTree(const std::vector<int>& nums) {
    std::vector<TreeNode*> stack(nums.size() + 2);
    TreeNode n0(0);
    stack[0] = &n0;
    int tos = 0, ret_v = nums[0];
    TreeNode* ret = nullptr;
    for (int i = 0, s = nums.size(); i < s; ++i) {
      int v = nums[i];
      stack[tos + 1] = nullptr;
      stack[0]->val = v + 1;
      int t;
      for (t = tos; stack[t]->val < v; --t) {
        stack[t]->right = stack[t + 1];
      }
      TreeNode* n = new TreeNode(v);
      n->left = (t == tos ? nullptr : stack[t + 1]);
      stack[tos = (++t)] = n;
      if (v >= ret_v) {
        ret_v = v;
        ret = n;
      }
    }
    stack[tos + 1] = nullptr;
    for (; tos; --tos) {
      stack[tos]->right = stack[tos + 1];
    }
    return ret;
  }
};

int main() {
  std::vector<int> input{3,2,1,6,0,5};
  Solution sol;
  visit(sol.constructMaximumBinaryTree(input));
}
