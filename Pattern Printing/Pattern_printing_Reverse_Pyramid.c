#include <stdio.h>
int main() {
   int i, j, space, rows, coloumns, k, temp=0;
   printf("Enter the number of rows: ");
   scanf("%d", &rows);
   printf("Enter the number of coloumns: ");
   scanf("%d", &coloumns);
   for( i=1; i<=rows; i++ )
   {
       for( j=0; j<(i-1); j++ )
       {
           printf(" ");
       }
       for( k=1; k<=(coloumns-temp); k++ )
       {
           printf("*");
       }
       temp = temp+2;
       printf("\n");
   }
   return 0;
}

OUTPUT:
Enter the number of rows: 6
Enter the number of coloumns: 11
***********
 *********
  *******
   *****
    ***
     *
