#include <string>
#include <stdexcept>
#include <algorithm>
#include <stdint.h>
#include <sstream>
#include <iostream>
#include <vector>

using namespace std;
static bool
isPalindrome(string &s, size_t l)
{
   if (l == 0) {
      throw std::invalid_argument("Bad string");
   } else if (l == 1) {
      return true;
   } else {
      int i, j;
      std::vector<char> st;
      for (i = 0; i < l/2; i++) {
         //cout << "Pushing " << s[i] << endl;
         st.push_back(s[i]);
      }
      if ((l % 2) != 0) {
         i++;
      }
      for (j = i; j < l; j++) {
         char last = *st.erase(st.end()-1);
         //cout << "Popped " << last << " and comparing with " << s[j] << endl;
         if (last != s[j]) {
            return false;
         }
      }
      return true;
   }
}

static string
getPartialString(const string &s, int indexToRemove)
{
   size_t l = s.length();
   string t;
   if (indexToRemove == 0) {
      t = s.substr(1);
   } else if (indexToRemove == l-1) {
      t = s.substr(0, l-1);
   } else {
      t = s.substr(0, indexToRemove);
      t += s.substr(indexToRemove + 1);
   }
   return t;
}

void readInput()
{
   string line;
   stringstream ss;
   if (getline(cin, line) == 0) {
      throw std::invalid_argument("Badline");
   }
   ss << line;
   uint32_t numTestCases;
   ss >> numTestCases;
   vector<string> allStrings;
   for (int i = 0; i < numTestCases; i++) {
      if (getline(cin, line) == 0) {
         throw std::invalid_argument("Badline");
      }
      allStrings.push_back(line);
   }
   vector<string>::const_iterator it = allStrings.begin();
   while (it != allStrings.end()) {
      string s = *it;
      size_t len = s.length();
      if (isPalindrome(s, len)) {
         cout << -1 << endl;
      } else {
         for (int i = 0; i < len; i++) {
            string p = getPartialString(s, i);
            if (isPalindrome(p, len-1)) {
               cout << i << endl;
               break;
            }
         }
      }
      it++;
   }
}


int main(int argc, char *argv[])
{
   readInput();
   return 0;
}
