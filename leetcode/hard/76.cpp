#include <iostream>
#include <string>
#include <vector>

struct str_node {
  int next, prev, next_ch;
};

class Solution {
  static constexpr int C_NUM = 256;
public:
  std::string minWindow(const std::string & str1, const std::string & str2) {
    int s1 = str1.size(), s2 = str2.size();
    if (0 == s1 || s2 > s1) {
      return "";
    }
    // str_vec[s1] is tail, str_vec[s1 + 1] is head
    std::vector<str_node> str_vec(s1 + 2, {-1, -1, -1}); 
    str_node &sh = str_vec[s1 + 1], &st = str_vec[s1];
    st.prev = s1 + 1;
    sh.next = s1;

    int first_char[C_NUM], last_char[C_NUM];
    for (auto &v : first_char) {
      v = -1;
    }
    for (auto &v : last_char) {
      v = -1;
    }
    int need_count[C_NUM] = {0};
    bool need[C_NUM] = {false};
    for (int c : str2) {
      need[c] = true;
      ++need_count[c];
    }
    int total_need_count = s2;
    int ans = s1 + 1, p = -1;
    for (int i = 0; i < s1; ++i) {
      int c = str1[i];
      int &hc = first_char[c], &tc = last_char[c];
      if (!need[c]) {
        continue;
      }
      // add c to the tail
      str_node & hc_i = str_vec[i];
      hc_i.next = s1;
      hc_i.prev = st.prev;
      str_vec[st.prev].next = i;
      st.prev = i;

      str_vec[i].next_ch = -1;
      if (tc != -1) {
        str_vec[tc].next_ch = i;
      }
      tc = i;
      if (-1 == hc) {
        hc = i;
      }
      if (!need_count[c]) {
        // remove first c
        str_node & hc_n = str_vec[hc];
        str_vec[hc_n.next].prev = hc_n.prev;
        str_vec[hc_n.prev].next = hc_n.next;
        hc = str_vec[hc].next_ch;
      } else {
        --need_count[c];
        --total_need_count;
        if (hc == -1) {
          hc = i;
        }
      }
      // update ans
      if (total_need_count) {
        continue;
      }
      int p1 = sh.next, ans1 = i - p1 + 1;
      if (ans1 < ans) {
        ans = ans1;
        p = p1;
      }
    }
    if (p != -1) {
      return str1.substr(p, ans);
    } else {
      return std::string();
    }
  }
};

int main() {
  Solution sol;
  //std::string s = sol.minWindow("zechiwcmjktroasetkzxlxpdibkeiqdhuhqfdsrmfmfvny", "ziiahux");
  //std::string s = sol.minWindow("AbabbbAbaA", "Bab");
  std::string s = sol.minWindow("cabefgecdaecf", "cae");
  std::cout << s.size() << std::endl;
  std::cout << s << std::endl;
}
