#include <string>

class Solution {
public:
  std::string complexNumberMultiply(const std::string &a,
                                    const std::string &b) {
    size_t p1, p2;
    int v1 = std::stoi(a, &p1), v2 = std::stoi(b, &p2);
    int v3 = std::stoi(a.substr(p1 + 1)), v4 = std::stoi(b.substr(p2 + 1));
    return std::to_string(v1 * v2 - v3 * v4) + "+" + std::to_string(v1 * v4 + v2 * v3) + "i";
  }
};
