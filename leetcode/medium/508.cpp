#include <vector>
#include <unordered_map>

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class Solution {
  static int search(TreeNode* root, std::unordered_map<int, int> & map, int&mv) {
    int s = root->val;
    if (root->left) {
      s += search(root->left, map, mv);
    }
    if (root->right) {
      s += search(root->right, map, mv);
    }
    int & v = map[s];
    ++v;
    if (v > mv) {
      mv = v;
    }
    return s;
  }
public:
  std::vector<int> findFrequentTreeSum(TreeNode* root) {
    if (!root) {
      return {};
    }
    std::unordered_map<int, int> map;
    int mv = 0;
    search(root, map, mv);
    std::vector<int> ret;
    for (auto kv : map) {
      if (kv.second == mv) {
        ret.push_back(kv.first);
      }
    }
    return std::move(ret);
  }
};

