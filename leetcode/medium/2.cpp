struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(nullptr) {}
};


class Solution {
  static ListNode* reverse(ListNode* L) {
    ListNode* L0 = L;
    ListNode* L1 = L->next;
    while (L1) {
      ListNode* L2 = L1->next;
      L1->next = L;
      L = L1;
      L1 = L2;
    }
    L0->next = nullptr;
    return L;
  }

  static ListNode* add(ListNode* L1, ListNode* L2) {
    int carr = 0;
    ListNode dumb(0);
    ListNode* L3 = & dumb;
    while (L1 && L2) {
      int v1 = L1->val;
      int v2 = L2->val;
      int v = v1 + v2 + carr;
      int v3 = v % 10;
      carr = v / 10;
      ListNode * L4 = new ListNode(v3);
      L3->next = L4;
      L3 = L4;
      L1 = L1->next;
      L2 = L2->next;
    }
    if (L2) {
      L1 = L2;
    }
    while (L1) {
      int v1 = L1->val;
      int v = v1 + carr;
      int v3 = v % 10;
      carr = v / 10;
      ListNode * L4 = new ListNode(v3);
      L3->next = L4;
      L3 = L4;
      L1 = L1->next;
    }
    if (carr) {
      ListNode * L4 = new ListNode(carr);
      L3->next = L4;
      L3 = L4;
    }
    return dumb.next;
  }

public:
    ListNode* addTwoNumbers(ListNode* L1, ListNode* L2) {
      //L1 = reverse(L1);
      //L2 = reverse(L2);
      return add(L1, L2);
    }
};
