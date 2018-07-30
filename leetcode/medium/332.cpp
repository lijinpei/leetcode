#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <utility>
#include <cstdint>
#include <unordered_map>

uint16_t V(const std::string & str) {
  return uint16_t(str[0] - 'A') << 10 | uint16_t(str[1] - 'A') << 5 | uint16_t(str[2] - 'A');
}

class Solution {
public:
  std::vector<std::string> findItinerary(std::vector<std::pair<std::string, std::string>> tickets) {
    int s = tickets.size();
    std::vector<uint32_t> tkt(s);
    std::unordered_map<uint16_t, uint16_t> hash_to_id;
    std::vector<uint16_t> id_to_hash(s + 1);
    std::vector<uint16_t> edge_num(s + 2);
    std::vector<uint16_t> edge_pos(s + 2);
    int id = 1;
    for (int i = 0; i < s; ++i) {
      uint32_t v1 = V(tickets[i].first);
      uint32_t v2 = V(tickets[i].second);
      auto& id1 = hash_to_id[v1];
      auto& id2 = hash_to_id[v2];
      if (!id1) {
        id_to_hash[id] = v1;
        id1 = id++;
      }
      if (!id2) {
        id_to_hash[id] = v2;
        id2 = id++;
      }
      ++edge_num[id1];
      tkt[i]= id1 << 16 | id2;
    }
    auto my_comp = [&](uint32_t v1, uint32_t v2) {
      uint32_t v3 = id_to_hash[(v1 >> 16)];
      uint32_t v4 = id_to_hash[(v2 >> 16)];
      if (v3 != v4) {
        return v3 < v4;
      }
      uint32_t v5 = id_to_hash[v1 & 0xffff];
      uint32_t v6 = id_to_hash[v2 & 0xffff];
      return v5 < v6;
    };
    std::sort(tkt.begin(), tkt.end(), my_comp);
    {
      uint16_t lp = (tkt[0] >> 16) - 1;
      for (int i = 0; i < s; ++i) {
        uint16_t np = tkt[i] >> 16;
        if (np != lp) {
          edge_pos[np] = i;
          lp = np;
        }
      }
    }
    std::vector<std::string> ret(s + 1);
    int ret_p = s;
    std::vector<uint16_t> st;
    st.reserve(s + 1);
    uint32_t st0 = hash_to_id[V("JFK")];
    st.push_back(st0);
    uint16_t lp = st0;
    while (!st.empty()) {
      if (!edge_num[lp]) {
        uint16_t p = id_to_hash[lp];
        char str[] = {char('A' + (p >> 10)), char('A' + (p >> 5 & 0x1f)), char('A' + (p & 0x1f)), '\0'};
        ret[ret_p--] = str;
        st.pop_back();
        lp = st.back();
      } else {
        --edge_num[lp];
        lp = tkt[edge_pos[lp]++];
        st.push_back(lp);
      }
    }
    return ret;
  }
};

int main() {
  Solution sol;
  std::vector<std::pair<std::string, std::string>> input{{"MUC","LHR"},{"JFK","MUC"},{"SFO","SJC"},{"LHR","SFO"}};
  auto ret = sol.findItinerary(input);
  for (auto v : ret) {
    std::cout << v << std::endl;
  }
}
