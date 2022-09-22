#include <stdio.h>
#include <stdlib.h>

struct simple_node
{
    int data;
    struct simple_node *next;
};

int main()
{
    struct simple_node *head, *newNode; // *second, *third, *fourth;

    head = malloc(sizeof(struct simple_node));

    for(int i=0; i<2; i++)
    {
        newNode = malloc(sizeof(struct simple_node));
        printf("Node %d address is %d",i+1, newNode);
    }

    return 0;
}

// #include <stdio.h>
// #include <stdlib.h>

// struct node
// {
//     int data;
//     struct node *next;
// };

// int main()
// {
//     struct node *head, *second, *third, *fourth;

//     head = malloc(sizeof(struct node));
//     second = malloc(sizeof(struct node));
//     third = malloc(sizeof(struct node));
//     fourth = malloc(sizeof(struct node));

//     head->data = 10;
//     second->data = 20;
//     third->data = 30;
//     fourth->data = 40;

//     head->next = second;
//     second->next = third;
//     third->next = fourth;
//     fourth->next = NULL;
// }