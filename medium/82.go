func deleteDuplicates(head *ListNode) *ListNode {
  for {
    if head == nil {
      return nil
    }
    if head.Next == nil {
      return head
    }
    hv := head.Val
    if hv != head.Next.Val {
      break
    }
    next := head.Next.Next
    for ; next != nil && next.Val == hv; next = next.Next {
    }
    head = next
  }
  ret := head
  next := head.Next
  for next != nil {
    if next.Next == nil {
      break
    }
    nv := next.Val
    next1 := next.Next
    flag := true
    for ; next1 != nil && next1.Val == nv; next1 = next1.Next {
      flag = false
    }
    if flag {
      head.Next = next
      head = next
      next = next.Next
    } else {
      next = next1
    }
  }
  head.Next = next
  return ret
}
