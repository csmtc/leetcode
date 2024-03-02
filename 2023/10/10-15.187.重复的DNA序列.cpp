// DNA序列 由一系列核苷酸组成，缩写为 'A', 'C', 'G' 和 'T'.。

// 例如，"ACGAATTCCG" 是一个 DNA序列 。
// 在研究 DNA 时，识别 DNA 中的重复序列非常有用。

// 给定一个表示 DNA序列 的字符串 s ，返回所有在 DNA 分子中出现不止一次的 长度为
// 10 的序列(子字符串)。你可以按 任意顺序 返回答案。

#include "map"
#include "queue"
#include "set"
#include "stack"
#include "time.h"
#include "unordered_map"
#include "unordered_set"
#include <algorithm>
#include <iostream>
#include <string>
#include <utility>
#include <vector>
using namespace std;

class Solution {
public:
  vector<string> findRepeatedDnaSequences(string s) {
    vector<string> ret;
    auto end = s.length()-10;
    if (s.length() < 10)
      return ret;
    unordered_map<string, int> smap;
    for (auto offset = 0; offset < 10; ++offset) {
      for (int idx = offset; idx  <= end; idx += 10) {
        auto piece = s.substr(idx, 10);
        if (++smap[piece] == 2)
          ret.push_back(piece);
      }
    }
    return ret;
  }
};

void inline go() {
  string s = "AAAAACCCCCAAAAACCCCCCAAAAAGGGTTT";
  for (auto x : Solution().findRepeatedDnaSequences(s))
    cout << x << '\t';
}

int main() {
  clock_t begin = clock();
  go();
  clock_t end = clock();
  cout << endl << "exec cost " << (end - begin) << " us.";
}