#include <iostream>
#include <vector>
using namespace std;


int main(int argc, char *argv[])
{
   int a[] = {0,1,2,4,5,3,7,8};
   int N=8;
   std::vector<int> v(a, a+sizeof(a)/sizeof(a[0]));
   int val = 0;
   for (int i = 0; i < N; i++) {
      val = val ^ a[i];
   }
   int expectedVal;
   switch (N%4) {
      case 0:
         expectedVal = N;
         break;
      case 1:
         expectedVal = 1;
         break;
      case 2:
         expectedVal = N + 1;
         break;
      case 3:
         expectedVal = 0;
         break;
   }
   cout << "Missing number is: " << (expectedVal ^ val) << endl;
   return 0;
}
