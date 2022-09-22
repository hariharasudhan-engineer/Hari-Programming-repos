#include <stdio.h>
#include <stdlib.h>

void createDoublyList();
void traverseList();
void AscendTheI();
void DescendTheI();

int routine, i, j;
float dummy;

struct node
{
    float ExI;
    float V;
    float I;
    float F;
    struct node *next;
    struct node *previous;
};

struct node *temp, *newNode, *head;


int main()
{
    printf("Enter the number of nodes: ");
    scanf("%d", &routine);

    createDoublyList();
    traverseList();
    AscendTheI();
    DescendTheI();

    return 0;
}

void createDoublyList()
{
    struct node *dummyVar;
    temp = malloc(sizeof(struct node));
    head = temp;

    printf("Expected Current 1: ");
    scanf("%f", &head->ExI);
    printf("\nVoltage 1: ");
    scanf("%f", &head->V);
    printf("\nCurrent 1: ");
    scanf("%f", &head->I);
    printf("\nFrequency 1: ");
    scanf("%f", &head->F);
    temp->previous = NULL;

    // printf("Voltage: %f \nCurrent: %f \nFrequency: %f \nExpected Current: %f", head->V, head->I, head->F, head->ExI);

    for(i=2; i<=routine; i++)
    {
        newNode = malloc(sizeof(struct node));
// Check whether the memory is filled or  not
        if(newNode == NULL)
        {
            printf("\n******Memory is FULL so it's not allocated******\n");
            break;
        }
// Assign previous address to the dummyVar to store into the current node of previous pointer variable
        dummyVar = temp;
// Assign next node address to the current node "next pointer variable"    
        temp->next = newNode;
// Assign new node address to the head     
        temp = newNode;
// dummyVar holding previous address that address is storing into the current node of previous pointer variable
        temp->previous = dummyVar;

        printf("\nExpected Current %d: ", i);
        scanf("%f", &temp->ExI);
        printf("\nVoltage %d: ", i);
        scanf("%f", &temp->V);
        printf("\nCurrent %d: ", i);
        scanf("%f", &temp->I);
        printf("\nFrequency %d: ", i);
        scanf("%f", &temp->F);
    }
}

/******************************************************************************************
 * This traverseList function is used to check all the next pointer and previous pointer
 * variable in each node is correctly holding the next/previous node of address.
 * Inside this function, head is pointing to the next node by assigning the address
 * which is holding in the current node next pointer variable
******************************************************************************************/
void traverseList()
{
    temp = head;
    printf("\n\nNext pointer variable, so data will be straight: ");
    for(i=0; temp->next != NULL ; i++)
    {
        printf("\n\nExpected Current->%d value = %f", i+1, temp->ExI);
        printf("\nVoltage->%d value = %f", i+1, temp->V);
        printf("\nCurrent->%d value = %f", i+1, temp->I);
        printf("\nFrequency->%d value = %f", i+1, temp->F);
// This is if statement: Last node of next variable will be holding NULL, 
// so this if statement is to avoid the storing of NULL into head
        if(i != routine-1) 
        {
            temp = temp->next;
        }        
    }
    printf("\n\nPrevious pointer variable, so data will be reverse: ");
    for(i=routine; i>0; i--)
    {
        printf("\n\nExpected Current->%d value = %f", i, temp->ExI);
        printf("\nVoltage->%d value = %f", i, temp->V);
        printf("\nCurrent->%d value = %f", i, temp->I);
        printf("\nFrequency->%d value = %f", i, temp->F);

        temp = temp->previous;
    }
}

void AscendTheI()
{
    float ascendArr[routine];
    temp = head;

// Store current(I) into ascendArr array variable to arrange ascending order
    for(i=0; temp->next != NULL ; i++)
    {
        ascendArr[i] = temp->I;
        temp = temp->next;
    }

// Compare each number with all the number and swap if previous is greater than next
    for(i=0; i<routine; i++)
    {
        for(j=i+1; j<routine; j++)
        {
            if(ascendArr[i] >= ascendArr[j])
            {
                dummy = ascendArr[i];
                ascendArr[i] = ascendArr[j];
                ascendArr[j] = dummy;
            }
        }
    }

    printf("\n\nAscending Order of Measured Current is below: ");
    for(i=0; i<routine; i++)
    {
        printf("\nCurrent->%d = %f", i+1, ascendArr[i]);
    }
}

void DescendTheI()
{
    float descendArr[routine];
    temp = head;

// Store current(I) into descendArr array variable to arrange descending order
    for(i=0; temp->next != NULL ; i++)
    {
        descendArr[i] = temp->I;
        temp = temp->next;
    }

// Compare each number with all the number and swap if previous is lesser than next
    for(i=0; i<routine; i++)
    {
        for(j=i+1; j<routine; j++)
        {
            if(descendArr[i] <= descendArr[j])
            {
                dummy = descendArr[i];
                descendArr[i] = descendArr[j];
                descendArr[j] = dummy;
            }
        }
    }

    printf("\n\nDescending Order of Measured Current is below: ");
    for(i=0; i<routine; i++)
    {
        printf("\nCurrent->%d = %f", i+1, descendArr[i]);
    }
}
