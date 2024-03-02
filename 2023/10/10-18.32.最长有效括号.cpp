#include <algorithm>
#include <deque> //  双端队列
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <time.h>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>
using namespace std;

const char L = '(', R = ')';
class SolutionV1 {
public:
  int longestValidParentheses(string s) {
    if (s.length() == 0)
      return 0;

    int n = s.length();
    vector<bool> valid(n);
    stack<int> S;
    // 初始化
    for (int i = 0; i < n; ++i) {
      if (s[i] == L)
        S.push(i);
      else { // 右括号
        if (!S.empty()) {
          int j = S.top();
          S.pop();
          valid[i] = true, valid[j] = true;
        }
      }
    }

    // 统计连续的Valid个数
    int max_val = 0, val;
    for (auto x : valid) {
      if (x)
        ++val, max_val = max(val, max_val);
      else
        val = 0;
    }
    return max_val;
  }
};

// 优化掉valid数组
class Solution {
public:
  int longestValidParentheses(string s) {
    if (s.length() == 0)
      return 0;

    int n = s.length(), val = 0;
    stack<int> S;
    // 初始化
    S.push(-1);
    for (int j = 0; j < n; ++j) {
      if (s[j] == '(')
        S.push(j);
      else { // 右括号
        // 相应的左括号
        S.pop();
        if (!S.empty()) {
          val = max(val, j - S.top());
        } else
          S.push(j);
      }
    }
    return val;
  }
};
inline void go() {
  string str = "()(()";
  cout << Solution().longestValidParentheses(str);
}
int main() {
  clock_t begin = clock();
  go();
  clock_t end = clock();
  cout << endl << "exec cost " << (end - begin) << " us.";
}