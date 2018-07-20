/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
#include <utility>

class Solution {
  static std::pair<int, ListNode*> reverse(ListNode* head) {
    int ret = 0;
    ListNode* prev = nullptr;
    while (head) {
      ++ret;
      ListNode* head1 = head->next;
      head->next = prev;
      prev = head;
      head = head1;
    }
    return {ret, prev};
  }
  static ListNode* forward(ListNode* head, int n) {
    while (n--) {
      head = head->next;
    }
    return head;
  }
public:
    ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
      auto res1 = reverse(headA);
      auto res2 = reverse(headB);
      if (res2.second != headA) {
        reverse(res1.second);
        reverse(res2.second);
        return nullptr;
      }
      auto res3 = reverse(res1.second);
      return forward(headA, (res1.first + res2.first + res3.first - 3) / 2 + 1 - res3.first);
    }
};
