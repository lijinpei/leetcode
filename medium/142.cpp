struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(nullptr) {}
};

class Solution {
public:
  ListNode *detectCycle(ListNode *head) {
    if (!head || !head->next) {
      return nullptr;
    }
    ListNode *ret = head, *h0 = head;
    while (true) {
      if (ret->next) {
        ret = ret->next;
        if (ret->next) {
          ret = ret->next;
        } else {
          return nullptr;
        }
      } else {
        return nullptr;
      }
      if (head->next) {
        head = head->next;
      } else {
        return nullptr;
      }
      if (head == ret) {
        while (h0 != ret) {
          h0 = h0->next;
          ret = ret->next;
        }
        return ret;
      }
    }
  }
};
