#include <iostream>
#include <cassert>
#include <unordered_map>
#include <forward_list>
#include <string>

enum ExpressionKind {
  EK_Add,
  EK_Mult,
  EK_Let,
  EK_Var,
  EK_Num
};

struct StringRef {
  int begin, end;
};

struct OperatorContext {
  ExpressionKind expr_kind;
  int operand_num; // number of operators that has been seen
  // value of operator has been seen, one value is enough
  union {
    StringRef str;
    int val;
  };
  OperatorContext(ExpressionKind ek) : expr_kind(ek), operand_num(0) {}
};

// benefits of a seperate impl class:
// 1. we are guaranteed a new evaluation context each Solution.evaluate() call
// 2. it's convenient to share certain variables(like the operator/symbol-table
// stack)
class SolutionImpl {
private:
  const std::string & expression;
  // each let expression introduce a new string-map on the stack of symbol_table
  std::forward_list<std::unordered_map<std::string, int>> symbol_table;
  // each let/add/mul introduce a new node on operator stack
  std::forward_list<OperatorContext> operator_stack;
  int expr_end;
  // before get_symbol(), pos is the next position to look at, other variabes
  // are not meaningful after get_symbol(), pos0 is the pos before get_symbol(),
  // next_kind is the kind of the symbol between [pos0, pos)
  int pos0, pos;
  ExpressionKind next_kind;
  // get_symbol() skips possible leading zeros, but not trailing ones
  void get_symbol() {
    while (pos < expr_end) {
      char c = expression[pos];
      if (c == '(' || c == ' ') {
        ++pos;
      } else {
        break;
      }
    }
    pos0 = pos;
    while (pos < expr_end) {
      char c = expression[pos];
      if (c == ')' || c == ' ') {
        break;
      } else {
        ++pos;
      }
    }
    char c = expression[pos0];
    if ((c <= '9' && c >= '0') || c == '-') {
      next_kind = EK_Num;
    } else {
      const std::string & var = expression.substr(pos0, pos - pos0);
      if (var == "let") {
        next_kind = EK_Let;
      } else if (var == "add") {
        next_kind = EK_Add;
      } else if (var == "mult") {
        next_kind = EK_Mult;
      } else {
        next_kind = EK_Var;
      }
    }
  }
  // this function is only used in evaluating let expression to determine if we
  // are at the last operand of the expression returns true is the next
  // non-blank character is ')', in this case, move pos next to ')' otherwise
  // return false and don't touch pos
  bool peek_right_parentheses() {
    int p1 = pos;
    for (; ; ++p1) {
      assert(p1 < expr_end);
      if (expression[p1] != ' ') {
        break;
      }
    }
    assert(p1 < expr_end);
    if (expression[p1] == ')') {
      pos = p1 + 1;
      return true;
    } else {
      return false;
    }
  }
  int get_var(const StringRef & str) {
    const std::string & s = expression.substr(str.begin, str.end - str.begin);
    for (const auto & st : symbol_table) {
      auto itor = st.find(s);
      if (itor != st.end()) {
        return itor->second;
      }
    }
    //std::cerr << s << std::endl;
    assert(false);
    return 0;
  }
  void put_var(const StringRef & str, int val) {
    (*symbol_table.begin())[expression.substr(str.begin, str.end - str.begin)] = val;
  }
  int eval_one() {
    bool expecting_val = true; // this is in fact expecting value or var in (let var val ...)
    int current_value;
    while (pos < expr_end) {
      while (expecting_val) {
        get_symbol();
        switch(next_kind) {
        case EK_Let:
          symbol_table.emplace_front();
          [[fallthrough]];
        case EK_Add:
        case EK_Mult:
          // predicate: let should bind at least one variable
          // if this is not true, we need to peek here to dsitinguish
          // (let v 1 v) (let v 1 (let v))
          operator_stack.push_front(next_kind);
          break;
        case EK_Var:
          assert(!operator_stack.empty());
            if (operator_stack.front().expr_kind == EK_Let &&
                operator_stack.front().operand_num == 0) {
              if (peek_right_parentheses()) {
                current_value = get_var({pos0, pos - 1});
                expecting_val = false;
              } else {
                operator_stack.front().operand_num = 1;
                operator_stack.front().str = {pos0, pos};
              }
            } else {
              //std::cout << pos0 << ' ' << pos << std::endl;
              current_value = get_var({pos0, pos});
              expecting_val = false;
          }
          break;
        case EK_Num:
          current_value = std::stoi(expression.substr(pos0, pos - pos0));
          expecting_val = false;
          break;
        default:
          assert(false);
        }
      }
      do {
        if (operator_stack.empty()) {
          return current_value;
        }
        OperatorContext  & oc = operator_stack.front();
        switch (oc.expr_kind) {
        case EK_Add:
        case EK_Mult:
          if (oc.operand_num == 0) {
            oc.operand_num = 1;
            oc.val = current_value;
            expecting_val = true;
          } else {
            if (oc.expr_kind == EK_Add) {
              current_value = oc.val + current_value;
            } else {
              current_value = oc.val * current_value;
            }
            operator_stack.pop_front();
            ++pos;
          }
          break;
        case EK_Let:
          if (oc.operand_num == 1) {
            put_var(oc.str, current_value);
            oc.operand_num = 0;
            expecting_val = true;
          } else {
            symbol_table.pop_front();
            operator_stack.pop_front();
            ++pos;
          }
          break;
        default:
          assert(false);
        }
      } while (!expecting_val);
    }
    return current_value;
  }
public:
  SolutionImpl(const std::string & expression_) : expression(expression_), expr_end(expression.size()), pos(0) {}
  int eval() {
    return eval_one();
  }
};

class Solution {
public:
  int evaluate(const std::string & expression) {
    return SolutionImpl(expression).eval();
  }
};

int main() {
  Solution sol;
  //std::cout << sol.evaluate("(add 1 2)") << std::endl;
  //std::cout << sol.evaluate("(let a1 3 b2 (add a1 1) b2)") << std::endl;
  //std::cout << sol.evaluate("(let x 2 (add (let x 3 (let x 4 x)) x))") << std::endl;
  //std::cout << sol.evaluate("(let x 1 y 2 x (add x y) (add x y))") << std::endl;
  //std::cout << sol.evaluate("(let x 3 x 2 x)") << std::endl;
  //std::cout << sol.evaluate("(let x 2 (mult x (let x 3 y 4 (add x y))))") << std::endl;
  std::cout << sol.evaluate("(let x 3 y 4 (add x y))") << std::endl;
  std::cout << sol.evaluate("(mult 2 (let x 3 y 4 (add x y)))") << std::endl;
  std::cout << sol.evaluate("(let x 2 (mult x (let x 3 y 4 (add x y))))") << std::endl;
  std::cout << sol.evaluate("(let x 2 (mult x 5))") << std::endl;
  std::cout << sol.evaluate("(mult 3 (add 2 3))") << std::endl;
  std::cout << sol.evaluate("(add 1 2)") << std::endl;
  std::cout << sol.evaluate("(let x 7 -12)") << std::endl;
}
