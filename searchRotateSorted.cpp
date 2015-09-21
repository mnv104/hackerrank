#include <vector>
#include <assert.h>
#include <iostream>
#include <sstream>
#include <string>
#include <getopt.h>

using namespace std;

int findMin(const std::vector<int>& v, int begin, int end)
{
   int middle = (end + begin) / 2;
   if (begin + 1 == end) {
      return std::min(v[begin], v[end]);
   } else if (begin == end) {
      return v[begin];
   }
   if (v[middle] > v[begin] && v[middle] > v[end]) {
      return findMin(v, middle, end);
   } else if (v[middle] < v[begin] && v[middle] < v[end]) {
      return findMin(v, begin, middle);
   } else {
      if (v[middle] > v[begin]) {
         return findMin(v, begin, middle);
      } else {
         return findMin(v, middle, end);
      }
   }
}


bool search(const std::vector<int> &v, int number, int begin, int end)
{
   int middle = (end + begin) / 2;
   if (begin + 1 == end) {
      return v[begin] == number || v[end] == number;
   } else if (begin == end) {
      return v[begin] == number;
   } else {
      if (v[middle] == number) {
         return true;
      }
      bool lt = v[middle] < number;
      if (v[middle] > v[begin] && v[middle] > v[end]) {
         if (lt) {
            return false;
         }
         if (v[begin] >= number) {
            return search(v, number, begin, middle);
         } else {
            return search(v, number, middle, end);
         }
      } else if (v[middle] < v[begin] && v[middle] < v[end]) {
         if (!lt) {
            return false;
         }
         if (v[end] >= number) {
            return search(v, number, middle, end);
         } else {
            return search(v, number, begin, middle);
         }
      } else {
         if (v[middle] > v[begin]) {
            int newBegin, newEnd;
            newBegin = lt ? middle : begin;
            newEnd = lt ? end : middle;
            return search(v, number, newBegin, newEnd);
         } else {
            int newBegin, newEnd;
            newBegin = lt ? begin : middle;
            newEnd = lt ? middle : end;
            return search(v, number, newBegin, newEnd);
         }
      }
   }
}

int main(int argc, char *argv[])
{
   std::vector<int> v;
   int c;
   int number;
   bool numberNotInit = true;
   while ((c = getopt(argc, argv, "n:v:")) != EOF) {
      switch (c) {
         case 'v':
            {
               std::stringstream ss(optarg);
               std::string token;
               while (std::getline(ss, token, ' ')) {
                  std::string::size_type sz;
                  int a = std::stoi(token, &sz);
                  v.push_back(a);
               }
               break;
            }
         case 'n':
            {
               std::string::size_type sz;
               number = std::stoi(string(optarg), &sz);
               numberNotInit = false;
               break;
            }
         default:
            exit(1);
      }
   }
   if (v.size() == 0 || numberNotInit) {
      cout << "Usage: " << argv[0] << " -v {list of comma separated numbers}" << "-n {number to search}" << endl;
      exit(1);
   }
   cout << findMin(v, 0, v.size() - 1) << endl;
   cout << search(v, number, 0, v.size() - 1) << endl;
   return 0;
}
