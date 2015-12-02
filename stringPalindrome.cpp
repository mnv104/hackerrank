#include <string>
#include <iostream>
#include <vector>
#include <ctype.h>

using namespace std;

class Solution {
public:
    bool isPalindrome(string s) {
        size_t l = s.length();
        if (l == 0 || l == 1) {
            return true;
        }
        int lPos = 0;
        int rPos = l - 1;
        while (lPos < rPos) {
           if (!isalnum(s[lPos])) {
              lPos++;
              continue;
           }
           if (!isalnum(s[rPos])) {
              rPos--;
              continue;
           }
           if (tolower(s[lPos]) == tolower(s[rPos])) {
              lPos++;
              rPos--;
           } else {
              return false;
           }
        }
        return true;
    }
};


int main()
{
   std::string s("A man, a plan, a canal, Panama");
   Solution solve;
   cout << "String " << s << " is " << (solve.isPalindrome(s) == 1 ? "a " : "not a ") << "palindrome" << endl;
   return 0;
}
