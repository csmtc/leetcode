#include "iostream"
#include "string"
#include "vector"
using namespace std;

class BaseExpr {
public:
  virtual void match(vector<string> input, vector<string> &output);
  virtual string gotoNextPos(string x);
};

class LiteralExpr : BaseExpr {
public:
  LiteralExpr() {}
  LiteralExpr(string expr) { this->expr = expr; }
  void match(vector<string> input, vector<string> &output) override {
    for (auto x : input) {
      auto y = gotoNextPos(x);
      if (y != "") {
        output.push_back(y);
      }
    }
  }
  string gotoNextPos(string x) override {
    for (auto cx = x.begin(), ce = expr.begin();
         cx < x.end() && ce < expr.end(); ++cx, ++ce) {
      if (*cx != *ce)
        return "";
    }
    return x.substr(expr.length());
  }

protected:
  string expr;
};

class RepeatExpr : BaseExpr {
public:
  void match(vector<string> input, vector<string> &output) override {
    for (auto x : input) {
      while (true) {
        auto y = gotoNextPos(x);
        if (y != "") {
          output.push_back(y);
          x = y;
        }
      }
    }
  }
  string gotoNextPos(string x) override { return expr.gotoNextPos(x); }

protected:
  BaseExpr expr;
};

typedef struct _struct_pattern {
  string str;
  bool repeat;
} pattern;
pattern ps[20];
typedef pair<char *, char *> state;
typedef vector<state> stateset;
class Solution {
public:
  bool isMatch(string s, string reg) {
    // 分析模式串，扫描其中的*修饰的子模式
    int ptop = -1;
    int i = 0, j = 0, len;
    while (j < reg.length()) {
      if (reg[j] == '*') {
        // 非重复字符的串
        len = j - i - 1;
        if (len) {
          ps[++ptop].str = reg.substr(i, len);
          ps[ptop].repeat = false;
        }
        // 重复的字符
        ps[++ptop].str = reg.substr(j - 1, 1);
        ps[ptop].repeat = true;
        i = 1 + j;
      }
      ++j;
    }
    // 最后一个子模式如果没有*修饰
    if (reg[reg.length() - 1] != '*') {
      ps[++ptop].str = reg.substr(i, reg.length());
      ps[ptop].repeat = false;
    }

    stateset in = {{(char *)s.data(), (char *)s.data() + s.length()}};
    stateset out;

    for (auto p = ps; p <= &ps[ptop]; ++p) {
      if (p->repeat) {
        match_str_repeat(in, out, p->str);
      } else {
        match_str(in, out, p->str);
      }
      in = out;
    }

    bool match = false;
    for (auto x : out) {
      match = match || x.first == x.second;
    }
    return match;
  }

protected:
  void match_str(stateset in, stateset &out, string expr) {
    out.clear();
    for (auto x : in) {
      auto y = gotoNextPos(x, expr);
      if (y.first != nullptr) {
        out.push_back(y);
      }
    }
  }
  void match_str_repeat(stateset in, stateset &out, string expr) {
    out.clear();
    for (auto x : in) {
      out.push_back(x); // 重复0次
      while (true) {
        auto y = gotoNextPos(x, expr);
        if (y.first != nullptr) {
          out.push_back(y);
          x = y;
        } else
          break;
      }
    }
  }
  // 字符串
  state gotoNextPos(state x, string expr) {
    if (x.first >= x.second) {
      x.first = nullptr;
      x.second = nullptr;
      return x;
    }
    auto cx = x.first;
    for (auto ce = expr.begin(); cx < x.second && ce < expr.end(); ++cx, ++ce) {
      if (*ce != '.' && *cx != *ce) {
        x.first = nullptr;
        x.second = nullptr;
        return x;
      }
    }
    x.first += expr.length();
    return x;
  }
};

int main() {
  pair<string, string> xs[10] = {
      {"aaaaaaaaaaaaaaaaaaab", "a*a*a*a*a*a*a*a*a*a*"},
      {"aaa", "ab*a*c*a"},
      {"aaa", "a*a"},
      {"mississippi", "mis*is*ip*."},
      {"aab", "c*a*b"},
      {"aa", "a*"},
      {"aa", ".*"}};
  Solution s;
  for (pair<string, string> p : xs) {
    cout << p.first << "," << p.second << "\t" << s.isMatch(p.first, p.second)
         << endl;
    // s.isMatch(p.first, p.second);
  }
  return 0;
}