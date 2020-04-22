#include <stdio.h>
int main()
{
   int a, b;
   b = 1;
   scanf("%d", &a);
   while (1 < a <= 10)
   {
      b *= a;
      a--;
      if (a == 1)
      {
         printf("该数的阶乘为%d", b);
         break;
      }
   }
}