// 给你一个字符串 s 、一个字符串 t 。返回 s 中涵盖 t 所有字符的最小子串。
// 如果 s 中不存在涵盖 t 所有字符的子串，则返回空字符串 "" 。
// 对于 t 中重复字符，我们寻找的子字符串中该字符数量必须不少于 t 中该字符数量。
// 如果 s 中存在这样的子串，我们保证它是唯一的答案。
#include "map"
#include "queue"
#include "stack"
#include "unordered_map"
#include <algorithm>
#include <iostream>
#include <string>
#include <utility>
#include <vector>
using namespace std;

// 滑动窗口
class SolutionV1 {
public:
  // 目标子串字符串中的字符数量，和当前窗口中的字符数量
  unordered_map<char, int> tmap, wmap;
  string minWindow(string s, string t) {
    int sl = s.length(), tl = t.length(), wsize = tl - 1;
    for (auto c : t)
      ++tmap[c];
    const char *sd = s.data();
    int left = 0, right = 0, min_left = 0, min_len = sl;

    bool iscover = false;
    for (; right < sl; ++right) {
      auto c = sd[right];
      if (tmap.find(c) == tmap.end()) {
        continue; // 未知字符
      } else {
        ++wmap[c];
      }
      // 检查是否为覆盖子串
      iscover = iscover || cover(wmap, tmap);
      if (iscover) {
        // Once all the characters are covered, move the left pointer and ensure
        // that all the characters are still covered to minimize the subarray
        // size.
        while (moveR(sd, left)) {
        }
        // record min subarray size
        if (right - left + 1 < min_len) {
          min_len = right - left + 1;
          min_left = left;
        }
      }
    }
    if (!iscover)
      return "";
    else
      return s.substr(min_left, min_len);
  }
  bool inline cover(unordered_map<char, int> &a, unordered_map<char, int> &b) {
    if (a.size() < b.size())
      return false;
    for (auto x : a) {
      auto y = b.find(x.first);
      if (y == b.end() || x.second < y->second)
        return false;
    }
    return true;
  }
  // 返回是否移动了pos
  bool inline moveR(const char *&sd, int &pos) {
    char c = sd[pos];
    // 非期望字符
    if (tmap.find(c) == tmap.end()) {
      ++pos;
      return true;
    } else if (wmap[c] > tmap[c]) {
      // 期望字符，且已有数量超出期望
      --wmap[c], ++pos;
      return true;
    }
    return false;
  };
};

// 滑动窗口，优化覆盖检测
class Solution {
public:
  unordered_map<char, int> map_t, map_s;
  string minWindow(string s, string t) {
    const char *sd = s.data();
    int target_cnt = t.size(), need_cnt = t.size(), s_length = s.length();
    int min_left = 0, min_len = INT32_MAX;
    for (auto c : t)
      ++map_t[c];
    for (int left = 0, right = 0, len = INT32_MAX; right < s_length;) {
      // 滑动窗口右边界，直到窗口包含了字符串T的所有元素
      while (right < s_length && need_cnt > 0) {
        auto p = map_t.find(sd[right]);
        // 是目标字符(p在map_t中)，且窗口里的该类型字符数目小于期望，视为需要的字符
        if (p != map_t.end() && (++map_s[p->first] <= p->second))
          if (--need_cnt == 0)
            break;
        ++right;
      }
      // 滑动窗口左边界，使之缩小，直到碰到一个必须包含的元素A
      while (need_cnt == 0) {
        auto c = sd[left];
        if (map_t.find(c) == map_t.end()) // 非目标字符，无影响
          ++left;
        else if (map_s[c] > map_t[c]) //目标字符，且数目大于期望
          --map_s[c], ++left;
        else { //目标字符，且数目<=期望（即必须包含的字符）
               // 更新最小子串
          if ((len = right - left + 1) < min_len)
            min_left = left, min_len = len;
          // 窗口右移一位，开始寻找下一个满足条件的滑动窗口
          ++left, ++right, ++need_cnt, --map_s[c];
        }
      }
    }
    return min_len == INT32_MAX ? "" : s.substr(min_left, min_len);
  }
};

int main() {
  Solution s;
  string str1 = "AB";
  string str2 = "A";

  auto ret = s.minWindow(str1, str2);
  cout << ret;
}