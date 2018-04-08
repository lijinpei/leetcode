struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(nullptr) {}
};

class Solution {
  static ListNode* reverse(ListNode* p) {
    static ListNode* tail;
    if (!p->next) {
      tail = p;
      return p;
    }
    auto ret = reverse(p->next);
    p->next = nullptr;
    tail->next = p;
    tail = p;
    return ret;
  }
public:
  void reorderList(ListNode* head) {
    int n = 0;
    for (ListNode* p = head; p; p = p->next) {
      ++n;
    }
    if (n <= 1) {
      return;
    }
    int m = (n - 1) / 2;
    ListNode*p = head;
    while (m--) {
      p = p->next;
    }
    ListNode* p1 = p->next, *p2 = p1;
    p->next = nullptr;
    p1 = reverse(p1);
    p = head;
    while (p && p1) {
      ListNode* np = p->next;
      ListNode* np1 = p1->next;
      p->next = p1;
      p1->next = np;
      p = np;
      p1 = np1;
    }
    if (n & 1) {
      p2->next = p;
    }
  }
};
