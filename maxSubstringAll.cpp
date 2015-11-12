#include <string>
#include <limits.h>
#include <stdexcept>
#include <map>
#include <iostream>

using namespace std;


class Solution {
public:
   unsigned int findEarliest(const map<char, unsigned int> &m) {
      unsigned int r = INT_MAX;
      for (auto i: m) {
         if (i.second < r) {
            r = i.second;
         }
      }
      return r;
   }
   string getMaxSubstringAll(const string &S, const string &T) {
      string res;
      unsigned int l = S.length(), m = T.length();
      map<char, unsigned int> m1;
      for (unsigned int i = 0; i < m; i++) {
         m1[T[i]] = INT_MAX;
      }
      unsigned int count = 0, numMatch = 0;
      for (unsigned int i = 0; i < l; i++) {
         try {
            unsigned int &p = m1.at(S[i]);
            if (p == INT_MAX) {
               numMatch++;
            }
            p = i;
            if (numMatch == m) {
               unsigned int j;
               string iRes;
               j = findEarliest(m1);
               iRes = S.substr(j, i-j+1);
               if (res.length() == 0 || iRes.length() < res.length()) {
                  res = iRes;
               }
            }
         } catch (const std::out_of_range &e) {
         }
      }
      return res;
   }
};


int main()
{
   string S("adobecodebanc"), T("abc");
   Solution s;
   cout << s.getMaxSubstringAll(S, T) << endl;
   cout << s.getMaxSubstringAll(S, "acd") << endl;
   return 0;
}
