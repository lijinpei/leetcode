#include <iostream>
#include <cassert>
#include <algorithm>
#include <string>
#include <vector>
#include <forward_list>
#include <unordered_map>
#include <numeric>

class TermTy;
class PolynomialTy;
class Solution;

TermTy operator*(const TermTy &, const TermTy &);
bool operator<(const TermTy &, const TermTy &);
bool sameTerm(const TermTy &, const TermTy &);
template <bool isMinus = false>
PolynomialTy operator+(const PolynomialTy &, const PolynomialTy &);
PolynomialTy operator-(const PolynomialTy &, const PolynomialTy &);
PolynomialTy operator*(const PolynomialTy &, const PolynomialTy &);

class TermTy {
  int constant;
  mutable std::vector<std::pair<int, int>> term;
  mutable int sum;

public:
  friend class PolynomialTy;
  friend class Solution;
  friend TermTy operator*(const TermTy &, const TermTy &);
  friend bool operator<(const TermTy &, const TermTy &);
  friend bool sameTerm(const TermTy &, const TermTy &);
  template <bool isMinus>
  friend PolynomialTy operator+(const PolynomialTy &, const PolynomialTy &);
  friend PolynomialTy operator-(const PolynomialTy &, const PolynomialTy &);
  friend PolynomialTy operator*(const PolynomialTy &, const PolynomialTy &);


  bool isZero() const { return isConstant() && constant == 0; }

  bool isConstant() const { return !term.size(); }

  void calc_sum() const {
    int s = 0;
    for (const auto np : term) {
      s += np.second;
    }
    sum = s;
  };

  static TermTy Constant(int v) {
    TermTy ret;
    ret.constant = v;
    return ret;
  }

  static TermTy Variable(int v) {
    TermTy ret;
    ret.constant = 1;
    ret.term.push_back({v, 1});
    return ret;
  }

  void dump() const {
    std::cerr << constant << 'c';
    for (const auto & np : term) {
      std::cerr << np.first << ':' << np.second;
    }
  }
};

TermTy operator*(const TermTy &t1, const TermTy &t2) {
  if (t1.isZero()) {
    return t1;
  }
  if (t2.isZero()) {
    return t2;
  }
  TermTy ret;
  int s1 = t1.term.size(), s2 = t2.term.size();
  ret.term.reserve(s1 + s2);
  ret.constant = t1.constant * t2.constant;
  int i1 = 0, i2 = 0;
  while (i1 < s1 && i2 < s2) {
    int n1 = t1.term[i1].first, p1 = t1.term[i1].second;
    int n2 = t2.term[i2].first, p2 = t2.term[i2].second;
    if (n1 == n2) {
      if (p1 + p2 != 0) {
        ret.term.emplace_back(n1, p1 + p2);
      }
      ++i1;
      ++i2;
    } else if (n1 < n2) {
      ret.term.emplace_back(n1, p1);
      ++i1;
    } else {
      ret.term.emplace_back(n2, p2);
      ++i2;
    }
  }
  while (i1 < s1) {
    ret.term.emplace_back(t1.term[i1].first, t1.term[i1].second);
    ++i1;
  }
  while (i2 < s2) {
    ret.term.emplace_back(t2.term[i2].first, t2.term[i2].second);
    ++i2;
  }
  return ret;
}

// compare term by some lexicographical order
bool operator<(const TermTy &t1, const TermTy &t2) {
  int s1 = t1.term.size(), s2 = t2.term.size();
  if (s1 != s2) {
    return s1 < s2;
  }
  for (int i = 0; i < s1; ++i) {
    if (t1.term[i].first != t2.term[i].first) {
      return t1.term[i].first < t2.term[i].first;
    }
    if (t1.term[i].second != t2.term[i].second) {
      return t1.term[i].second < t2.term[i].second;
    }
  }
  return false;
}

// without considering constant, whether the two terms are the same
bool sameTerm(const TermTy &t1, const TermTy &t2) {
  if (t1.term.size() != t2.term.size()) {
    return false;
  }
  return std::equal(t1.term.begin(), t1.term.end(), t2.term.begin());
}

class PolynomialTy {
  mutable std::vector<TermTy> poly;
public:
  friend class TermTy;
  friend class Solution;
  friend TermTy operator*(const TermTy &, const TermTy &);
  friend bool operator<(const TermTy &, const TermTy &);
  friend bool sameTerm(const TermTy &, const TermTy &);
  template <bool isMinus>
  friend PolynomialTy operator+(const PolynomialTy &, const PolynomialTy &);
  friend PolynomialTy operator-(const PolynomialTy &, const PolynomialTy &);
  friend PolynomialTy operator*(const PolynomialTy &, const PolynomialTy &);

  void canonicalize() const {
    std::sort(poly.begin(), poly.end());
    int i1 = 0, i2 = 1, s = poly.size();
    while (i2 < s) {
      if (sameTerm(poly[i1], poly[i2])) {
        poly[i1].constant += poly[i2++].constant;
      } else {
        if (poly[i1].constant != 0) {
          poly[++i1] = poly[i2++];
        } else {
          poly[i1] = poly[i2++];
        }
      }
    }
    if (poly[i1].constant) {
    poly.resize(i1 + 1);
} else {
    poly.resize(i1);
}
  }
  bool isZero() const { return poly.size() == 1 && poly[0].isZero(); }
  static PolynomialTy Constant(int v) {
    PolynomialTy ret;
    ret.poly.push_back(TermTy::Constant(v));
    return ret;
  }
  static PolynomialTy Variable(int v) {
    PolynomialTy ret;
    ret.poly.push_back(TermTy::Variable(v));
    return ret;
  }
  void dump() const {
    for (const auto & p : poly) {
      p.dump();
      std::cerr << ' ';
    }
  }
};

template <bool isMinus>
PolynomialTy operator+(const PolynomialTy &p1,
                              const PolynomialTy &p2) {
  PolynomialTy ret;
  ret.poly.reserve(p1.poly.size() + p2.poly.size());
  ret.poly = p1.poly;
  for (const auto &v : p2.poly) {
    ret.poly.push_back(v);
    if (isMinus) {
      ret.poly.back().constant = -ret.poly.back().constant;
    }
  }
  return ret;
}

PolynomialTy operator-(const PolynomialTy &p1,
                              const PolynomialTy &p2) {
  return operator+<true>(p1, p2);
}

PolynomialTy operator*(const PolynomialTy &p1, const PolynomialTy &p2) {
  if (p1.isZero()) {
    return p1;
  }
  if (p2.isZero()) {
    return p2;
  }
  PolynomialTy ret;
  ret.poly.reserve(p1.poly.size() * p2.poly.size());
  for (const auto &t1 : p1.poly) {
    for (const auto &t2 : p2.poly) {
      ret.poly.push_back(t1 * t2);
    }
  }
  return ret;
}

class Solution {
  int variable_id;
  std::unordered_map<std::string, int> variable_map, env_map;
  std::unordered_map<int, std::string> rev_variable_map;

  int getVar(const std::string & str) {
    auto ret = variable_map.emplace(str, variable_id);
    if (ret.second) {
      rev_variable_map[variable_id] = str;
      return variable_id++;
    } else {
      return ret.first->second;
    }
  }

  bool getEnv(const std::string & str, int & v) {
    auto itor = env_map.find(str);
    if (itor != env_map.end()) {
      v = itor->second;
      return true;
    } else {
      return false;
    }
  }

  enum TokenKind {
    TK_Number,
    TK_Variable,
    TK_LeftParentheses,
    TK_RightParentheses,
    TK_Add,
    TK_Minus,
    TK_Mult,
    TK_Eos
  };
  TokenKind token_kind;
  int token_value;
  void getToken(int &i, const std::string &expression) {
    int s = expression.size();
    while (i < s && expression[i] == ' ') {
      ++i;
    }
    if (i < s) {
      switch (expression[i]) {
      case '(':
        token_kind = TK_LeftParentheses;
        ++i;
        break;
      case ')':
        token_kind = TK_RightParentheses;
        ++i;
        break;
      case '+':
        token_kind = TK_Add;
        ++i;
        break;
      case '-':
        token_kind = TK_Minus;
        ++i;
        break;
      case '*':
        token_kind = TK_Mult;
        ++i;
        break;
      default:
        if (std::isdigit(expression[i])) {
          int i1;
          for (i1 = i + 1; i1 < s; ++i1) {
            if (!std::isdigit(expression[i1])) {
              break;
            }
          }
          token_kind = TK_Number;
          token_value = std::stoi(expression.substr(i, i1 - i));
          i = i1;
        } else {
          int i1;
          for (i1 = i + 1; i1 < s; ++i1) {
            if (!std::isalpha(expression[i1])) {
              break;
            }
          }
          const std::string & str = expression.substr(i, i1 - i);
          i = i1;
          int v;
          if (getEnv(str, v)) {
            token_kind = TK_Number;
            token_value = v;
          } else {
            token_kind = TK_Variable;
            token_value = getVar(str);
          }
        }
      }
      return;
    }
    token_kind = TK_Eos;
  }

  std::vector<std::string> make_ans(const PolynomialTy &p) {
    p.canonicalize();
    int s = p.poly.size();
    std::vector<int> var_num(variable_id);
    std::iota(var_num.begin(), var_num.end(), 1);
    auto var_comp = [&](int v1, int v2) {
      return rev_variable_map[v1] < rev_variable_map[v2];
    };
    std::sort(var_num.begin(), var_num.end(), var_comp);
    std::vector<int> var_order(variable_id + 1);
    for (int i = 0; i < variable_id; ++i) {
      var_order[var_num[i]] = i;
    }
    auto term_comp = [&](const std::pair<int, int> & np1, const std::pair<int, int> & np2) {
      return var_order[np1.first] < var_order[np2.first];
    };
    for (const auto & t : p.poly) {
      t.calc_sum();
      std::sort(t.term.begin(), t.term.end(), term_comp);
    }
    auto poly_comp = [&](const TermTy & t1, const TermTy & t2) {
      if (t1.sum != t2.sum) {
        return t1.sum > t2.sum;
      }
      int i1 = 0, s1 = t1.term.size();
      int i2 = 0, s2 = t2.term.size();
      while (i1 < s1 && i2 < s2) {
        if (t1.term[i1].first != t2.term[i2].first) {
          return var_order[t1.term[i2].first] < var_order[t2.term[i2].first];
        }
        if (t1.term[i1].second != t2.term[i2].second) {
          return t1.term[i1].second > t2.term[i2].second;
        }
        ++i1;
        ++i2;
      }
      return false;
    };
    std::sort(p.poly.begin(), p.poly.end(), poly_comp);
    std::vector<std::string> ret;
    ret.reserve(s);
    for (const auto t : p.poly) {
      std::string str = std::to_string(t.constant);
      for (const auto pv : t.term) {
        std::string str1 = "*" + rev_variable_map[pv.first];
        for (int i = 0; i < pv.second; ++i) {
          str += str1;
        }
      }
      ret.push_back(str);
    }
    return ret;
  }
  void init(const std::vector<std::string> &evalvars,
            const std::vector<int> &evalints) {
    variable_id = 1;
    variable_map.clear();
    env_map.clear();
    for (int i = 0, s = evalvars.size(); i < s; ++i) {
      env_map[evalvars[i]] = evalints[i];
    }
  }

public:
  std::vector<std::string> basicCalculatorIV(const std::string &expression,
                                   const std::vector<std::string> &evalvars,
                                   const std::vector<int> &evalints) {
    init(evalvars, evalints);
    std::forward_list<TokenKind> operator_stack;
    std::forward_list<PolynomialTy> operand_stack;
    int i = 0;
    while (true) {
      getToken(i, expression);
      if (token_kind == TK_Eos) {
        break;
      }
      switch (token_kind) {
      case TK_Number:
      case TK_Variable: {
        operand_stack.push_front(token_kind == TK_Number ? PolynomialTy::Constant(token_value)
                                     : PolynomialTy::Variable(token_value));
        goto calc;
      } break;
      case TK_LeftParentheses:
        operator_stack.push_front(TK_LeftParentheses);
        break;
      case TK_RightParentheses: {
        PolynomialTy poly = PolynomialTy::Constant(0);
        while (operator_stack.front() != TK_LeftParentheses) {
          if (operator_stack.front() == TK_Add) {
            poly = poly + operand_stack.front();
          } else {
            poly = poly - operand_stack.front();
          }
          operator_stack.pop_front();
          operand_stack.pop_front();
        }
        operator_stack.pop_front();
        operand_stack.front() = operand_stack.front() + poly;
        goto calc;
      } break;
      case TK_Add:
      case TK_Minus:
      case TK_Mult:
        operator_stack.push_front(token_kind);
        break;
      default:
        assert(false);
      }
      continue;
    calc:
      if (!operator_stack.empty() && TK_Mult == operator_stack.front()) {
        PolynomialTy poly = operand_stack.front();
        operand_stack.pop_front();
        while (!operator_stack.empty() && TK_Mult == operator_stack.front()) {
          assert(!operand_stack.empty());
          PolynomialTy poly1 = operand_stack.front();
          operand_stack.pop_front();
          operator_stack.pop_front();
          poly = poly * poly1;
        }
        operand_stack.push_front(poly);
      }
    }
    if (operand_stack.empty()) {
      return {};
    } else {
      PolynomialTy poly = PolynomialTy::Constant(0);
      while (!operator_stack.empty()) {
        if (operator_stack.front() == TK_Add) {
          poly = poly + operand_stack.front();
        } else {
          poly = poly - operand_stack.front();
        }
        operator_stack.pop_front();
        operand_stack.pop_front();
      }
      poly = poly + operand_stack.front();
      return make_ans(poly);
    }
  }
};

void output(const std::vector<std::string> & v) {
  std::cerr << '[';
  bool b = false;
  for (const auto v1 : v) {
    if (b) {
      std::cerr << ", ";
    }
    b = true;
    std::cout << v1;
  }
  std::cerr << ']' << std::endl;
}

int main() {
  Solution sol;
  output(sol.basicCalculatorIV("e + 8 - a + 5", {"e"}, {1}));
  output(sol.basicCalculatorIV("e - 8 + temperature - pressure", {"e", "temperature"}, {1, 12}));
  output(sol.basicCalculatorIV("(e + 8) * (e - 8)", {}, {}));
  output(sol.basicCalculatorIV("a * b * c + b * a * c * 4", {}, {}));
  output(sol.basicCalculatorIV("((a - b) * (b - c) + (c - a)) * ((a - b) + (b - c) * (c - a))", {}, {}));
  output(sol.basicCalculatorIV("(5 - 1 - f) + 11 * (12 * d - p) + (y - ac) + (bk * 8 + 6 * cg * r)", {"d", "g", "h", "j", "l", "o", "s", "u", "v", "w", "af", "ag", "ah", "ak", "at", "au", "av", "aw", "az", "bc", "be", "bg", "bj", "bm", "bn", "bq", "br", "bs", "bt", "bu", "bv", "bw", "bx", "by", "bz", "ca", "cd", "ce", "cf", "ch", "ci", "ck", "cq", "cr", "cs", "cu", "cv"}, {3, 6, 7, 9, 11, 1, 5, 7, 8, 9, 10, 11, 12, 2, 11, 12, 0, 1, 4, 12, 1, 3, 6, 9, 10, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 2, 5, 6, 7, 9, 10, 12, 5, 6, 7, 9, 10}));
}
