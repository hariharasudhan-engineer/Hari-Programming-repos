// C program to print
// the given pattern

#include<stdio.h>
void main(main)
{
	int i,j,k=1;
	
	for( i=0; i<=6; i++ )
	{ 
	    for( j=1; j<=i; j++ )
	    {
	        printf("%d ", k++);
	    }
	    printf("\n");
	}
	
}

OUTPUT:
1 
2 3 
4 5 6 
7 8 9 10 
11 12 13 14 15 
16 17 18 19 20 21 


// C program to print
// the given pattern

#include<stdio.h>
void main(main)
{
	int i,j,k=1;
	
	for( i=0; i<=5; i++ )
	{ 
	    for( j=1; j<=i; j++ )
	    {
	        printf("%d ", (k++%2));
	    }
	    printf("\n");
	}
	
}


OUTPUT:
1 
0 1 
0 1 0 
1 0 1 0 
1 0 1 0 1 