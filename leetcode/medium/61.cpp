#include <utility>

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(nullptr) {}
};

class Solution {
public:
  ListNode *rotateRight(ListNode *head, int k) {
    int n = 0;
    ListNode* lp = head;
    for (ListNode* p = head; p; p = p->next) {
      ++n;
      lp = p;
    }

    if (!n) {
      return nullptr;
    }
    k %= n;
    if (!k) {
      return head;
    }
    k = n - k;
    ListNode* p = head;
    while (--k) {
      p = p->next;
    }
    lp->next = head;
    return std::exchange(p->next, nullptr);
  }
};
