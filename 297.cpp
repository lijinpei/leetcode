#include <string>

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class Codec {
  TreeNode* deserialize_impl(const std::string & data, int & n) {
    if (data[n] == ' ') {
      ++n;
      return nullptr;
    } else {
      int n0 = n;
      while (data[n++] != ';') {
        continue;
      }
      auto *ret = new TreeNode(std::stoi(data.substr(n0, n - n0 - 1)));
      ret->left = deserialize_impl(data, ++n);
      ret->right = deserialize_impl(data, n);
      return ret;
    }
  }

public:
    // Encodes a tree to a single string.
  std::string serialize(TreeNode* root) {
      if (!root) {
        return " ";
      } else {
        return std::to_string(root->val) + ";" + serialize(root->left) + serialize(root->right);
      }
    }

    // Decodes your encoded data to tree.
    TreeNode* deserialize(const std::string & data) {
      int n = 0;
      return deserialize_impl(data, n);
    }
};

// Your Codec object will be instantiated and called as such:
// Codec codec;
// codec.deserialize(codec.serialize(root));
