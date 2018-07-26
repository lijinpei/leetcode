#include <cstdint>
#include <unordered_map>
#include <utility>
#include <vector>
struct TreeNode {
  int val;
  TreeNode *left;
  TreeNode *right;
  TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};
struct Tree {
  int val;
  unsigned left, right;
  Tree(int v) : val(v), left(0), right(0) {}
  bool operator==(const Tree &rhs) const {
    return left == rhs.left && right == rhs.right && val == rhs.val;
  }
};
inline void hash_combine(std::size_t &seed, unsigned int v) {
  seed ^= v + 0x9e3779b9 + (seed << 6) + (seed >> 2);
}
namespace std {
template <> struct hash<Tree> {
  size_t operator()(const Tree &t) const {
    size_t seed = 0;
    hash_combine(seed, t.left);
    hash_combine(seed, t.right);
    hash_combine(seed, unsigned(t.val));
    return seed;
  }
};
} // namespace std

class Solution {
  std::unordered_map<Tree, int> tn;
  int ntn;
  std::vector<TreeNode *> ret;
  int search(TreeNode *root) {
    Tree t(root->val);
    if (root->left) {
      t.left = search(root->left);
    }
    if (root->right) {
      t.right = search(root->right);
    }
    int &h = tn[t];
    if (h < 0) {
      return -h;
    }
    if (h > 0) {
      ret.push_back(root);
      h = -h;
      return -h;
    }
    return h = ntn++;
  }

public:
  std::vector<TreeNode *> findDuplicateSubtrees(TreeNode *root) {
    tn.clear();
    ret.clear();
    ntn = 1;
    if (!root) {
      return {};
    }
    search(root);
    return std::move(ret);
  }
};

