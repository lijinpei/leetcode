#include <cstdint>
#include <stack>
#include <utility>

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
public:
  bool findTarget(TreeNode* root, int k) {
    if (!root) {
      return false;
    }
    auto mark = [](TreeNode* p, uintptr_t m) -> TreeNode* {
      return reinterpret_cast<TreeNode*>((uintptr_t(p) + m));
    };
    auto get_mark = [](TreeNode* p) -> std::pair<TreeNode*, uintptr_t> {
      const uintptr_t m = uintptr_t(3);
      uintptr_t up = reinterpret_cast<uintptr_t>(p);
      return {reinterpret_cast<TreeNode*>(up & ~uintptr_t(m)), up & uintptr_t(m)};
    };
    enum State : uintptr_t {
      Visit_Left,
      Visit_Self,
      Visit_Right
    };
    std::stack<TreeNode*> s1, s2;
    {
      TreeNode* p = root;
      while (true) {
        s1.push(mark(p, Visit_Left));
        if (p->left) {
          p = p->left;
        } else {
          s1.top() = mark(p, Visit_Self);
          break;
        }
      }
    }
    {
      TreeNode* p = root;
      while (true) {
        s2.push(mark(p, Visit_Right));
        if (p->right) {
          p = p->right;
        } else {
          s2.top() = mark(p, Visit_Self);
          break;
        }
      }
    }
    auto get_next = [&](std::stack<TreeNode*> & st) -> TreeNode* {
      TreeNode *p = st.top();
      while (true) {
        auto res = get_mark(p);
        if (res.second == Visit_Left) {
          st.top() = mark(res.first, Visit_Self);
          return res.first;
        } else if (res.second == Visit_Self && res.first->right) {
          p = res.first;
          st.top() = mark(p, Visit_Right);
          p = p->right;
          while (true) {
            st.push(mark(p, Visit_Left));
            if (p->left) {
              p = p->left;
            } else {
              return p;
            }
          }
        } else {
          st.pop();
          if (st.empty()) {
            return nullptr;
          }
          p = st.top();
        }
      }
    };
    auto get_prev = [&](std::stack<TreeNode*> & st) -> TreeNode* {
      TreeNode *p = st.top();
      while (true) {
        auto res = get_mark(p);
        if (res.second == Visit_Right) {
          st.top() = mark(res.first, Visit_Self);
          return res.first;
        } else if (res.second == Visit_Self && res.first->left) {
          p = res.first;
          st.top() = mark(p, Visit_Left);
          p = p->left;
          while (true) {
            st.push(mark(p, Visit_Right));
            if (p->right) {
              p = p->right;
            } else {
              return p;
            }
          }
        } else {
          st.pop();
          if (st.empty()) {
            return nullptr;
          }
          p = st.top();
        }
      }
    };
    TreeNode* p1 = get_mark(s1.top()).first, *p2 = get_mark(s2.top()).first;
    if (p1 == p2) {
      return false;
    }
    while (true) {
      int v1 = p1->val;
      while (true) {
        int v2 = p2->val;
        int v3 = v1 + v2;
        if (v3 == k) {
          return true;
        }
        if (v3 < k) {
          break;
        }
        p2 = get_prev(s2);
        if (p1 == p2) {
          return false;
        }
      }
      p1 = get_next(s1);
      if (!p1 || p1 == p2) {
        return false;
      }
    }
  }
};
