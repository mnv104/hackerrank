#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <stdexcept>
#include <sstream>
#include <string>

using namespace std;

long
value(const std::string &s, int base)
{
   size_t l = s.length();
   long total = 0;
   int pow = 1;
   for (int i = 0; i < l; i++) {
      char w = s[l - i - 1];
      int v;
      if (w >= '0' && w <= '9') {
         v = w - '0';
      } else if (isxdigit(w)) {
         v = 10 + tolower(w) - 'a';
      } else {
         throw std::invalid_argument("Bad number");
      }
      if (v >= base) {
         throw std::invalid_argument("Bad digit");
      }
      if (v != 0) {
         total += v * pow;
      }
      pow *= base;
   }
   return total;
}


int main(int argc, char *argv[])
{
   long v1, v2;
   if (argc > 1) {
      try {
         std::string s(argv[1]);
         cout << "Binary String s: " << s << endl;
         v1 = value(s, 2);
         cout << "Value is " << v1 << endl;
      } catch(...) {
         cout << "Invalid binary string:" << argv[1] << endl;
         exit(1);
      }
   }
   if (argc > 2) {
      try {
         std::string s(argv[2]);
         if (s.compare(0, 2, "0x") == 0) {
            s = s.substr(2);
         }
         cout << "Hex String s: " << s << endl;
         v2 = value(s, 16);
         cout << "Value is " << v2 << endl;
      } catch(...) {
         cout << "Invalid hex string:" << argv[2] << endl;
         exit(1);
      }
   }
   return 0;
}
