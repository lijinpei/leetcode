#include <string>

class Trie {
  struct TrieNode {
    char c;
    TrieNode *child, *sibling;
    bool end_mark;
    TrieNode(char c, TrieNode *child = nullptr, TrieNode *sibling = nullptr,
             bool end_mark = false)
        : c(c), child(child), sibling(sibling), end_mark(end_mark) {}
  };
  TrieNode root;

  template <bool canInsert = false>
  static TrieNode* find(TrieNode* root, char c) {
    if (!root->child) {
      if (!canInsert) {
        return nullptr;
      } else {
        return root->child = new TrieNode(c);
      }
    }
    if (c < root->child->c) {
      if (!canInsert) {
        return nullptr;
      } else {
        return root->child = new TrieNode(c, nullptr, root->child);
      }
    }
    if (c == root->child->c) {
      return root->child;
    }
    for (TrieNode* ch = root->child; ; ) {
      TrieNode* ch1 = ch->sibling;
      if (!ch1) {
        if (!canInsert) {
          return nullptr;
        } else {
          return ch->sibling = new TrieNode(c, nullptr, nullptr);
        }
      }
      if (c < ch1->c) {
        if (!canInsert) {
          return nullptr;
        } else {
          return ch->sibling = new TrieNode(c, nullptr, ch->sibling);
        }
      }
      if (c == ch1->c) {
        return ch1;
      }
      ch = ch1;
    }
    return nullptr;
  }

public:
  Trie() : root(' ') {}

  void insert(const std::string & word) {
    TrieNode* r = &root;
    for (auto c : word) {
      r = find<true>(r, c);
    }
    r->end_mark = true;
  }

  bool search(const std::string & word) {
    TrieNode* r = &root;
    for (auto c : word) {
      r = find<false>(r, c);
      if (!r) {
        return false;
      }
    }
    return r->end_mark;
  }

  bool startsWith(const std::string & prefix) {
    TrieNode* r = &root;
    for (auto c : prefix) {
      r = find<false>(r, c);
      if (!r) {
        return false;
      }
    }
    return true;
  }
};
