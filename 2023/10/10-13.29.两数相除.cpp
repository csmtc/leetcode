#include <algorithm>
#include <iostream>

#include "vector"
using namespace std;

#define MY_INT_MIN -2147483648
#define MY_INT_MAX 2147483647
int inline safe_add(int a, int b) {
  if (a > 0 && b > 0 && a > MY_INT_MAX - b) return MY_INT_MAX;
  if (a < 0 && b < 0 && a < MY_INT_MIN - b) return MY_INT_MIN;
  return a + b;
}
class Solution {
 public:
  int divide(int a, int b) {
    int ci, b_2ci = 0, c = 0, lastval = 0, offset = 0;
    // 处理溢出
    if (b == MY_INT_MIN) return a == MY_INT_MIN ? 1 : 0;
    if (a == MY_INT_MIN) {
      a += abs(b);
      offset = b > 0 ? -1 : 1;
    }
    bool positive = (a >= 0 && b > 0) || (a < 0 && b < 0);
    if (a < 0) a = -a;
    if (b < 0)
      b = -b;
    // 把a拆解为b*(若干2^ci)+余数的形式
    // 即a = bc+r = b*(c0*2^0+c1*2^1+ci*2^i+...+cn*2^n)+r
    // 初始商c=0，每轮循环在 a>2^ci的前提下找到最大的ci
    // c+=ci，a-=b*(2^ci)
    while (a > 0) {
      if (a < b) break;
      b_2ci = b, ci = 1;
      while (b_2ci << 1 > lastval && a > b_2ci << 1) {
        b_2ci = b_2ci << 1, ci = ci << 1;
        lastval = b_2ci;
      }

      c += ci, a -= b_2ci, lastval = 0;
    }
    c = positive ? c : -c;
    c = safe_add(offset, c);
    return c;
  }
};

int main() { cout << Solution().divide(-1010369383, -2147483648); }