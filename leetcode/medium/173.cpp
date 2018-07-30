#include <stack>

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class BSTIterator {
  std::stack<TreeNode*> stack;
public:
    BSTIterator(TreeNode *root) {
      while (root) {
        stack.push(root);
        root = root->left;
      }
    }

    /** @return whether we have a next smallest number */
    bool hasNext() {
      return !stack.empty();
    }

    /** @return the next smallest number */
    int next() {
      TreeNode* r = stack.top();
      int ret = r->val;
      stack.pop();
      r = r->right;
      while (r) {
        stack.push(r);
        r = r->left;
      }
      return ret;
    }
};

/**
 * Your BSTIterator will be called like this:
 * BSTIterator i = BSTIterator(root);
 * while (i.hasNext()) cout << i.next();
 */
