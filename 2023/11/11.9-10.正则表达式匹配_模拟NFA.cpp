#include <iostream>
#include <string>
#include <utility>
#include <vector>
using namespace std;
// 哨兵
#define PATTERN_EOF 0
#define PATTERN_LETTER 1
#define PATTERN_DOT 2
#define PATTERN_STAR 3
using Pattern = struct Pattern {
  int typ;
  char val;
};

Pattern ps[21];

void compile(const string &str) {
  int pstr_len = 0;
  for (auto c : str) {
    if (c == '.')
      ps[pstr_len].typ = PATTERN_DOT;
    else if (c == '*')
      ps[pstr_len].typ = PATTERN_STAR;
    else
      ps[pstr_len].typ = PATTERN_LETTER;
    ps[pstr_len++].val = c;
  }
  ps[pstr_len].typ = PATTERN_EOF;
}

bool inline match_one(const Pattern &p, const char c) {
  switch (p.typ) {
  case PATTERN_LETTER:
    return c == p.val;
  case PATTERN_DOT:
    return true;
  default:
    return false;
  };
}

// ps:后续匹配模式队列，p：要匹配的字符，str：匹配的目标字符串
// bool match_star(Pattern ps[], Pattern p, const char *str);
bool match_pattern(Pattern *ps, const char *str);

bool match_star(Pattern *ps, Pattern p, const char *str) {
  const char *begin_pos = str;
  while (*str != '\0' && match_one(p, *str)) {
    ++str;
  }
  while (str >= begin_pos) {
    if (match_pattern(ps, str--))
      return true;
  }
  return false;
}
bool match_pattern(Pattern *ps, const char *str) {
  bool isMatchOne;
  do {
    if (ps[0].typ == PATTERN_EOF) {
      return *str == '\0';
    } else if (ps[1].typ == PATTERN_STAR) {
      return match_star(ps + 2, *ps, str);
    }
  } while ((isMatchOne = *str != '\0') &&
           (isMatchOne = match_one(*ps++, *str++)));
  return isMatchOne;
}
class Solution {
public:
  bool isMatch(string s, string p) {
    compile(p);
    return match_pattern(ps, s.c_str());
  }
};

int main() {
  vector<pair<string, string>> testset{
      {"a", "aa"},  {"ab", ".*c"},    {"aaa", "a*a"},
      {"a", "ab*"}, {"aab", "c*a*b"}, {"mississippi", "mis*is*p*."}};
  for (auto &p : testset)
    cout << p.first << '\t' << p.second << ":\t"
         << Solution().isMatch(p.first, p.second) << endl;
}