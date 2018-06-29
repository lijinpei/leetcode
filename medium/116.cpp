struct TreeLinkNode {
 int val;
 TreeLinkNode *left, *right, *next;
 TreeLinkNode(int x) : val(x), left(nullptr), right(nullptr), next(nullptr) {}
};

class Solution {
  void connect (TreeLinkNode* root, TreeLinkNode* right) {
    root->next = right;
    if (root->left) {
      connect(root->left, root->right);
      connect(root->right, right ? right->left : nullptr);
    }
  }
public:
  void connect(TreeLinkNode *root) {
    if (root) {
      connect(root, nullptr);
    }
  }
};
