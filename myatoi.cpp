#include <string>
#include <stdint.h>
#include <iostream>
using namespace std;

class Solution {
public:
    int myAtoi(string str) {
        size_t l = str.length();
        if (l == 0) {
            return 0;
        }
        int pow10, pow16, prod, total;
        int *pow;
        pow = &pow10;
restart:
        pow10 = 1;
        pow16 = 1;
        prod = 1;
        total = 0;
        int i = l-1;
        bool symEncountered = false;
        while (i >= 0) {
           char a = str[i];
           int v = 0;
           if (a >= '0' && a <= '9') {
              if (symEncountered) {
                 return 0;
              }
              v = (a - '0') * (*pow);
           } else if (isxdigit(a)) {
              if (symEncountered) {
                 return 0;
              }
              if (pow == &pow10) {
                 pow = &pow16;
                 goto restart;
              }
              v = (10 + tolower(a) - 'a') * (*pow);
           } else if (a != ' ') {
              if (symEncountered) {
                 return 0;
              }
              if (a == '+') {
                 prod = 1;
                 symEncountered = true;
              } else if (a == '-') {
                 prod = -1;
                 symEncountered = true;
              } else {
                 return 0;
              }
           } else {
              symEncountered = true;
           }
           total += v;
           pow10 *= 10;
           pow16 *= 16;
           if (total > INT32_MAX) {
               return -1;
           }
           i--;
        }
        return total * prod;
    }
};

int main(void)
{
   Solution s;
   cout << s.myAtoi("1") << endl;
   cout << s.myAtoi("   +1") << endl;
   cout << s.myAtoi("   -1") << endl;
   cout << s.myAtoi("+   -1") << endl;
   cout << s.myAtoi("    -12345") << endl;
   cout << s.myAtoi("    +abcde") << endl;
   cout << s.myAtoi("    +abcd9") << endl;
   return 0;
}
