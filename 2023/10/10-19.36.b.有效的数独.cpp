// 请你判断一个 9 x 9 的数独是否有效。只需要 根据以下规则
// ，验证已经填入的数字是否有效即可。

// 数字 1-9 在每一行只能出现一次。
// 数字 1-9 在每一列只能出现一次。
// 数字 1-9 在每一个以粗实线分隔的 3x3 宫内只能出现一次。（请参考示例图）

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
class Solution {
public:
  bool isValidSudoku(vector<vector<char>> &A) {
    int m = A.size(), n = m / 3;
    int row = 0, col = 0, i, j, sum;
    vector<bool> exist(10, false);

    for (row = 0; row < n; ++row) {
      for (col = 0; col < n; ++col) {
        for (i = 0; i < 10; ++i)
          exist[i] = false;
        for (i = 0; i < 3; ++i) {
          for (j = 0; j < 3; ++j) {
            auto c = A[row * 3 + i][col * 3 + j];
            if (c == '.')
              continue;
            auto idx = c - '0';
            if (exist[idx])
              return false;
            exist[idx] = true;
          }
        }
      }
    }
    for (i = 0; i < m; ++i) {
      for (int k = 0; k < 10; ++k)
        exist[k] = false;
      for (j = 0; j < m; ++j) {
        auto c = A[i][j];
        if (c == '.')
          continue;
        auto idx = c - '0';
        if (exist[idx])
          return false;
        exist[idx] = true;
      }
    }
    for (j = 0; j < m; ++j) {
      for (int k = 0; k < 10; ++k)
        exist[k] = false;
      for (i = 0; i < m; ++i) {
        auto c = A[i][j];
        if (c == '.')
          continue;
        auto idx = c - '0';
        if (exist[idx])
          return false;
        exist[idx] = true;
      }
    }
    return true;
  }
};
inline void go() {

  vector<vector<char>> V = vector<vector<char>>(9, vector<char>(9)) = {
      {'5', '3', '.', '.', '7', '.', '.', '.', '.'},
      {'6', '.', '.', '1', '9', '5', '.', '.', '.'},
      {'.', '9', '8', '.', '.', '.', '.', '6', '.'},
      {'8', '.', '.', '.', '6', '.', '.', '.', '3'},
      {'4', '.', '.', '8', '.', '3', '.', '.', '1'},
      {'7', '.', '.', '.', '2', '.', '.', '.', '6'},
      {'.', '6', '.', '.', '.', '.', '2', '8', '.'},
      {'.', '.', '.', '4', '1', '9', '.', '.', '5'},
      {'.', '.', '.', '.', '8', '.', '.', '7', '9'}};

  cout << Solution().isValidSudoku(V);
}
int main() {
  clock_t begin = clock();
  go();
  clock_t end = clock();
  cout << endl << " exec cost " << (end - begin) << " us.";
}