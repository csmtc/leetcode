// 给你一个整数 x ，如果 x 是一个回文整数，返回 true ；否则，返回 false 。
// 回文数是指正序（从左向右）和倒序（从右向左）读都是一样的整数。
#include <iostream>
using namespace std;

class Solution {
public:
  Solution(){}
    bool isPalindrome(int x) {
      if (x < 0)
        return false;
      else if (x == 0)
        return true;
      else {
        int stack[10],top=-1;
        while (x > 0) {
          stack[++top] = x % 10;
          x/=10;
        }

        for (int i = 0; i < top; ++i) {
          if(stack[i]!=stack[top--])return false;
        }
        return true;
      }
    }
};
int main() {
  int xs[10] = {121, -121, 10};
  Solution s;
  for (int x : xs) {
    cout<<x<<"\t"<<s.isPalindrome(x)<<endl;
  }
  return 0;
}