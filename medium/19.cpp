class Solution {
public:
  ListNode* removeNthFromEnd(ListNode* head, int n) {
    int l = 0;
    for (ListNode* p = head; p; p = p->next) {
      ++l;
    }
    l -= n;
    if (!l) {
      return head->next;
    }
    ListNode* h1 = head;
    while (--l) {
      h1 = h1->next;
    }
    h1->next = h1->next->next;
    return head;
  }
};
