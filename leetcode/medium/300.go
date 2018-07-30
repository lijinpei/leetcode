func lengthOfLIS(nums []int) int {
  l := len(nums)
  if l < 2 {
    return l
  }
  st := nums[0:1]
  s := 1
  for i := 1; i < l; i++ {
    v := nums[i]
    if v > st[s - 1] {
      st = append(st, v)
      s++
      continue
    }
    l, r := 0, s
    for l + 1 < r {
      m := (l + r) / 2
      if v <= nums[m - 1] {
        r = m
      } else {
        l = m
      }
    }
    st[l] = v
  }
  return s
}
