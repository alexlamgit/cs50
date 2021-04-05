#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    int number;
    struct node *next;
} 
node;

node *LIST = NULL;

node* createnode(int val)
{
   node *n = malloc(sizeof(node));
    if (*n == NULL)
    {
        printf("Not enough memory")
        return 1; 
    }
    n -> number = 5;
    n -> next = NULL; 
    return n;
}



n = malloc(sizeof(node));
if (n == NULL)
{
    printf("Not enough memory");
    return 1;
}
n -> number = 10;
n -> next = NULL; 


