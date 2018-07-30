package main

import "fmt"

type pair struct {
  val int
  pos int
}

func decPush(stack []pair, val int, pos int) []pair {
  for len(stack) != 0 {
    if stack[len(stack) - 1].val <= val {
      stack = stack[:len(stack) - 1]
    } else {
      break
    }
  }
  return append(stack, pair{val, pos})
}

func incPush(stack []pair, val int, pos int) []pair {
  for len(stack) != 0 {
    if stack[len(stack) - 1].val >= val {
      stack = stack[:len(stack) - 1]
    } else {
      break
    }
  }
  return append(stack, pair{val, pos})
}

func peel(stack []pair, pos int) []pair {
  for len(stack) != 0 {
    if stack[0].pos < pos {
      stack = stack[1:]
    } else {
      break
    }
  }
  return stack
}

func containsNearbyAlmostDuplicate(nums []int, k int, t int) bool {
  l := len(nums)
  if k <= 0 || t < 0 {
    return false
  }
  s1 := make([]pair, 0, l)
  s2 := make([]pair, 0, l)
  for pos, val := range nums {
    s1 = peel(s1, pos - k)
    s2 = peel(s2, pos - k)
    if len(s1) != 0 {
      v := val - s1[0].val
      if (v >= 0 && v <= t) {
        return true
      }
    }
    if len(s2) != 0 {
      v := s2[0].val - val
      if (v >= 0 && v <= t) {
        return true;
      }
    }
    s1 = incPush(s1, val, pos)
    s2 = decPush(s2, val, pos)
  }
  return false
}

func main() {
  nums := [3]int{7, 1, 3}
  fmt.Printf("%v\n", containsNearbyAlmostDuplicate(nums[:], 2, 3))
}
