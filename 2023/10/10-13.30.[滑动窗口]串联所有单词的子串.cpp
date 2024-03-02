#include <iostream>
#include <string>
#include <utility>
#include <algorithm>
#include <vector>
#include "map"
#include "unordered_map"
#include "queue"
#include "stack"
using namespace std;

// 暴力解,超时
class SolutionV1 {
public:
  vector<int> findSubstring(string s, vector<string> &words) {
    word_len = words[0].length();
    word_cnt = words.size();
    string_len = word_len * word_cnt;
    for (int i = 0, j = -1; i < words.size(); ++i) {
      // j个不同的单词
      auto x = smap.find(words[i]);
      if (x == smap.end()) {
        smap.emplace(words[i], ++j);
        scnts.push_back(1);
      } else {
        scnts[x->second]++;
      }
    }
    vector<int> ret;
    // O(m/l*n*l)
    for (auto i = find_next(s, 0); i + string_len <= s.length();
         i = find_next(s, i + 1)) {
      vector<int> scnts_cp(scnts);
      // O(n*l)
      if (match(s, i, words, scnts_cp))
        ret.push_back(i);
    }
    return ret;
  }

private:
  unsigned int word_len, word_cnt, string_len;
  vector<int> scnts;     // poscnt
  map<string, int> smap; // string->pos

  string::size_type inline find_next(const string &s, string::size_type i) {
    string::size_type pos = s.length();
    for (auto x : smap) {
      pos = min(pos, s.find(x.first, i));
      if (pos == i)
        return pos;
    }
    return pos;
  }
  int inline max(vector<int> arr) {
    for (auto x : arr)
      if (x > 0)
        return x;
    return 0;
  }
  bool match(const string &s, string::size_type i, const vector<string> word,
             vector<int> scnts_cp) {
    for (auto j = i + string_len; i < j && i < s.length(); i += word_len) {
      auto sub = s.substr(i, word_len);
      auto x = smap.find(sub);
      if (x == smap.end() || --scnts_cp[x->second] < 0)
        return false;
    }

    return 0 == max(scnts_cp);
  }
};

// 80ms
class SolutionV2 {
public:
  vector<int> findSubstring(string s, vector<string> &words) {
    init(words);
    vector<int> ret;
    map<string, int> diff_; // string->(word cnt in words)
    diff_.emplace("_", 0);
    for (auto w : words) {
      ++diff_[w];
    }

    for (auto offset = 0; offset < word_len; ++offset) {
      if (offset + substr_len > s.length())
        break;
      // init diff: word ->(word cnt in words) -(word cnt in s)
      map<string, int> diff(diff_);
      string lstr, rstr;
      for (auto left = offset;
           left - offset < substr_len && left + word_len <= s.length();
           left += word_len) {
        rstr = s.substr(left, word_len);
        subtract_diff(diff, rstr);
      }
      if (all_zero(diff))
        ret.push_back(offset);
      // char const *str = s.data()+offset,*lstr = str;
      for (auto left = offset + word_len; left + substr_len <= s.length();
           left += word_len) {
        // 滑动
        rstr = s.substr(left + substr_len - word_len, word_len);
        subtract_diff(diff, rstr);
        lstr = s.substr(left - word_len, word_len);
        add_diff(diff, lstr);
        if (all_zero(diff))
          ret.push_back(left);
      }
    }
    return ret;
  }

private:
  vector<int> scnts;     // poscnt
  map<string, int> smap; // string->pos
  unsigned int word_len, word_cnt, substr_len;
  void inline subtract_diff(map<string, int> &diff, const string &sub) {
    auto x = diff.find(sub);
    if (x == diff.end())
      --diff.find("_")->second;
    else {
      x->second--;
    }
  }
  void inline add_diff(map<string, int> &diff, const string &sub) {
    auto x = diff.find(sub);
    if (x == diff.end())
      ++diff.find("_")->second;
    else {
      ++x->second;
    }
  }
  bool inline all_zero(const map<string, int> &arr) {
    for (auto x : arr)
      if (x.second != 0)
        return false;
    return true;
  }
  void inline init(const vector<string> &words) {
    word_len = words[0].length();
    word_cnt = words.size();
    substr_len = word_len * word_cnt;
  }
};

class Solution {
public:
  vector<int> findSubstring(string s, vector<string> &words) {
    // 单词长度，字符串长度，子串长度,窗口长度
    int wl = words[0].length(), sl = s.length(), subl = words.size() * wl,
        winsize = (words.size() - 1) * wl;
    vector<int> ret;
    // 记录words中每个单词的数量
    unordered_map<string, int> mwords;
    for (auto x : words)
      ++mwords[x];

    // 根据偏移量划分
    for (int offset = 0; offset < wl; ++offset) {
      // 记录当前窗口中每个单词的数量，和已匹配的单词数
      unordered_map<string, int> mwindow;
      // 扫描每个单词
      for (int left = offset, right = offset; right + wl <= sl; right += wl) {
        auto rstr = s.substr(right, wl);
        auto x = mwords.find(rstr);
        if (x == mwords.end()) {
          // 未知单词，该词语不存在于words中
          mwindow.clear();
          left = right + wl;
        } else {
          // 已知单词
          ++mwindow[rstr];
          // 滑动左端点，确保窗口中的指定单词的数量要小于等于目标串中的
          while (mwindow[rstr] > mwords[rstr]) {
            auto lstr = s.substr(left, wl);
            left += wl, --mwindow[lstr];
          }
          // 实际窗口长度等于目标长度
          if (right-left == winsize) {
            ret.push_back(left);
          }
        }
      }
    }
    return ret;
  }
};

int main() {
  Solution s;
  string str = "wordgoodgoodgoodbestword";
  vector<string> words = {"word", "good", "best", "good"};
  auto ret = s.findSubstring(str, words);
  for (auto x : ret) {
    cout << x << '\t';
  }
}