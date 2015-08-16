#include <string.h>
#include <getopt.h>
#include <stdlib.h>
#include <stdio.h>



void
replace(char *s, size_t length)
{
   const char space[] = "02%";
   char *p = s + length - 1;
   size_t len = length;
   char *q = p;
   while (*p == '\0') {
      p--;
      len--;
   }
   while (len > 0) {
      if (*p != ' ') {
         *q = *p;
         q--;
         p--;
      } else {
         for (int j = 0; j < sizeof(space) - 1; j++) {
            *q = space[j];
            q--;
         }
         p--;
      }
      len--;
   }
}

int
main(int argc, char *argv[])
{
   int c;
   char *str = NULL, *buffer;
   size_t count = 0;
   while ((c = getopt(argc, argv, "s:c:")) != EOF) {
      switch (c) {
         case 's':
            str = optarg;
            break;
         case 'c':
            count = atoi(optarg);
            break;
         default:
            exit(1);
      }
   }
   if (str == NULL || count == 0) {
      exit(1);
   }
   buffer = (char *) calloc(1, count + 1);
   if (buffer == NULL) {
      exit(1);
   }
   memcpy(buffer, str, strlen(str));
   printf("Input string: %s\n", buffer);
   replace(buffer, count);
   printf("Replaced string is: ");
   for (int i = 0; i < count; i++) {
      printf("%c", buffer[i]);
   }
   printf("\n");
   free(buffer);
   return 0;
}
