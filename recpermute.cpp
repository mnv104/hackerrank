#include <string>
#include <iostream>
#include <vector>
using namespace std;


void recPermute(const string &soFar, const string & rest, std::vector<string> &v)
{
   if (rest == "") {
      v.push_back(soFar);
   } else {
      for (unsigned int i = 0; i < rest.length(); i++) {
         string next = soFar + rest[i];
         string remaining = rest.substr(0, i) + rest.substr(i+1);
         cout << next << " " << remaining << endl;
         recPermute(next, remaining, v);
      }
   }
}

std::vector<string> permute(const string &s)
{
   std::vector<string> v;
   recPermute("", s, v);
   return v;
}

int main(void)
{
   std::vector<string> v;
   v = permute("abcd");
   for (auto i : v) {
      cout << i << endl;
   }
   return 0;
}
