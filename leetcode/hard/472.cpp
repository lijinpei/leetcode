#include <algorithm>
#include <iostream>
#include <list>
#include <string>
#include <vector>

struct TrieNode {
  TrieNode *child, *sibling;
  TrieNode *fail, *output;
  int depth;
  char c;
  bool is_end;
  TrieNode(char c, TrieNode *child, TrieNode *sibling)
      : child(child), sibling(sibling), fail(nullptr), output(nullptr),
        depth(0), c(c), is_end(false) {}
};

template <bool CanInsert> TrieNode *find_child(TrieNode *p, char c) {
  if (!p->child || p->child->c > c) {
    if (CanInsert) {
      p->child = new TrieNode(c, nullptr, p->child);
    } else {
      return nullptr;
    }
  }
  if (p->child->c == c) {
    return p->child;
  }
  p = p->child;
  TrieNode *p1 = p->sibling;
  while (p1) {
    if (p1->c == c) {
      return p1;
    }
    if (p1->c < c) {
      p = p1;
      p1 = p1->sibling;
    } else {
      if (CanInsert) {
        return p->sibling = new TrieNode(c, nullptr, p1);
      } else {
        return nullptr;
      }
    }
  }
  if (CanInsert) {
    return p->sibling = new TrieNode(c, nullptr, nullptr);
  } else {
    return nullptr;
  }
}

TrieNode *add_to_trie(TrieNode &root, const std::string &str) {
  TrieNode *p = &root;
  for (auto c : str) {
    p = find_child<true>(p, c);
  }
  p->is_end = true;
  return p;
}

void build_ac_tree(TrieNode *root) {
  root->depth = 0;
  root->fail = nullptr;
  root->output = nullptr;
  root->is_end = false;
  std::list<std::pair<TrieNode *, TrieNode *>> queue;
  for (TrieNode *p = root->child; p; p = p->sibling) {
    p->output = nullptr;
    p->depth = 1;
    queue.emplace_back(nullptr, p);
  }
  while (!queue.empty()) {
    TrieNode *f = queue.front().first;
    TrieNode *p = queue.front().second;
    queue.pop_front();
    char c = p->c;
    while (f) {
      TrieNode *p1 = find_child<false>(f, c);
      if (p1) {
        f = p1;
        break;
      }
      f = f->fail;
    }
    if (!f) {
      f = root;
    }
    p->fail = f;
    p->output = f->is_end ? f : f->output;
    int d = p->depth + 1;
    for (TrieNode *ch = p->child; ch; ch = ch->sibling) {
      queue.emplace_back(f, ch);
      ch->depth = d;
    }
  }
}

bool calc(TrieNode* root, const std::string & word) {
  int s = word.size();
  if (!s) {
    return false;
  }
  std::vector<bool> dp(s + 1);
  dp[0] = true;
  TrieNode* p = root;
  for (int i = 1; i <= s; ++i) {
    char c = word[i - 1];
    while (p) {
      TrieNode* p1 = find_child<false>(p, c);
      if (p1) {
        p = p1;
        break;
      } else {
        p = p->fail;
      }
    }
    if (!p) {
      p = root;
    } else {
      for (TrieNode* p1 = (p->is_end && i != s) ? p : p->output; p1; p1 = p1->output) {
        if (dp[i - p1->depth]) {
          dp[i] = true;
        }
      }
    }
  }
  return dp[s];
}

void checkdepth(TrieNode* r, int d) {
  if (r->depth != d) {
    std::cout << "wrong depth " << d << std::endl;
    return;
  }
  for (TrieNode* ch = r->child; ch; ch = ch->sibling) {
    checkdepth(ch, d + 1);
  }
}

class Solution {
public:
  std::vector<std::string>
  findAllConcatenatedWordsInADict(std::vector<std::string> &words) {
    auto str_length_comp = [](const std::string &s1, const std::string &s2) {
      return s1.size() < s2.size();
    };
    std::sort(words.begin(), words.end(), str_length_comp);
    int N = words.size();
    std::vector<std::string> ret;
    ret.reserve(N);
    TrieNode root(' ', nullptr, nullptr);
    for (int i = 0; i < N; ++i) {
      add_to_trie(root, words[i]);
    }
    build_ac_tree(&root);
    for (int i = 0; i < N; ++i) {
      if (calc(&root, words[i])) {
        ret.push_back(std::move(words[i]));
      }
    }
    return std::move(ret);
  }
};

int main() {
  std::vector<std::string> input = {"cat", "cats",        "catsdogcats",
                                    "dog", "dogcatsdog",  "hippopotamuses",
                                    "rat", "ratcatdogcat"};
  Solution sol;
  auto ret = sol.findAllConcatenatedWordsInADict(input);
  for (auto r : ret) {
    std::cout << r << std::endl;
  }
}
