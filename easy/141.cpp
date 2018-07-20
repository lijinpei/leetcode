/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    bool hasCycle(ListNode *head) {
      ListNode* head1 = head;
      while (head && head1) {
        head = head->next;
        head1 = head1->next;
        if (!head1) {
          return false;
        }
        head1 = head1->next;
        if (head == head1) {
          return true;
        }
      }
      return false;
    }
};
