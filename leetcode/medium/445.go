package main

type ListNode struct {
    Val int
    Next *ListNode
}

func addTwoNumbers_impl(h1 * ListNode, h2 * ListNode) * ListNode {
  carry := 0
  var l1, l2 *ListNode = nil, nil
  for h2 != nil {
    carry += h1.Val + h2.Val
    if carry >= 10 {
      h1.Val = carry - 10
      carry = 1
    } else {
      h1.Val = carry
      carry = 0
    }
    n1, n2 := h1, h2
    h1, h2 = h1.Next, h2.Next
    n1.Next, n2.Next = l1, l2
    l1, l2 = n1, n2
  }
  for h1 != nil {
    carry = h1.Val + carry
    if carry < 10 {
      h1.Val = carry
      carry = 0
    } else {
      h1.Val = carry - 10
      carry = 1
    }
    n1 := h1
    h1 = h1.Next
    n1.Next = l1
    l1 = n1
  }
  if carry != 0 {
    return &ListNode{carry, l1}
  } else {
    return l1
  }
}

func revList(head * ListNode) (*ListNode, int) {
  if head == nil {
    return nil, 0
  }
  ret := 1
  ln := head
  head = head.Next
  ln.Next = nil
  for head != nil {
    head, ln, head.Next = head.Next, head, ln
    ret++
  }
  return ln, ret
}

func addTwoNumbers(l1 *ListNode, l2 *ListNode) *ListNode {
  h1, n1 := revList(l1)
  h2, n2 := revList(l2)
  if n1 < n2 {
    h1, h2 = h2, h1
  }
  return addTwoNumbers_impl(h1, h2)
}

func main() {
}
