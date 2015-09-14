#include <string>
#include <vector>
#include <sstream>
#include <iostream>
#include <set>
#include <iostream>

using namespace std;
class Solution {
public:
   std::set<std::string> allPalindromes;
   std::string maxPalindrome;
   int lengthOfLongestPalindrome(const std::string &str) {
      allPalindromes.clear();
      maxPalindrome.clear();
      size_t l = str.length();
      if (l == 0) {
         return 0;
      }
      bool table[l][l];
      for (unsigned int i = 0; i < l; i++) {
         table[i][i] = true;
         //cout << "Inserted " << str.substr(i, 1) << endl;
         allPalindromes.insert(str.substr(i, 1));
      }
      for (unsigned int i = 0; i < l-1; i++) {
         if (str[i] == str[i+1]) {
            table[i][i+1] = true;
            //cout << "Inserted " << str.substr(i, 2) << endl;
            allPalindromes.insert(str.substr(i, 2));
         }
      }
      size_t longestBegin = 0, maxLen = 0;

      for (unsigned int j = 3; j <= l; j++) {
         for (unsigned int i = 0; i < l - j + 1; i++) {
            unsigned int pos = i + j -1;
            if (str[pos] == str[i] &&
                table[i+1][pos - 1]) {
               table[i][pos] = true;
               longestBegin = i;
               maxLen = j;
               //cout << "Inserted " << str.substr(i, maxLen) << endl;
               allPalindromes.insert(str.substr(i, maxLen));
               maxPalindrome = str.substr(i, maxLen);
            }
         }
      }
      return maxLen;
   }
};

void display(const std::set<std::string> &s)
{
   for (auto st: s) {
      cout << st << ", ";
   }
   cout << endl;
}

int main(void)
{
   Solution s;
   cout << s.lengthOfLongestPalindrome("dvdfdvd") << endl;
   cout << "Max palindrome: " << s.maxPalindrome << endl;
   display(s.allPalindromes);
   cout << s.lengthOfLongestPalindrome("abba") << endl;
   cout << "Max palindrome: " << s.maxPalindrome << endl;
   display(s.allPalindromes);
   cout << s.lengthOfLongestPalindrome("jbpnbwwd") << endl;
   cout << "Max palindrome: " << s.maxPalindrome << endl;
   display(s.allPalindromes);
   cout << s.lengthOfLongestPalindrome("j") << endl;
   cout << "Max palindrome: " << s.maxPalindrome << endl;
   display(s.allPalindromes);
   cout << s.lengthOfLongestPalindrome("") << endl;
   cout << "Max palindrome: " << s.maxPalindrome << endl;
   display(s.allPalindromes);
   return 0;
}
