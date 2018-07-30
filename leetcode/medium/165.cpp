#include <iostream>
#include <string>

class Solution {
  struct Version {
    const char * p, *pe;
    operator bool() {
      return p != pe;
    }
    static Version Zero() {
      static const char *str = "0";
      return {str, str + 1};
    }
  };
  Version getVersion(const char *&p, const char* pe) {
    const char *p0 = p;
    for (; p < pe; ++p) {
      if ('.' == *p) {
        return {p0, p++};
      }
    }
    return {p0, p};
  }
  int compare(const Version & v1, const Version & v2) {
    /*
    std::cout << "Print version1:\n";
    for (const char * p = v1.p; p < v1.pe; ++p) {
      std::cout << *p;
    }
    std::cout << std::endl;
    std::cout << "Print version2\n";
    for (const char * p = v2.p; p < v2.pe; ++p) {
      std::cout << *p;
    }
    std::cout << std::endl;
    */
    const char * p1 = v1.p;
    for (; p1 < v1.pe && '0' == *p1; ++p1) {
      continue;
    }
    const char * p2 = v2.p;
    for (; p2 < v2.pe && '0' == *p2; ++p2) {
      continue;
    }
    int l1 = v1.pe - p1, l2 = v2.pe - p2;
    /*
    std::cout << l1 << std::endl;
    std::cout << l2 << std::endl;
    */
    if (!l1) {
      return l2 ? -1 : 0;
    }
    if (!l2) {
      return l1 ? 1 : 0;
    }
    if (l1 > l2) {
      return 1;
    }
    if (l1 < l2) {
      return -1;
    }
    for (int i = 0; i < l1; ++i) {
      char c1 = p1[i], c2 = p2[i];
      if (c1 > c2) {
        return 1;
      }
      if (c1 < c2) {
        return -1;
      }
    }
    return 0;
  }
public:
  int compareVersion(const std::string & version1, const std::string & version2) {
    const char* p1 = version1.data(), *p2 = version2.data();
    const char* pe1 = version1.data() + version1.size(), *pe2 = version2.data() + version2.size();
    while (true) {
      if (p1 == pe1 && p2 == pe2) {
        break;
      }
      auto v1 = getVersion(p1, pe1);
      auto v2 = getVersion(p2, pe2);
      auto ret = compare(v1, v2);
      if (ret) {
        return ret;
      }
    }
    return 0;
  }
};

int main() {
  Solution sol;
  std::cout << sol.compareVersion("1", "01");
}
