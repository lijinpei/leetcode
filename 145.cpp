/*
 * Morris postorder traversal
 */
#include <vector>

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};
/*
 * The idea is to do this:
 * Visit(root) {
 *   if (root->left) {
 *     Visit(root->left);
 *     reverseOutputRightDescendants(root->left);
 *   }
 *   Visit(root->right);
 * }
 * claim: Visit(root) will output the left-partial tree at root in postorder.
 * left-partial tree for a tree root, is the sub-portion of the tree except node
 * root and all its right descendants
 * prove:
 * given a tree rooted at r, during Visit(r), root will point to every node in
 * preorder. We prove our claim with induction.
 * if r1 has no child , claim holds.
 * if r1 has some child, and the claim holds for r1's child, right after the if
 * statement, there are two possibilities:
 * 1: root->left == nullptr
 * 2: root->left != nullptr, Visit(root->left) has output root->left's
 *    left-partial tree(by our induction condition), then 
 *    reverseOutputRightDescentdants will make up root->left 's right
 *    descendants chain, so the whole root->left has been postorder visited.
 * then, Visit(root->right) will output root->right's partial tree in postorder.
 * left + right's paritial = root's partial, so the claim holds.
 */
class Solution {
public:
  std::vector<int> postorderTraversal(TreeNode *root) {
    std::vector<int> ret;
    auto traverseRightDescendants = [&](TreeNode* root) {
      auto  reverseRight = [](TreeNode *root) {
        TreeNode* p = nullptr;
        while (root) {
          TreeNode* np = root->right;
          root->right = p;
          p = root;
          root = np;
        }
        return p;
      };
      TreeNode* p = reverseRight(root), *p1 = p;
      while (p) {
        ret.push_back(p->val);
        p = p->right;
      }
      reverseRight(p1);
    };
    TreeNode dump_node(0);
    dump_node.left = root;
    root = &dump_node;
    while (root) {
      TreeNode* prev = root->left;
      if (!prev) {
        root = root->right;
      } else {
        while (prev->right && prev->right != root) {
          prev = prev->right;
        }
        if (prev->right) {
          prev->right = nullptr;
          traverseRightDescendants(root->left);
          root = root->right;
        } else {
          prev->right = root;
          root = root->left;
        }
      }
    }
    return ret;
  }
};
