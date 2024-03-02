
// 给你一个字符串 s 和一个字符规律 p，请你来实现一个支持 '.' 和 '*'
// 的正则表达式匹配。

// '.' 匹配任意单个字符
// '*' 匹配零个或多个前面的那一个元素
// 所谓匹配，是要涵盖 整个 字符串 s的，而不是部分字符串。
#include <algorithm>
#include <iostream>
using namespace std;

typedef struct _struct_pattern {
  string str;
  bool repeat;
} pattern;
pattern ps[20];

bool isPlainMatch(string s, string reg) {
  if (s.length() == 0)
    return false;
  else if (s.length() > reg.length())
    return false;
  int i, len = reg.length();
  for (i = 0; i < len; ++i) {
    if (reg[i] != s[i] && reg[i] != '.') {  // 不匹配
      return false;
    }
  }
  return true;
}

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

    i = 0;
    string subs;
    bool ismatch;
    for (auto p = ps; p <= &ps[ptop]; ++p) {
      // cout<<p->str<<'\t'<<p->repeat<<endl;
      if (p->repeat) {
        ismatch = true;
        while (ismatch) {
          subs = s.substr(i, p->str.length());
          ismatch = isPlainMatch(subs, p->str);
          if (ismatch) i += subs.length();
        }
      } else {
        subs = s.substr(i, p->str.length());
        ismatch = isPlainMatch(subs, p->str);
        if (!ismatch) return false;
        i += subs.length();
      }
    }
    return i == s.length();
  }
};

int main() {
  pair<string, string> xs[10] = {{"aaa", "a*a"},
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