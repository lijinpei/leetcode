struct ListNode {
  int val;
  ListNode *next;
  ListNode(int x) : val(x), next(nullptr) {}
};

class Solution {
public:
  ListNode *reverseBetween(ListNode *head, int m, int n) {
    ListNode** lp;
    ListNode* p = head;
    if (m == 1) {
      lp = &head;
    } else {
      for (int i = 2; i < m; ++i) {
        if (p) {
          p = p->next;
        }
      }
      if (!p->next) {
        return head;
      }
      lp = &p->next;
      p = p->next;
    }
    ListNode* p0 = p, *p1 = p0->next;
    for (int i = m; i < n; ++i) {
      ListNode *np1 = p1->next;
      p1->next = p0;
      p0 = p1;
      p1 = np1;
    }
    p->next = p1;
    *lp = p0;
    return head;
  }
};
