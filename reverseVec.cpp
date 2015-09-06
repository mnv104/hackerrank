#include <vector>
#include <iostream>

using namespace std;

void reverseVector(std::vector<int> &v)
{
   size_t l = v.size();
   for (int i = 0; i < l/2; i++) {
      if (i != l-i-1) {
         int tmp = v[l-i-1];
         v[l-i-1] = v[i];
         v[i] = tmp;
      }
   }
}


void rotateArray(std::vector<int> &v, int numSteps)
{
   size_t l = v.size();
   if (numSteps > l) {
      numSteps = numSteps % l;
   }
   std::vector<int> v1(v.begin(), v.begin() + l - numSteps),
      v2(v.begin() + l - numSteps, v.end());
   reverseVector(v1);
   reverseVector(v2);
   v1.insert(v1.end(), v2.begin(), v2.end());
   reverseVector(v1);
   v = v1;
}

int main(int argc, char *argv[])
{
   int v[argc-2];
   if (argc > 2) {
      for (int j = 2; j < argc; j++) {
         v[j-2] = atoi(argv[j]);
      }
   } else {
      return 0;
   }
   std::vector<int> vec(v, v + sizeof(v) / sizeof(v[0]));
   rotateArray(vec, atoi(argv[1]));
   for (auto i: vec) {
      cout << i << " ";
   }
   cout << endl;
}
