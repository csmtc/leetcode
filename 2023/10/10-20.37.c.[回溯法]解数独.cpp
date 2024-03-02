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

#define CHAR_NUMS 10
#define BOARD_SIDE_LEN 9
class Solution {
public:
  Solution(){};
  void solveSudoku(vector<vector<char>> &board) {
    this->board = board;
    // 重置字符集合
    for (int i = 0; i < 9; ++i) {
      for (int j = 0; j < 9; ++j) {
        int c = board[i][j] - '0';
        if (c > 0) {
          row_used[i][c] = true;
          col_used[j][c] = true;
          chunk_used[i / 3][j / 3][c] = true;
        }
      }
    }
    _solveSudoku(0, 0);
  }

protected:
  vector<vector<char>> board;
  // 3个bool数组，存储已使用的元素
  bool row_used[9][CHAR_NUMS]{false};
  bool col_used[9][CHAR_NUMS]{false};
  bool chunk_used[3][3][CHAR_NUMS]{false};

  bool _solveSudoku(int i, int j) {
    // 处理下标换行
    if (j == BOARD_SIDE_LEN) {
      j = 0;
      if (++i == BOARD_SIDE_LEN)
        return true;
    }
    // 若当前位置非空：跳过该位置
    if (board[i][j] != '.')
      return _solveSudoku(i, j + 1);
    else {
      // 尝试向board[i][j]填入 '0'~'9'
      for (char idx = 1; idx <= 9; ++idx) {
        bool &a = row_used[i][idx], &b = col_used[j][idx],
             &c = chunk_used[i / 3][j / 3][idx];
        if (a || b || c) // 该字符已使用
          continue;
        board[i][j] = idx + '0'; // 填入字符
        a = true, b = true, c = true;
        if (_solveSudoku(i, j + 1)) // 填下一个位置
          return true;
        board[i][j] = '.'; // 回溯
        a = false, b = false, c = false;
      }
    }
    return false;
  }
};
inline void go() {
  vector<vector<char>> board = vector<vector<char>>(9, vector<char>(9)) = {
      {'5', '3', '.', '.', '7', '.', '.', '.', '.'},
      {'6', '.', '.', '1', '9', '5', '.', '.', '.'},
      {'.', '9', '8', '.', '.', '.', '.', '6', '.'},
      {'8', '.', '.', '.', '6', '.', '.', '.', '3'},
      {'4', '.', '.', '8', '.', '3', '.', '.', '1'},
      {'7', '.', '.', '.', '2', '.', '.', '.', '6'},
      {'.', '6', '.', '.', '.', '.', '2', '8', '.'},
      {'.', '.', '.', '4', '1', '9', '.', '.', '5'},
      {'.', '.', '.', '.', '8', '.', '.', '7', '9'}};
  Solution().solveSudoku(board);
  for (auto x : board) {
    for (auto y : x) {
      cout << y << ' ';
    }
    cout << endl;
  }
}
int main() {
  clock_t begin = clock();
  go();
  clock_t end = clock();
  //   cout << endl << 'exec cost ' << (end - begin) << ' us.';
}
