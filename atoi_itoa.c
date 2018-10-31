#include <stdio.h>

 

int atoi(char *str)
{
 int rVal = 0;
 int sign = 1; 


 while (*str && (*str == ' ' || *str == '\t')) str++;
 if (*str == NULL) return(0);

 
 if (*str == '+' || *str == '-') {
  sign = (*str++ == '+') ? 1 : -1;
 }

 while (*str && *str >= '0' && *str <= '9') {
  rVal = rVal * 10 + *str++ - '0';
 }

 return(rVal * sign);
}


char *itoa(int val)
{
 static char rStr[80];
 int i, strLen = 0;
 int minus = val < 0; 

 
 if (minus) val *= -1; 
 while (val) {
  rStr[strLen++] = '0' + val % 10;
  val /= 10;
 }
 if (minus) rStr[strLen++] = '-'; 
 rStr[strLen] = 0x00; 

 
 for (i = 0; i < strLen / 2; i++) {
  rStr[i] ^= rStr[strLen - i - 1] ^= rStr[i] ^= rStr[strLen - i - 1];
 }

 return rStr;
}

 

int main(void)
{
 printf("%d\n", atoi("+100"));
 printf("%d\n", atoi("-1234"));
 printf("%s\n", itoa(1234));
 printf("%s\n", itoa(-321));

 return(0);
}

