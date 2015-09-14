#include <string>
#include <vector>
#include <sstream>
#include <iostream>
#include <set>
#include <iostream>

using namespace std;
class Solution {
public:
   std::string lengthOfAtmost2Substr(const std::string &str) {
      std::set<char> s;
      std::string sub, maxSub;
      size_t l = str.length();
      size_t maxVal = 0;
      size_t pos = 0;
      while (pos < l) {
         std::set<char>::iterator it = s.find(str[pos]);
         stringstream ss;
         if (it == s.end()) { /* Not found */
            if (s.size() < 2) {
               ss << str[pos];
               sub.append(ss.str());
               s.insert(str[pos]);
               pos++;
            } else {
               if (maxVal < sub.length()) {
                  maxVal = sub.length();
                  maxSub = sub;
               }
               sub = sub.substr(sub.length() - 1);
               s.clear();
               s.insert(sub[0]);
            }
         } else {
            ss << str[pos];
            sub.append(ss.str());
            s.insert(str[pos]);
            pos++;
         }
      }
      if (maxVal < s.size()) {
         maxVal = s.size();
         maxSub = sub;
      }
      return maxSub;
   }
};

int main(void)
{
   Solution s;
   cout << s.lengthOfAtmost2Substr("dvdf") << endl;
   cout << s.lengthOfAtmost2Substr("ababedef") << endl;
   cout << s.lengthOfAtmost2Substr("abadededf") << endl;
   return 0;
}
