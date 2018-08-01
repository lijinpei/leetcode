#include <vector>
#include <algorithm>

class Solution {
  class SolutionImpl {
    std::vector<int> &nums1, &nums2;
    int k;
    std::vector<int> st1, st2;
    std::vector<int> max_number;

    static bool larger(std::vector<int> &nums1, int p1, std::vector<int> &nums2,
                       int p2) {
      int s1 = nums1.size();
      int s2 = nums2.size();
      for (; p1 < s1 && p2 < s2; ++p1, ++p2) {
        if (nums1[p1] == nums2[p2]) {
          continue;
        }
        return nums1[p1] > nums2[p2];
      }
      return p1 != s1;
    }

    static void maxNumber(std::vector<int> &nums, int k, std::vector<int> &st) {
      st.resize(0);
      for (int i = 0, s = nums.size(); i < s; ++i) {
        int v = nums[i];
        while (int(st.size()) + s - i - 1 >= k && !st.empty() && st.back() < v) {
          st.pop_back();
        }
        if (int(st.size()) < k) {
          st.push_back(v);
        }
      }
    }
    void merge(std::vector<int> &nums1, std::vector<int> &nums2) {
      max_number.resize(0);
      int s1 = nums1.size(), s2 = nums2.size();
      int p1 = 0, p2 = 0;
      while (p1 < s1 && p2 < s2) {
        if (larger(nums1, p1, nums2, p2)) {
          max_number.push_back(nums1[p1++]);
        } else {
          max_number.push_back(nums2[p2++]);
        }
      }
      if (p1 < s1) {
        for (; p1 < s1; ++p1) {
          max_number.push_back(nums1[p1]);
        }
      }
      if (p2 < s2) {
        for (; p2 < s2; ++p2) {
          max_number.push_back(nums2[p2]);
        }
      }
    }

  public:
    SolutionImpl(std::vector<int> &nums1, std::vector<int> &nums2, int k)
        : nums1(nums1), nums2(nums2), k(k), st1(k), st2(k), max_number(k) {}
    std::vector<int> calc() {
      int s1 = nums1.size();
      int s2 = nums2.size();
      std::vector<int> ans;
      for (int i = std::max(0, k - s2); i <= s1 && i <= k; ++i) {
        maxNumber(nums1, i, st1);
        maxNumber(nums2, k - i, st2);
        merge(st1, st2);
        if (ans.empty() || larger(max_number, 0, ans, 0)) {
          ans = max_number;
        }
      }
      return ans;
    }
  };
public:
  std::vector<int> maxNumber(std::vector<int> &nums1, std::vector<int> &nums2,
                             int k) {
    return SolutionImpl(nums1, nums2, k).calc();
  }
};
