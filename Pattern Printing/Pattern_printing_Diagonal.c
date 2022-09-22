// C program to print
// the given pattern

// C program to print
// the given pattern

/* This is I written */

#include<stdio.h>
void main(main)
{
	int i,j;
	
	for( i=1; i<=8; i++)
	{
	    for( j=1; j<=i; j++)
	    {
	        if(i==1 || j==1 || j==(i*2)-j || i==8)
	        {
	            printf("* ");
	        }
	        else
	        {
	            printf("  ");
	        }
	    }
	    printf("\n");
	}
	
}


/* Taken from YT */

#include<stdio.h>
void main(main)
{
	int i,j;
	
	for( i=1; i<=10; i++)
	{
	    for( j=1; j<=10; j++)
	    {
	        if(j==1 || j==i || i==10)
	        {
	            printf("* ");
	        }
	        else
	        {
	            printf("  ");
	        }
	    }
	    printf("\n");
	}
	
}