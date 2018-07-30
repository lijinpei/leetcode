func sortColors(nums []int)  {
  l, r := 0, len(nums) - 1
  l0, r0 := l, r
  for l <= r {
    for l <= r {
      if 2 == nums[r] {
        nums[r0] = 2
        r0--
      } else if 0 == nums[r] {
        break
      }
      r--
    }
    if !(l <= r) {
      break
    }
    for l <= r{
      if 0 == nums[l] {
        nums[l0] = 0
        l0++
      } else if 2 == nums[l] {
        break
      }
      l++
    }
    if !(l <= r) {
      break
    }
    nums[l0] = 0
    nums[r0] = 2
    l0++
    r0--
    l++
    r--
  }
  for i := l0; i <= r0; i++ {
    nums[i] = 1
  }
}
