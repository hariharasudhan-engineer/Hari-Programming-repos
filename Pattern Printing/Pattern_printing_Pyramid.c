#include <stdio.h>
int main() {
   int i, j, space, rows, coloumns, k, temp=0, count=1;
   printf("Enter the number of rows: ");
   scanf("%d", &rows);
   //printf("Enter the number of coloumns: ");
  // scanf("%d", &coloumns);
   temp = rows;
   for( i=1; i<=rows; i++ )
   {
       for( j=1; j<=(temp-1); j++ )
       {
           printf(" ");
       }
       for( k=1; k<=count; k++ )
       {
           printf("*");
       }
       count=count+2;
       temp-=1;
       printf("\n");
   }
   return 0;
}

OUTPUT:
Enter the number of rows: 7
      *
     ***
    *****
   *******
  *********
 ***********
*************
