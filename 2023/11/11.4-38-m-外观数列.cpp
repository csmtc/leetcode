#include <algorithm>
#include <ctime>
#include <deque> //  双端队列
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>
using namespace std;

class Solution {
public:
  string countAndSay(int n) {
    string s = "1";
    stringstream ss(s);
    for (int i = 1; i < n; ++i) {
      _cas(ss, s);
      s = move(ss.str());
    }
    return ss.str();
  }

protected:
  void _cas(stringstream &ss, string &s) {
    ss.str("");
    char last_char = s[0];
    int cnt = 0;
    for (auto c : s) {
      if (last_char == c)
        ++cnt;
      else {
        ss << cnt << last_char;
        last_char = c, cnt = 1;
      }
    }
    if (cnt >= 1)
      ss << cnt << last_char;
  }
};
inline void go() { cout << Solution().countAndSay(4); }
int main() {
  clock_t begin = clock();
  go();
  clock_t end = clock();
  cout << endl << "exec cost " << (end - begin) << " us.";
}