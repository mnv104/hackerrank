#include <vector>
#include <stdio.h>
#include <iostream>
#include <string>
#include <sstream>
#include <getopt.h>
#include <stdlib.h>
using namespace std;


bool isSorted(const std::vector<int> nums)
{
   size_t l = nums.size();
   bool sorted = true, init = false, lt = false;
   for (int i = 1; i < l; i++) {
      bool thisLt;
      thisLt = (nums[i-1] > nums[i]);
      if (!init) {
         init = true;
         lt = thisLt;
      } else if (lt ^ thisLt) {
         sorted = false;
         break;
      }
   }
   return sorted;
}


int main(int argc, char *argv[])
{
   std::vector<int> v;
   int c;
   while ((c = getopt(argc, argv, "v:")) != EOF) {
      switch (c) {
         case 'v':
            {
               std::stringstream ss(optarg);
               std::string token;
               while (std::getline(ss, token, ',')) {
                  std::string::size_type sz;
                  int a = std::stoi(token, &sz);
                  v.push_back(a);
               }
               break;
            }
         default:
            exit(1);
      }
   }
   if (v.size() == 0) {
      cout << "Usage: " << argv[0] << " -v {list of comma separated numbers}" << endl;
      exit(1);
   }
   cout << isSorted(v) << endl;
   return 0;
}
