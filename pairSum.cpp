#include <vector>
#include <stdexcept>
#include <map>
#include <iostream>
#include <functional>

using namespace std;

std::vector<std::pair<int, int>>
pairSumZero(const std::vector<int> &v)
{
   std::vector<std::pair<int, int>> v1;
   std::map<int, int> m;
   for (unsigned int i = 0; i < v.size(); i++) {
      try {
         m.at(v[i]);
         v1.push_back(std::make_pair(v[i], v[i] * -1));
      } catch (const std::out_of_range &e) {
         m[v[i] * -1] = 0;
      }
   }
   return v1;
}

std::vector<std::pair<int, int>>
pairSumValue(const std::vector<int> &v, int N)
{
   std::vector<std::pair<int, int>> v1;

   std::map<int, int> m;
   for (unsigned int i = 0; i < v.size(); i++) {
      try {
         m.at(v[i]);
         v1.push_back(std::make_pair(v[i], N-v[i]));
      } catch (const std::out_of_range &e) {
         m[N - v[i]] = 0;
      }
   }
   return v1;
}

int main()
{
   int a[] = {3, 7, 2, 5, 6, 4, 1};
   std::vector<int> v(a, a + sizeof(a)/sizeof(a[0]));
   int b[] = {-3, 7, -2, 2, 6, 3, -7};
   std::vector<int> vA(a, a + sizeof(a)/sizeof(a[0]));
   std::vector<int> vB(b, b + sizeof(b)/sizeof(b[0]));
   std::vector<std::pair<int, int>> v1 = pairSumValue(vA, 5);
   for (auto i: v1) {
      cout << i.first << " " << i.second <<endl;
   }
   std::vector<std::pair<int, int>> v2 = pairSumZero(vB);
   for (auto i: v2) {
      cout << i.first << " " << i.second <<endl;
   }
   return 0;
}
