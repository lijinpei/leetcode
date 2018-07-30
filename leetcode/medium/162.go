func findPeakElement(nums []int) int {
  l, r := 0, len(nums)
  if r == 1 || nums[0] > nums[1] {
    return 0
  }
  if nums[r - 1] > nums[r - 2] {
    return r - 1
  }
  for l + 1 < r {
    m := (l + r) / 2
    if nums[m] > nums[m - 1] {
      if nums[m] > nums[m + 1] {
        return m
      } else {
        l = m
      }
    } else {
      r = m
    }
  }
  return l + 1
}
