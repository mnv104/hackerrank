#include <string>
#include <map>
#include <vector>
#include <iostream>
#include <sstream>
#include <stdint.h>

using namespace std;

typedef std::pair<uint32_t, uint32_t> range;

struct extentRange {
   std::pair<std::pair<uint32_t, uint32_t>,
      std::pair<uint32_t, uint32_t>> r;
   extentRange(uint32_t one, uint32_t two, uint32_t three, uint32_t four) {
      r = std::make_pair(std::make_pair(one, two),
                         std::make_pair(three, four));
   }
};

struct extentVal {
   std::vector<extentRange> v;
   void addRange(const extentRange &e) {
      v.push_back(e);
   }
};

struct rangeMap {
   std::map<std::string, extentVal> m;
};

void
parse(const std::string &s, rangeMap &rm)
{
   std::stringstream ss;
   ss << s;
   std::string vmdkPathName;
   while (ss) {
      std::string line;
      getline(ss, line);
      if (line.size() == 0) {
         break;
      }
      std::stringstream ss1;
      ss1 << line;
      std::string firstWord;
      ss1 >> firstWord;
      if (firstWord.compare("vmdk") == 0) {
         ss1 >> vmdkPathName;
         rm.m[vmdkPathName] = extentVal();
      } else {
         ss1.clear();
         ss1.str("");
         ss1 << line;
         extentVal &ev = rm.m.at(vmdkPathName);
         uint32_t one, two, three, four;
         ss1 >> one >> two >> three >> four;
         ev.addRange(extentRange(one, two, three, four));
      }
   }
}

int main()
{
   std::string s("vmdk /a/b/c.vmdk\n0 10 100 110\n20 30 200 210\n100 110 300 310\nvmdk /a/b/c/d.vmdk\n0 10 40 50\n10 15 50 55\n");
   rangeMap m;
   parse(s, m);
   for (auto ev: m.m) {
      cout << ev.first << endl;
      for (auto er: ev.second.v) {
         cout << er.r.first.first << " " << er.r.first.second << " "
            << er.r.second.first << " " << er.r.second.second << endl;
      }
   }
   return 0;
}
