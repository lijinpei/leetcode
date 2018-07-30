#include <cassert>
/**
 * // This is the interface that allows for creating nested lists.
 * // You should not implement it, or speculate about its implementation
 * class NestedInteger {
 *   public:
 *     // Constructor initializes an empty nested list.
 *     NestedInteger();
 *
 *     // Constructor initializes a single integer.
 *     NestedInteger(int value);
 *
 *     // Return true if this NestedInteger holds a single integer, rather than a nested list.
 *     bool isInteger() const;
 *
 *     // Return the single integer that this NestedInteger holds, if it holds a single integer
 *     // The result is undefined if this NestedInteger holds a nested list
 *     int getInteger() const;
 *
 *     // Set this NestedInteger to hold a single integer.
 *     void setInteger(int value);
 *
 *     // Set this NestedInteger to hold a nested list and adds a nested integer to it.
 *     void add(const NestedInteger &ni);
 *
 *     // Return the nested list that this NestedInteger holds, if it holds a nested list
 *     // The result is undefined if this NestedInteger holds a single integer
 *     const vector<NestedInteger> &getList() const;
 * };
 */
class Solution {
  static int parseNumber(const std::string & s, int & p) {
    bool neg = false;
    if (s[p] == '-') {
      neg = true;
      ++p;
    }
    int v = 0;
    while (std::isdigit(s[p])) {
      v = v * 10 + s[p++] - '0';
    }
    return neg ? -v : v;
  }
  NestedInteger deserialize_list(const std::string & s, int & p) {
    assert(s[p] == '[');
    ++p;
    NestedInteger ret;
    if (s[p] == ']') {
      ++p;
      return ret;
    }
    while (true) {
      if (std::isdigit(s[p]) || s[p] == '-') {
        ret.add(NestedInteger(parseNumber(s, p)));
        if (']' == s[p++]) {
          return ret;
        }
      } else {
        ret.add(deserialize_list(s, p));
        if (']' == s[p++]) {
          return ret;
        }
      }
    }
  }
  NestedInteger deserialize_impl(const std::string & s, int & p) {
    if (s[p] == '[') {
      return deserialize_list(s, p);
    }
    return NestedInteger(parseNumber(s, p));
  }
public:
    NestedInteger deserialize(const std::string & s) {
      int p = 0;
      return deserialize_impl(s, p);
    }
};
