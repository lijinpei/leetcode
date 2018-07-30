package main

var sol, nums []int
var ret [][]int
var sn int

func search(p, v1 int) {
  if len(sol) >= 2 {
    cpy := make([]int, len(sol))
    copy(cpy, sol)
    ret = append(ret, cpy)
  }
  s := len(sol)
  for i := p; i < sn; i++ {
    v := nums[i]
    if v <= v1 {
      continue
    }
    before := false
    for j := p; j < i; j++ {
      if nums[j] == v {
        before = true
        break
      }
    }
    if before {
      continue;
    }
    for j := i; j < sn; j++ {
      if nums[j] == v {
        sol = append(sol, v)
        search(j + 1, v)
      }
    }
    sol = sol[:s]
  }
}

func findSubsequences(nums_ []int) [][]int {
  nums = nums_
  sn = len(nums)
  sol = []int{}
  ret = [][]int{}
  search(0, -101)
  return ret
}

func main() {
  nums := [...]int{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15}
  for i := 0; i < 100; i++ {
    findSubsequences(nums[:])
  }
}
