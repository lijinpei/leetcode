#include <iostream>
#include <cstdint>
#include <vector>

struct TreeLinkNode {
  int val;
  TreeLinkNode *left, *right, *next;
  TreeLinkNode(int x) : val(x), left(nullptr), right(nullptr), next(nullptr) {}
};

class Solution {
  TreeLinkNode* updown(TreeLinkNode* root) {
    int depth = 1;
    while (depth && root) {
      if (root->left) {
        root->left->next = root;
        root = root->left;
        --depth;
      } else if (root->right) {
        root->right->next = root;
        root = root->right;
        --depth;
      } else {
        while (root->next && (root == root->next->right || !root->next->right)) {
          root = root->next;
          ++depth;
        }
        if (!root->next) {
          return nullptr;
        }
        root->next->right->next = root->next;
        root = root->next->right;
      }
    }
    return root;
  }

  void connect_impl(TreeLinkNode *root, TreeLinkNode *right) {
    if (root->right) {
        root->right->next = root;
      if (root->left) {
        root->left->next = root;
        connect_impl(root->left, root->right);
      }
      connect_impl(root->right, updown(right));
    } else if (root->left) {
      connect_impl(root->left, updown(right));
    }
    root->next = right;
  }

public:
  void connect(TreeLinkNode *root) {
    if (root) {
      connect_impl(root, nullptr);
    }
  }
};

TreeLinkNode* getNode(std::vector<int> & v) {
  int s = v.size();
  std::vector<TreeLinkNode*> p(s);
  for (int i = 0; i < s; ++i) {
    if (v[i]) {
      p[i] = new TreeLinkNode(v[i]);
    }
  }
  for (int i = 0; i < s; ++i) {
    auto N = [&](int n) {
      return n < s ? p[n] : nullptr;
    };
    if (!p[i]) {
      continue;
    }
    p[i]->left = N(2 * i + 1);
    p[i]->right = N(2 * i + 2);
  }
  return p[0];
}

int main() {
  /*
  TreeLinkNode n1(1), n2(2), n3(3), n4(4), n5(5);
  n1.left = &n2;
  n1.right = &n3;
  n2.left = &n4;
  n2.right = &n5;
  */
//  std::vector<int> v = {1,2,2,3,3,3,3,4,4,4,4,4,4,0,0,5,5};
  std::vector<int> v = {1, 2, 21, 3, 31, 0, 0, 4, 41};
  Solution sol;
  sol.connect(getNode(v));
}
