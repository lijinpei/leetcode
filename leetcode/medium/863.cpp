#include <vector>

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
  class SolutionImpl {
    std::vector<int> ret;
    TreeNode* root, *target;
    int K;
    void search1(TreeNode* root, int D) {
      if (!D) {
        ret.push_back(root->val);
      }
      if (D < 0) {
        return;
      }
      if (root->left) {
        search1(root->left, D - 1);
      }
      if (root->right) {
        search1(root->right, D - 1);
      }
    }
    int search(TreeNode* root) {
      if (target == root) {
        search1(root, K);
        return 0;
      }
      int ret = -1, retl = -1, retr = -1;
      if (root->left) {
        retl = search(root->left);
      }
      if (root->right) {
        retr = search(root->right);
      }
      if (retl >= 0) {
        ret = retl + 1;
        if (ret == K) {
          this->ret.push_back(root->val);
        }
        if (root->right) {
          search1(root->right, K - ret - 1);
        }
        return ret;
      }
      if (retr >= 0) {
        ret = retr + 1;
        if (ret == K) {
          this->ret.push_back(root->val);
        }
        if (root->left) {
          search1(root->left, K - ret - 1);
        }
        return ret;
      }
      return ret;
    }
  public:
    SolutionImpl(TreeNode* root, TreeNode* target, int K) : root(root), target(target), K(K) {
    }
    std::vector<int> calc() {
      search(root);
      return std::move(ret);
    }
  };
public:
  std::vector<int> distanceK(TreeNode* root, TreeNode* target, int K) {
    return SolutionImpl(root, target, K).calc();
  }
};
