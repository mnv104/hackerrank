#include <vector>
#include <cstdio>
#include <climits>
#include <iostream>
#include <stdint.h>

using namespace std;
class Solution {
public:
    int reverse(int x) {
        unsigned int t;
        if (x < 0) {
            t = x * -1;
        } else {
            t = x;
        }
        std::vector<int> v;
        while (t > 0) {
            v.insert(v.begin(), t % 10);
            t /= 10;
        }
        long val = 1;
        long ret = 0;
        while (!v.empty()) {
            long m = val * v.front();
            if (m > INT32_MAX) {
               return 0;
            }
            printf("val=%lu, front()=%d, m=%lu, val*10=%lu, ret=%lu,ret+m=%lu\n",
                   val, v.front(), m, val*10, ret, ret+m);
            val *= 10;
            ret += m;
            if (ret > INT32_MAX) {
               return 0;
            }
            v.erase(v.begin());
        }
        if (x < 0) {
            ret = ret * -1;
        }
        return ret;
    }
};


int main(void)
{
   Solution s;
   cout << s.reverse(5647) << endl;
   cout << s.reverse(1534236469) << endl;
   cout << s.reverse(-2147483412) << endl;
   cout << s.reverse(1563847412) << endl;
   return 0;
}
