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
  void nextPermutation(vector<int> &A) {
    /*
    for i=n-2...0, for j=n-1...i+1 find j>i st A[j]>A[i]
    sort(A[i+1],A[n])
    */
    int left, right, n = A.size();
    for (left = n - 2; left >= 0; --left) {
      for (right = n - 1; right > left; --right) {
        if (A[left] < A[right]) {
          swap(A[left], A[right]);
          sort(A.begin() + left + 1, A.end());
          return;
        }
      }
    }
    sort(A.begin(), A.end());
  }
};

inline void go() {
  vector<int> arr{1, 2, 5, 4, 3};
  Solution().nextPermutation(arr);
  for (auto x : arr)
    cout << x << '\t';
}
int main() {
  clock_t begin = clock();
  go();
  clock_t end = clock();
  cout << endl << "exec cost " << (end - begin) << " us.";
}