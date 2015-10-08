#include <string>
#include <iostream>

using namespace std;


bool isPalindrome(const std::string &str)
{
   size_t l = str.length();
   if (l == 0 || l == 1) {
      return true;
   }
   if (str[0] != str[l-1]) {
      return false;
   }
   return isPalindrome(str.substr(1, l-2));
}



int main(int argc, char *argv[])
{
   if (argc > 1) {
      cout << isPalindrome(argv[1]) << endl;
   }
   return 0;
}
