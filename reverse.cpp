#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <getopt.h>
#include <iostream>
#include <stdlib.h>
using namespace std;

void reverse(char *s, size_t len)
{
   char *begin = s, *end = s + len - 1;
   while (begin < end) {
      char p = *end;
      *end = *begin;
      *begin = p;
      begin++;
      end--;
   }
}


int main(int argc, char *argv[])
{
   int c;
   char *str = NULL;
   while ((c = getopt(argc, argv, "s:")) != EOF) {
      switch (c) {
         case 's':
            str = strdup(optarg);
            break;
         default:
            exit(1);
      }
   }
   if (str == NULL) {
      exit(1);
   }
   printf("Original string: ");
   size_t len = strlen(str);
   for (int i = 0; i < len; i++) {
      cout << str[i];
   }
   cout << endl;
   reverse(str, strlen(str));
   printf("Reversed string:");
   for (int i = 0; i < len; i++) {
      cout << str[i];
   }
   cout << endl;
   return 0;
}
