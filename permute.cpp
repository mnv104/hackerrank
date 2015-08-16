#include <iostream>
#include <sstream>
#include <stdexcept>
#include <vector>
#include <string>



std::vector<std::string>
permute(const std::string &v)
{
   std::vector<std::string> w;
   size_t s = v.size();
   if (s == 0) {
      throw std::invalid_argument("Invalid argument");
   } else if (s == 1) {
      w.emplace_back(v);
      return w;
   } else if (s == 2) {
      std::string s;
      s = std::string(1, v[0]) + std::string(1, v[1]);
      w.emplace_back(s);
      s = std::string(1, v[1]) + std::string(1, v[0]);
      w.emplace_back(s);
      return w;
   } else {
      std::vector<std::string> y;
      char l = v[s - 1];
      w = permute(v.substr(0, v.length() - 1));
      for (const std::string &st : w) {
         int i, j;
         size_t len = st.length();
         for (i = 0; i <= len; i++) {
            std::stringstream ss;
            for (j = 0; j < len; j++) {
               if (i == j) {
                  ss << l;
               }
               ss << st[j];
            }
            if (i == j) {
               ss << l;
            }
            y.emplace_back(ss.str());
         }
      }
      return y;
   }
}


int
main(int argc, const char *argv[])
{
   std::string s;
   if (argc > 1) {
      s = std::string(argv[1]);
   }
   try {
      std::vector<std::string> v = permute(s);
      std::cout << "Number of permutations " << v.size() << std::endl;
      for (const std::string &i : v) {
         std::cout << i << std::endl;
      }
   } catch (const std::exception &e) {
      std::cout << "Error : " << e.what() << std::endl;
      return -1;
   }
   return 0;
}
