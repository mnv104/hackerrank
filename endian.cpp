#include <stdio.h>
#include <sys/types.h>
#include <stdint.h>


uint16_t
htobes(uint16_t a)
{
   return (((a & 0x00ff) << 8) |
           ((a & 0xff00) >> 8));
}

uint32_t
htobel(uint32_t a)
{
   return (((a & 0x000000ff) << 24) |
           ((a & 0x0000ff00) << 8)  |
           ((a & 0x00ff0000) >> 8)  |
           ((a & 0xff000000) >> 24));
}

uint64_t
htobell(uint64_t a)
{
   return (((a & 0x00000000000000ff) << 56) |
           ((a & 0x000000000000ff00) << 40) |
           ((a & 0x0000000000ff0000) << 24) |
           ((a & 0x00000000ff000000) << 8)  |
           ((a & 0x000000ff00000000) >> 8)  |
           ((a & 0x0000ff0000000000) >> 24) |
           ((a & 0x00ff000000000000) >> 40) |
           ((a & 0xff00000000000000) >> 56));
}

char *
betoasciill(uint64_t a, char *string, int stringLength)
{
   if (snprintf(string, stringLength, "%02x.%02x.%02x.%02x.%02x.%02x.%02x.%02x",
                   ((a & 0xff00000000000000) >> 56),
                   ((a & 0x00ff000000000000) >> 48),
                   ((a & 0x0000ff0000000000) >> 40),
                   ((a & 0x000000ff00000000) >> 32),
                   ((a & 0x00000000ff000000) >> 24),
                   ((a & 0x0000000000ff0000) >> 16),
                   ((a & 0x000000000000ff00) >> 8),
                   ((a & 0x00000000000000ff))) >= stringLength) {
      return NULL;
   }
   return string;
}

char *
betoasciil(uint32_t a, char *string, int stringLength)
{
   if (snprintf(string, stringLength, "%02x.%02x.%02x.%02x",
                   ((a & 0xff000000) >> 24),
                   ((a & 0x00ff0000) >> 16),
                   ((a & 0x0000ff00) >> 8),
                   (a & 0x000000ff)) >= stringLength) {
      return NULL;
   }
   return string;
}

char *
betoasciis(uint16_t a, char *string, int stringLength)
{
   if (snprintf(string, stringLength, "%02x.%02x",
                   ((a & 0xff00) >> 8),
                    (a & 0x00ff)) >= stringLength) {
      return NULL;
   }
   return string;
}


int main(void)
{
   unsigned int a = 1032984;
   unsigned short b = 2049;
   uint64_t c = 8357430024902048;
   printf("0x%x 0x%x\n", a, htobel(a));
   printf("0x%x 0x%x\n", b, htobes(b));
   printf("0x%Lx 0x%Lx\n",
          (unsigned long long)c, (unsigned long long) htobell(c));
   char str[32];
   printf("%s\n", betoasciil(htobel(a), str, sizeof(str)));
   printf("%s\n", betoasciis(htobes(b), str, sizeof(str)));
   printf("%s\n", betoasciill(htobell(c), str, sizeof(str)));
   return 0;
}
