// 给定两个整数 n 和 k，返回范围 [1, n] 中所有可能的 k 个数的组合。
#include "iostream"
#include "string"
#include "vector"
#include <sstream>
using namespace std;
class Solution {
public:
  vector<vector<int>> combine(int n, int k) {
    vector<vector<int>> ret;
    vector<int> combine;
    build(1, n, k, ret, combine);
    return ret;
  }
  void build(int begin, int n, int k, vector<vector<int>> &ret,
             vector<int> &combine) {
    if (k == 0) {
      ret.push_back(combine);
    } else {
      for (auto i = begin; i <= n; ++i) {
        combine.push_back(i);
        build(i + 1, n, k - 1, ret, combine);
        combine.pop_back();
      }
    }
  }
};

int main() {
  Solution s;
  int n = 4, k = 2;
  auto ret = s.combine(n, k);
  for (auto x : ret) {
    for (auto y : x) {
      cout << y << '\t';
    }
    cout << endl;
  }
}