// 给定一个仅包含数字 2-9 的字符串，返回所有它能表示的字母组合。
#include "iostream"
#include "string"
#include "unordered_map"
#include "vector"
using namespace std;

const string dmap[8] = {"abc", "def",  "ghi", "jkl",
                        "mno", "pqrs", "tuv", "wxyz"};
const int lens[8] = {3, 3, 3, 3, 3, 4, 3, 4};

unsigned long measure1 = 0, measure2 = 0;
class Solution {
public:
  vector<string> letterCombinations(string digits) {
    vector<string> combinations;
    if (digits.empty()) {
      return combinations;
    }
    unordered_map<char, string> phoneMap{
        {'2', "abc"}, {'3', "def"},  {'4', "ghi"}, {'5', "jkl"},
        {'6', "mno"}, {'7', "pqrs"}, {'8', "tuv"}, {'9', "wxyz"}};
    string combination;
    backtrack(combinations, phoneMap, digits, 0, combination);
    return combinations;
  }

  void backtrack(vector<string> &combinations,
                 const unordered_map<char, string> &phoneMap,
                 const string &digits, int index, string &combination) {
    if (index == digits.length()) {
      combinations.push_back(combination);
    } else {
      char digit = digits[index];
      const string &letters = phoneMap.at(digit);
      for (const char &letter : letters) {
        combination.push_back(letter);
        backtrack(combinations, phoneMap, digits, index + 1, combination);
        combination.pop_back();
      }
    }
  }
};

/**直接实现*/
class Solution1 {
public:
  vector<string> letterCombinations(string digits) {
    vector<string> ret;
    if (digits.empty())
      return ret;
    int idx, before, after = 1, cnt, k;
    for (auto c : digits) {
      idx = c - '2';
      after *= lens[idx];
    }
    cnt = after;
    for (int i = 0; i < cnt; ++i)
      ret.push_back("");
    for (auto c : digits) {
      idx = c - '2';
      before = cnt / after;
      after /= lens[idx];
      k = -1;

      for (int i = 0; i < before; ++i)
        for (auto dc : dmap[idx]) {
          for (int j = 0; j < after; ++j) {
            ret[++k] += dc;
            ++measure2;
          }
          
        }
    }
    return ret;
  }
};
int main() {
  Solution s;
  Solution1 s1;
  string str = "2349";
  auto ret = s.letterCombinations(str);
  s1.letterCombinations(str);
  cout<<measure1<<'\t'<<measure2;
//   cout << ret.size() << endl;
//   for (auto x : ret) {
//     cout << x << '\t';
//   }
}