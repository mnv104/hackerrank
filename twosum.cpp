#include <vector>
#include <map>
#include <unistd.h>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
using namespace std;

class Solution {
private:
   vector<int> nums;
   int target;
public:
   vector<int> twoSum() {
      size_t l = nums.size();
       std::map<int, int> s;
       std::map<int, int>::iterator it;
       for (int i = 0; i < l; i++) {
           it = s.find(nums[i]);
           if (it != s.end()) {
               int l1[] = {it->second+1, i+1};
               return std::vector<int>(l1, l1 + sizeof(l1)/sizeof(l1[0]));
           } else {
               s.emplace(target-nums[i], i);

           }
       }
       cout << "No such pair!" << endl;
       throw std::invalid_argument("No such pair");
   }

   void
   readInput()
   {
      string line;
      if (getline(cin, line) == 0) {
         throw invalid_argument("Bad line");
      }
      std::size_t first = line.find_first_of("{"),
         last = line.find_first_of("}");
      if (first == string::npos || last == string::npos) {
         throw invalid_argument("Bad argument");
      }
      std::string line1 = line.substr(first + 1, last - first - 1);
      stringstream ss;
      ss << line1;
      string token;
      while (getline(ss, token, ',')) {
         nums.emplace_back(stoi(token));
      }
      std::size_t l = line.find_last_of("=");
      if (l == string::npos) {
         throw invalid_argument("Bad argument");
      }
      line1 = line.substr(l + 1);
      target = stoi(line1);
   }
};


int main(int argc, char *argv[])
{
    Solution s;
    s.readInput();
    vector<int> answer = s.twoSum();
    cout << "index1="  << answer[0] << ", index2=" << answer[1] << endl;
    return 0;
}
