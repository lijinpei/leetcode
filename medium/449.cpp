#include <string>
#include <utility>

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class Codec {
  static void fromInt(void* p_, int v) {
    unsigned char *p = reinterpret_cast<unsigned char*>(p_);
    for (int i = int(sizeof(int)) - 1; i >= 0; --i) {
      p[i] = v & 0xFF;
      v >>= 8;
    }
  }
  static int toInt(const void* p_) {
    const unsigned char *p = reinterpret_cast<const unsigned char*>(p_);
    int r = 0;
    for (int i = 0; i < int(sizeof(int)); ++i) {
      r = (r << 8) + p[i];
    }
    return r;
  }
  static TreeNode* getNode(const std::string & data, int pos) {
    return new TreeNode(toInt(data.data() + pos));
  }
  static std::pair<TreeNode*, int> deserialize(const std::string & data, int pos) {
    int s = data[pos + sizeof(int)];
    if (!s) {
      return {nullptr, pos + sizeof(int) + 1};
    }
    auto ret = std::make_pair<TreeNode*, int>(getNode(data, pos), pos + sizeof(int) + 1);
    if (s == 1) {
      return ret;
    }
    if (s & 2) {
      auto res1 = deserialize(data, ret.second);
      ret.first->left = res1.first;
      ret.second = res1.second;
    }
    if (s & 4) {
      auto res2 = deserialize(data, ret.second);
      ret.first->right = res2.first;
      ret.second = res2.second;
    }
    return ret;
  }
public:

  // Encodes a tree to a single string.
  std::string serialize(TreeNode* root) {
    std::string ret(sizeof(int) + 1, ' ');
    if (!root) {
      ret[sizeof(int)] = 0;
      return ret;
    }
    int s = 1;
    fromInt(&ret[0], root->val);
    std::string sl, sr;
    if (root->left) {
      s += 2;
      sl = serialize(root->left);
    }
    if (root->right) {
      s += 4;
      sr = serialize(root->right);
    }
    ret[sizeof(int)] = s;
    return ret + sl + sr;
  }

  // Decodes your encoded data to tree.
  TreeNode* deserialize(const std::string & data) {
    return deserialize(data, 0).first;
  }
};

// Your Codec object will be instantiated and called as such:
// Codec codec;
// codec.deserialize(codec.serialize(root));
