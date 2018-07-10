package main

type ListNode struct {
    Val int
    Next *ListNode
}

var bitvec []uint64

func resize(n int) {
  bitvec = make([]uint64, (n + 63) / 64)
}

func set(v uint) {
  var v1, v2 uint = v / 64, v % 64
  bitvec[v1] |= uint64(1) << v2
}


func test(v uint) bool {
  var v1, v2 uint = v / 64, v % 64
  if (bitvec[v1] & (uint64(1) << v2)) != 0 {
    return true
  } else {
    return false
  }
}

func listLen(head *ListNode) int {
  ret := 0
  for head != nil {
    ret++
    head = head.Next
  }
  return ret
}

func numComponents(head *ListNode, G []int) int {
  n := listLen(head)
  resize(n)
  for _, v := range G {
    set(uint(v))
  }
  in := false
  ret := 0
  for head != nil {
    if test(uint(head.Val)) {
      if !in {
        ret++
        in = true
      }
    } else {
      in = false
    }
    head = head.Next
  }
  return ret
}

func main() {
}

