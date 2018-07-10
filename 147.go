/**
 * Definition for singly-linked list.
 * type ListNode struct {
 *     Val int
 *     Next *ListNode
 * }
 */
func insertionSortList(head *ListNode) *ListNode {
  if head == nil {
    return nil
  }
  tail := head
  for next := head.Next; next != nil; {
    next1 := next.Next
    if next.Val <= head.Val {
      head, next.Next = next, head
    } else if next.Val >= tail.Val {
      tail, tail.Next = next, next
    } else {
      v := next.Val
      n := head
      for ; v > n.Next.Val; n = n.Next {
      }
      n.Next, next.Next = next, n.Next
    }
    next = next1
  }
  tail.Next = nil
  return head
}
