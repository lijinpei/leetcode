#include <vector>
#include <string>
#include <map>

class Solution {
  struct Str {
    int length;
    int arr[26];
    bool operator<(const Str & rhs) const {
      if (length != rhs.length) {
        return length < rhs.length;
      }
      for (int i = 0; i < 26; ++i) {
        if (arr[i] != rhs.arr[i]) {
          return arr[i] < rhs.arr[i];
        }
      }
      return false;
    }
    Str(const std::string & s) : arr{} {
      length = s.size();
      for (auto c : s) {
        ++arr[c - 'a'];
      }
    }
  };
public:
  std::vector<std::vector<std::string>> groupAnagrams(std::vector<std::string>& strs) { 
    std::map<Str, int> map;
    for (const auto & s : strs) {
      ++map[Str(s)];
    }
    std::vector<std::vector<std::string>> ret;
    ret.resize(map.size());
    int i = 0;
    for (auto & kv : map) {
      ret[i].reserve(kv.second);
      kv.second = i++;
    }
    for (const auto & s : strs) {
      ret[map[Str(s)]].push_back(s);
    }
    return ret;
  }
};
