#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int main () {
   char str[80] = "/sommatrice?op1=1&op2=2";
   char *function, *op1, *op2;
   float val1, val2;
   
   function = strtok(str, "?");
   op1 = strtok(NULL, "&");
   op2 = strtok(NULL, "");
   printf("%s, %s \n", op1, op2);
   strtok(op1,"=");
   val1 = atof(strtok(NULL,"="));
   strtok(op2,"=");
   val2 = atof(strtok(NULL,"="));
   printf("%f, %f \n", val1, val2);
   
   printf("%s %s %s %f %f", function, op1, op2, val1, val2);
   
   return(0);
}

