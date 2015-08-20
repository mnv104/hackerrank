#include <string>
#include <utility>
#include <string.h>
#include <errno.h>
#include <dirent.h>
#include <list>
#include <iostream>
#include <cstdio>
#include <fcntl.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdexcept>
#include <sys/stat.h>

using namespace std;

enum TravType {
   TRAV_DFS = 0,
   TRAV_BFS,
};


class Path {
public:
   std::string _path;
   TravType _type;
   bool _isDir;
public:
   Path(const std::string &path,
        TravType type = TRAV_DFS) :
      _type(type) {
         char *p;
         if ((p = realpath(path.c_str(), NULL)) == NULL) {
            throw std::invalid_argument("Bad path");
         }
         _path = p;
         struct stat s;
         if (stat(_path.c_str(), &s) < 0) {
            throw std::invalid_argument("Failed to do a stat on path");
         }
         _isDir = S_ISDIR(s.st_mode);
         free(p);
   }
   class iterator {
   private:
      Path *_p;
      std::list<std::pair<string, bool> > _v;
   public:
      iterator(Path *p) : _p(p) {
         if (!_p) {
            return;
         }
         _v.push_back(std::make_pair(_p->_path, false));
      }
      ~iterator() { }
      void addDirEntries(const std::string &s) {
         struct stat sbuf;
         if (stat(s.c_str(), &sbuf) == 0 && S_ISDIR(sbuf.st_mode)) {
            DIR *dH;
            dH = opendir(s.c_str());
            if (!dH) {
               cerr << "Failed to open child directory" << endl;
            } else {
               errno = 0;
               struct dirent *de;
               while ((de = readdir(dH)) != NULL) {
                  if (strcmp(de->d_name, ".") &&
                     strcmp(de->d_name, "..")) {
                     std::string path = s + "/" + de->d_name;
                     if (_p->_type == TRAV_BFS)  {
                        _v.push_back(std::make_pair(path, false));
                     } else {
                        _v.push_front(std::make_pair(path, false));
                     }
                  }
               }
               closedir(dH);
            }
         }
      }
      string operator*() {
         string s;
         if (!_p) {
            throw std::invalid_argument("Invalid iterator position");
         }
         if (_v.size() == 0) {
            throw std::invalid_argument("Invalid iterator");
         }
         do {
            list<pair<string, bool> >::iterator it = _v.begin();
            s = it->first;
            struct stat sbuf;
            if (stat(s.c_str(), &sbuf) == 0 && (!S_ISDIR(sbuf.st_mode) || it->second)) {
               return s;
            }
            it->second = true;
            addDirEntries(s);
         } while (1);
      }
      iterator operator++(int unused) {
         if (_v.size() == 0) {
            return *this;
         }
         list<pair<string, bool> >::iterator it = _v.begin();
         _v.erase(it);
         return *this;
      }
      iterator operator++() {
         if (_v.size() == 0) {
            return iterator(NULL);
         }
         list<pair<string, bool> >::iterator it = _v.begin();
         _v.erase(it);
         return *this;
      }
      bool operator!=(const iterator &a) {
         //cout << "size of my list = " << _v.size() << " size of other object list = " << a._v.size() << endl;
         return _v.size() != a._v.size();
      }
   };
   iterator begin() {
      return iterator(this);
   }
   iterator end() {
      return iterator(NULL);
   }
};


int main(int argc, char *argv[])
{
   char *dir;
   if (argc > 1) {
      dir = argv[1];
   } else {
      dir = getenv("PWD");
      if (dir == NULL) {
         throw std::invalid_argument("Invalid current working directory");
      }
   }
   std::string s;
   try {
      s = dir;
   } catch (const std::exception &e) {
      cerr << e.what() << endl;
      throw std::invalid_argument("Failed to convert to string");
   }
   try {
      Path p(s);
      Path::iterator it = p.begin();
      while (it != p.end()) {
         cout << (*it) << endl;
         it++;
      }
   } catch (const std::exception &e) {
      cerr << e.what() << endl;
      throw std::invalid_argument("Failed to path iterate");
   }
   return 0;
}
