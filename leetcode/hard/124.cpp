#include <algorithm>
#include <utility>
#include <climits>

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class Solution {
  // first: ans, second: sum
  using PT = std::pair<int, int>;
  static PT search(TreeNode* root) {
    const int val = root->val;
    auto f = [](TreeNode* p) -> PT {
      return p ? search(p) : PT(INT_MIN, 0);
    };
    auto calc = [](const int v, const PT & p1, const PT & p2) -> PT {
      int nv = v + p1.second + p2.second;
      int ns = v + std::max(p1.second, p2.second);
      return {std::max(nv, std::max(p1.first, p2.first)), std::max(ns, 0)};
    };
    return calc(root->val, f(root->left), f(root->right));
  }
public:
    int maxPathSum(TreeNode* root) {
      return search(root).first;
    }
};

int main() {
}
