#include <string>
#include <vector>
#include <sstream>
#include <iostream>
#include <set>
#include <iostream>

using namespace std;
class Solution {
public:
   int lengthOfLongestSubstring(const std::string &str) {
      std::set<char> s;
      std::string sub, maxSub;
      size_t l = str.length();
      int maxVal = 0;
      int pos = 0;
      while (pos < l) {
         std::set<char>::iterator it = s.find(str[pos]);
         stringstream ss;
         if (it != s.end()) {
            if (maxVal < s.size()) {
               maxVal = s.size();
               maxSub = sub;
            }
            s.erase(sub[0]);
            sub = sub.substr(1);
         } else {
            ss << str[pos];
            sub.append(ss.str());
            s.insert(str[pos]);
            pos++;
         }
      }
      if (maxVal < static_cast<int>(s.size())) {
         maxSub = sub;
      }
      cout << maxSub << endl;
      return std::max(maxVal, static_cast<int>(s.size()));
   }
};

int main(void)
{
   Solution s;
   cout << s.lengthOfLongestSubstring("dvdf") << endl;
   cout << s.lengthOfLongestSubstring("dvdfavbc") << endl;
   cout << s.lengthOfLongestSubstring("jbpnbwwd") << endl;
   return 0;
}
