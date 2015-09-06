#include <vector>
#include <iostream>

using namespace std;

int main(void)
{
   int a[]= {1, 2, 8, 9};
   std::vector<int> v(a, a + sizeof(a)/sizeof(a[0]));
   std::vector<int>::iterator it = v.begin();
   while (it != v.end()) {
      cout << *it << endl;
      it++;
   }
}
