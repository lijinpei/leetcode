#include <utility>

struct TreeNode {
  int val;
  TreeNode *left;
  TreeNode *right;
  TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class Solution {
  using RetTy = std::pair<TreeNode**, TreeNode*>;
  static RetTy find(TreeNode* &root, int key) {
    int v = root->val;
    if (v == key) {
      return {&root, root};
    }
    TreeNode* p = root;
    while (true) {
      if (key < v) {
        if (p->left) {
          v = p->left->val;
          if (v == key) {
            return {&(p->left), p->left};
          }
          p = p->left;
        } else {
          return {nullptr, nullptr};
        }
      } else {
        if (p->right) {
          v = p->right->val;
          if (v == key) {
            return {&(p->right), p->right};
          }
          p = p->right;
        } else {
          return {nullptr, nullptr};
        }
      }
    }
  }
  static RetTy largest(TreeNode* &root) {
    if (!root->right) {
      return {&root, root};
    }
    TreeNode *p = root, *c = root->right;
    for (; c->right; ) {
      p = c;
      c = c->right;
    }
    return {&(p->right), c};
  }
  static RetTy smallest(TreeNode* &root) {
    if (!root->left) {
      return {&root, root};
    }
    TreeNode *p = root, *c = root->left;
    for (; c->left; ) {
      p = c;
      c = c->left;
    }
    return {&(p->left), c};
  }
public:
  TreeNode *deleteNode(TreeNode *root, int key) {
    if (!root) {
      return nullptr;
    }
    TreeNode* ret = root;
    auto ret1 = find(ret, key);
    TreeNode** pp = ret1.first;
    TreeNode* p = ret1.second;
    if (!p) {
      return ret;
    }
    while (true) {
      if (p->left) {
        auto ret1 = largest(p->left);
        p->val = ret1.second->val;
        p = ret1.second;
        pp = ret1.first;
      } else if (p->right) {
        auto ret1 = smallest(p->right);
        p->val = ret1.second->val;
        p = ret1.second;
        pp = ret1.first;
      } else {
        *pp = nullptr;
        break;
      }
    }
    return ret;
  }
};
