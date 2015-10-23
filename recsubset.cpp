#include <string>
#include <sstream>
#include <iostream>
#include <set>

using namespace std;

void recSubset(const std::string &soFar, const std::string &rest, std::set<string> &s1)
{
   if (rest == "") {
      s1.insert(soFar);
   } else {
      stringstream ss;
      ss << rest[0];
      recSubset(soFar + ss.str(), rest.substr(1), s1);
      recSubset(soFar, rest.substr(1), s1);
   }
}

std::set<string> subset(const string &s)
{
   std::set<string> s1;
   recSubset("", s, s1);
   return s1;
}


int main(void)
{
   std::set<string> s;
   s = subset("abcd");
   for (auto i: s) {
      cout << i << endl;
   }
   return 0;
}
