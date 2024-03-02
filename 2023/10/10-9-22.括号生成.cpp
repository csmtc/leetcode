// 数字 n 代表生成括号的对数，请你设计一个函数，用于能够生成所有可能的并且
// 有效的 括号组合。
#include "iostream"
#include "string"
#include "vector"
#include <sstream>
using namespace std;

class Solution {
public:
  vector<string> generateParenthesis(int n) {
    vector<vector<string>> buf(9);
    buf[0].push_back("");
    this->generateParenthesis_(buf, n);
    return buf[n];
  }
  void generateParenthesis_(vector<vector<string>> &buf, int n) {
    if (n == 0 || buf[n].size() > 0)
      return;
    this->generateParenthesis_(buf, n - 1);
    int p, q;
    for (p = 0; p < n; ++p) {
      q = n - 1 - p;
      // buf[p],buf[q] 笛卡尔积
      //   cout << p << '\t' << q << endl;
      for (auto a : buf[p]) {
        for (auto b : buf[q]) {
          buf[n].push_back("(" + a + ")" + b);
        }
      }
    }

    // cout << n << ":" << buf[n].size() << endl;
  }
};

int main() {
  Solution s;
  auto ret = s.generateParenthesis(5);
  cout << ret.size() << endl;
  for (auto x : ret) {
    cout << x << endl;
  }
}