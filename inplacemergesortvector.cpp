#include <vector>
#include <iostream>

using namespace std;

class Solution {
public:
    void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
       int i, j;
       int pos = m + n - 1;
       for (i = m - 1, j = n - 1; i >= 0 && j >= 0;) {
          if (nums1[i] < nums2[j]) {
             nums1[pos] = nums2[j];
             j--;
          } else {
             nums1[pos] = nums1[i];
             i--;
          }
          pos--;
       }
       while (i >= 0 && pos >= 0) {
          nums1[pos--] = nums1[i--];
       }
       while (j >= 0 && pos >= 0) {
          nums1[pos--] = nums2[j--];
       }

    }
};

void func1()
{
#define M 3
#define N 3
   int a1[M+N] = {4,5,6,0,0,0};
   int b1[N] = {1,2,3};
   vector<int> v1(a1, a1+sizeof(a1)/sizeof(a1[0]));
   vector<int> v2(b1, b1+sizeof(b1)/sizeof(b1[0]));
   Solution s;
   s.merge(v1, M, v2, N);
   for (auto i: v1) {
      cout << i << " ";
   }
   cout << endl;
#undef M
#undef N
}


void func2()
{
#define M 1
#define N 3
   int a1[M+N] = {4,0,0,0};
   int b1[N] = {1,2,3};
   vector<int> v1(a1, a1+sizeof(a1)/sizeof(a1[0]));
   vector<int> v2(b1, b1+sizeof(b1)/sizeof(b1[0]));
   Solution s;
   s.merge(v1, M, v2, N);
   for (auto i: v1) {
      cout << i << " ";
   }
   cout << endl;
#undef M
#undef N
}


void func3()
{
#define M 2
#define N 4
   int a1[M+N] = {5,6,0,0,0,0};
   int b1[N] = {1,2,3,4};
   vector<int> v1(a1, a1+sizeof(a1)/sizeof(a1[0]));
   vector<int> v2(b1, b1+sizeof(b1)/sizeof(b1[0]));
   Solution s;
   s.merge(v1, M, v2, N);
   for (auto i: v1) {
      cout << i << " ";
   }
   cout << endl;
#undef M
#undef N
}

void func4()
{
#define M 0
#define N 5
   int a1[M+N] = {0, 0, 0, 0, 0};
   int b1[N] = {1,2,3,4,5};
   vector<int> v1(a1, a1+sizeof(a1)/sizeof(a1[0]));
   vector<int> v2(b1, b1+sizeof(b1)/sizeof(b1[0]));
   Solution s;
   s.merge(v1, M, v2, N);
   for (auto i: v1) {
      cout << i << " ";
   }
   cout << endl;
#undef M
#undef N
}

void func5()
{
#define M 5
#define N 1
   int a1[M+N] = {1,2,4,5,6,0};
   int b1[N] = {3};
   vector<int> v1(a1, a1+sizeof(a1)/sizeof(a1[0]));
   vector<int> v2(b1, b1+sizeof(b1)/sizeof(b1[0]));
   Solution s;
   s.merge(v1, M, v2, N);
   for (auto i: v1) {
      cout << i << " ";
   }
   cout << endl;
#undef M
#undef N
}




int main()
{
   func1();
   func2();
   func3();
   func4();
   func5();
   return 0;
}
