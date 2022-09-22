

#include <stdio.h>
#include <stdlib.h>

struct node
{
    int data;
    struct node *previous;
    struct node *next;
};

int main()
{
    struct node *head, *second, *third, *fourth;

    head = malloc(sizeof(struct node));
    second = malloc(sizeof(struct node));
    third = malloc(sizeof(struct node));
    fourth = malloc(sizeof(struct node));

    head->data = 10;
    second->data = 20;
    third->data = 30;
    fourth->data = 40;

    head->previous = NULL;
    second->previous = head;
    third->previous = second;
    fourth->previous = third;

    head->next = second;
    second->next = third;
    third->next = fourth;
    fourth->next = NULL;
}